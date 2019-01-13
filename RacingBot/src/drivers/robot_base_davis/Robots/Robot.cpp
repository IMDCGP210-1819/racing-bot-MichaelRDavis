#include "Robot.h"
#include "../BehaviorTree/BehaviorTree.h"
#include "../BehaviorTree/Blackboard.h"
#include "../BehaviorTree/Composites/BTSequence.h"
#include "../RobotAI/RobotTasks.h"

int Robot::m_StuckCount = 0;
const float Robot::MAX_UNSTUCK_ANGLE = 30.0f / 180.0f * PI;
const float Robot::UNSTUCK_TIME_LIMIT = 2.0f;
const float Robot::SHIFT = 0.9f;
const float Robot::SHIFT_MARGIN = 4.0f;

Robot::Robot()
	: MAX_UNSTUCK_SPEED(5.0f)
	, MIN_UNSTUCK_DIST(3.0f)
	, STEERING_CONTROL(1.0f)
	, MAX_UNSTUCK_COUNT(100)
	, GRAVITY_SCALE(9.80f)
	, FULL_ACCELERATION(1.0f)
{
	m_BehaviorTree = std::make_unique<BehaviorTree>();
	if (m_BehaviorTree)
	{
		CreateBlackboard();
		CreateBehaviorTree();
	}
}

Robot::Robot(int Index)
	: MAX_UNSTUCK_SPEED(5.0f)
	, MIN_UNSTUCK_DIST(3.0f)
	, STEERING_CONTROL(1.0f)
	, MAX_UNSTUCK_COUNT(100)
	, GRAVITY_SCALE(9.80f)
	, FULL_ACCELERATION(1.0f)
{
	m_BehaviorTree = std::make_unique<BehaviorTree>();
	if (m_BehaviorTree)
	{
		CreateBlackboard();
		CreateBehaviorTree();
	}

	m_Index = Index;
}

Robot::~Robot()
{

}

void Robot::InitTrack(tTrack* Track, void* CarHandle, void** CarParamHandle, tSituation* Situation)
{
	m_Track = Track;
	*CarParamHandle = nullptr;
}

void Robot::NewRace(tCarElt* Car, tSituation* Situation)
{
	m_MaxStuckCount = int(UNSTUCK_TIME_LIMIT / RCM_MAX_DT_ROBOTS);
	m_StuckCount = 0;
	m_Car = Car;
	m_BodyMass = GfParmGetNum(Car->_carHandle, SECT_CAR, PRM_MASS, nullptr, 1000.0f);
	CalculateDownforce();
	CalculateDrag();
}

void Robot::Drive(tCarElt* Car, tSituation* Situation)
{
	m_Car = Car;
	Update(Car, Situation);
	memset(&Car->ctrl, 0, sizeof(tCarCtrl));
	UpdateBehaviorTree();
}

int Robot::PitCommand(tCarElt* Car, tSituation* Situation)
{
	return ROB_PIT_IM;
}

void Robot::EndRace(tCarElt* Car, tSituation* Situation)
{

}

void Robot::CreateBlackboard()
{
	if (m_BehaviorTree)
	{
		m_BehaviorTree->GetBlackbaord()->SetVariable(0, this);
		m_BehaviorTree->GetBlackbaord()->SetVariable(1, &(tdble)m_Car->ctrl.accelCmd);
		m_BehaviorTree->GetBlackbaord()->SetVariable(2, &(tdble)m_Car->ctrl.brakeCmd);
		m_BehaviorTree->GetBlackbaord()->SetVariable(3, &(int)m_Car->ctrl.gear);
	}
}

void Robot::CreateBehaviorTree()
{
	auto sequence = std::make_shared<BTSequence>();
	auto driveTask = std::make_shared<DriveTask>(m_BehaviorTree->GetBlackbaord());
	//auto reverseTask = std::make_shared<ReverseTask>(m_BehaviorTree->GetBlackbaord());
	//auto accelTask = std::make_shared<AccelerateTask>(m_BehaviorTree->GetBlackbaord());
	//auto brakeTask = std::make_shared<BrakeTask>(m_BehaviorTree->GetBlackbaord());
	//auto gearTask = std::make_shared<ShiftGearTask>(m_BehaviorTree->GetBlackbaord());
	sequence->InsertChildNode(driveTask);
	//sequence->InsertChildNode(reverseTask);
	//sequence->InsertChildNode(accelTask);
	//sequence->InsertChildNode(brakeTask);
	//sequence->InsertChildNode(gearTask);
	m_BehaviorTree->SetRootNode(sequence);
}

void Robot::UpdateBehaviorTree()
{
	if (m_BehaviorTree)
	{
		m_BehaviorTree->Update();
	}
}

void Robot::OnDrive()
{
	if (CanDrive())
	{
		float SteerAngle = m_CarAngle - m_Car->_trkPos.toMiddle / m_Car->_trkPos.seg->width;
		m_Car->ctrl.steer = SteerAngle / m_Car->_steerLock;
		m_Car->ctrl.gear = m_Gear;
		m_Car->ctrl.brakeCmd = m_Brake;
		if (m_Car->ctrl.brakeCmd == 0.0f)
		{
			m_Car->ctrl.accelCmd = m_Acceleration;
		}
		else
		{
			m_Car->ctrl.accelCmd = 0.0f;
		}
	}
	else
	{
		m_Car->ctrl.steer = -m_CarAngle / m_Car->_steerLock;
		m_Car->ctrl.gear = -1;
		m_Car->ctrl.accelCmd = 0.3f;
		m_Car->ctrl.brakeCmd = 0.0f;
	}
}

void Robot::OnReverse()
{
	m_Car->ctrl.steer = -m_CarAngle / m_Car->_steerLock;
	m_Car->ctrl.gear = -1;
	m_Car->ctrl.accelCmd = 0.3f;
	m_Car->ctrl.brakeCmd = 0.0f;
}

void Robot::Update(tCarElt* Car, tSituation* Situation)
{
	m_TrackAngle = RtTrackSideTgAngleL(&(Car->_trkPos));
	m_CarAngle = m_TrackAngle - Car->_yaw;
	NORM_PI_PI(m_CarAngle);
	m_Mass = m_BodyMass + m_Car->_fuel;
}

float Robot::GetTrackSegmentSpeed(tTrackSeg* Segment)
{
	if (Segment->type == TR_STR)
	{
		return FLT_MAX;
	}
	else
	{
		float Friction = Segment->surface->kFriction;
		return sqrt(Friction * GRAVITY_SCALE * Segment->radius) / (1.0f - MIN(1.0f, Segment->radius * m_Downforce * Friction / m_Mass));
	}
}

float Robot::GetTrackSegmentEndDistance(tCarElt* Car)
{
	if (Car->_trkPos.seg->type == TR_STR)
	{
		return Car->_trkPos.seg->length - Car->_trkPos.toStart;
	}
	else
	{
		return (Car->_trkPos.seg->arc - Car->_trkPos.toStart) * Car->_trkPos.seg->radius;
	}
}

float Robot::GetAcceleration(tCarElt* Car)
{
	float Speed = GetTrackSegmentSpeed(Car->_trkPos.seg);
	float GearRatio = Car->_gearRatio[Car->_gear + Car->_gearOffset];
	float MaxRPM = Car->_enginerpmRedLine;
	if (Speed > Car->_speed_x + FULL_ACCELERATION)
	{
		return 1.0f;
	}
	else
	{
		return Speed / Car->_wheelRadius(REAR_RGT) * GearRatio / MaxRPM;
	}
}

float Robot::GetBraking(tCarElt* Car)
{
	tTrackSeg* Segment = Car->_trkPos.seg;
	float CurrentSpeedSq = Car->_speed_x * Car->_speed_x;
	float Friction = Segment->surface->kFriction;
	float MaxHeading = CurrentSpeedSq / (2.0f * Friction * GRAVITY_SCALE);
	float Heading = GetTrackSegmentEndDistance(Car);
	float TrackSpeed = GetTrackSegmentSpeed(Segment);
	
	if (TrackSpeed < Car->_speed_x)
		return 1.0f;

	Segment = Segment->next;
	while (Heading < MaxHeading)
	{
		TrackSpeed = GetTrackSegmentSpeed(Segment);
		if (TrackSpeed < Car->_speed_x)
		{
			float SpeedSq = TrackSpeed * TrackSpeed;
			float BrakeDist = m_Mass * (CurrentSpeedSq - SpeedSq) / (2.0f * (Friction * GRAVITY_SCALE * m_Mass + SpeedSq * (m_Downforce * Friction + m_DragForce)));
			if (BrakeDist > Heading)
			{
				return 1.0f;
			}
		}
		Heading += Segment->length;
		Segment = Segment->next;
	}

	return 0.0f;
}

int Robot::GetGear(tCarElt* Car)
{
	if (Car->_gear <= 0)
		return 1;

	float GearUp = Car->_gearRatio[Car->_gear + Car->_gearOffset];
	float Omega = Car->_enginerpmRedLine / GearUp;
	float WheelRadius = Car->_wheelRadius(2);

	if (Omega * WheelRadius * SHIFT < Car->_speed_x)
	{
		return Car->_gear + 1;
	}
	else
	{
		float GearDown = Car->_gearRatio[Car->_gear + Car->_gearOffset - 1];
		Omega = Car->_enginerpmRedLine / GearDown;
		if (Car->_gear > 1 && Omega * WheelRadius * SHIFT > Car->_speed_x + SHIFT_MARGIN)
		{
			return Car->_gear - 1;
		}

		return Car->_gear;
	}
}

void Robot::CalculateDownforce()
{
	char* WheelSections[4] = { SECT_FRNTRGTWHEEL, SECT_FRNTLFTWHEEL, SECT_REARRGTWHEEL, SECT_REARLFTWHEEL };
	float RearWingArea = GfParmGetNum(m_Car->_carHandle, SECT_REARWING, PRM_WINGAREA, (char*)nullptr, 0.0f);
	float RearWingAngle = GfParmGetNum(m_Car->_carHandle, SECT_REARWING, PRM_WINGANGLE, (char*)nullptr, 0.0f);
	float WingCoefficient = 1.23f * RearWingArea * sin(RearWingAngle);
	float FrontWing = GfParmGetNum(m_Car->_carHandle, SECT_AERODYNAMICS, PRM_FCL, (char*)nullptr, 0.0f) + GfParmGetNum(m_Car->_carHandle, SECT_AERODYNAMICS, PRM_FCL, (char*)nullptr, 0.0f);
	float Height = 0.0f;
	
	for (int i = 0; i < 4; i++)
	{
		Height += GfParmGetNum(m_Car->_carHandle, WheelSections[i], PRM_RIDEHEIGHT, (char*)nullptr, 0.20f);
	}

	Height *= 1.5f;
	Height = Height * Height;
	Height = Height * Height;
	Height = 2.0f * exp(-3.0f * Height);
	m_Downforce = Height * FrontWing + 4.0f * WingCoefficient;
}

void Robot::CalculateDrag()
{
	float AirResistance = GfParmGetNum(m_Car->_carHandle, SECT_AERODYNAMICS, PRM_CX, (char*)nullptr, 0.0f);
	float FrontArea = GfParmGetNum(m_Car->_carHandle, SECT_AERODYNAMICS, PRM_FRNTAREA, (char*)nullptr, 0.0f);
	AirResistance = 0.645f * AirResistance * FrontArea;
}

bool Robot::IsStuck() const
{
	if (fabs(m_CarAngle) > MAX_UNSTUCK_ANGLE && m_Car->_speed_x < MAX_UNSTUCK_SPEED && fabs(m_Car->_trkPos.toMiddle) > MIN_UNSTUCK_DIST)
	{
		if (m_StuckCount > MAX_UNSTUCK_COUNT && m_Car->_trkPos.toMiddle * m_CarAngle < 0.0f)
		{
			return true;
		}
		else
		{
			m_StuckCount++;
			return false;
		}
	}
	else
	{
		m_StuckCount = 0;
		return false;
	}
}

bool Robot::CanDrive() const
{
	return !IsStuck();
}
