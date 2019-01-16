#include "Robot.h"
#include "../BehaviorTree/BehaviorTree.h"
#include "../BehaviorTree/Blackboard.h"
#include "../BehaviorTree/Composites/BTSequence.h"
#include "../RobotAI/RobotTasks.h"

int Robot::m_StuckCount = 0;
const float Robot::MAX_UNSTUCK_ANGLE = 15.0f / 180.0f * PI;
const float Robot::UNSTUCK_TIME_LIMIT = 2.0f;
const float Robot::SHIFT = 0.9f;
const float Robot::SHIFT_MARGIN = 4.0f;
const float Robot::ABS_SLIP = 0.9f;
const float Robot::ABS_MINSPEED = 3.0f;
const float Robot::TCL_SLIP = 0.9f;
const float Robot::TCL_MINSPEED = 3.0f;

Robot::Robot()
	: MAX_UNSTUCK_SPEED(5.0f)
	, MIN_UNSTUCK_DIST(3.0f)
	, STEERING_CONTROL(1.0f)
	, GRAVITY_SCALE(9.81f)
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
	InitTractionControl();
}

void Robot::Drive(tCarElt* Car, tSituation* Situation)
{
	Update(Situation);
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
		m_BehaviorTree->GetBlackbaord()->SetVariable(4, &(tdble)m_Car->ctrl.steer);
	}
}

void Robot::CreateBehaviorTree()
{
	auto sequence = std::make_shared<BTSequence>();
	//auto driveTask = std::make_shared<DriveTask>(m_BehaviorTree->GetBlackbaord());
	auto steerTask = std::make_shared<SteerTask>(m_BehaviorTree->GetBlackbaord());
	auto gearTask = std::make_shared<ShiftGearTask>(m_BehaviorTree->GetBlackbaord());
	auto accelTask = std::make_shared<AccelerateTask>(m_BehaviorTree->GetBlackbaord());
	auto brakeTask = std::make_shared<BrakeTask>(m_BehaviorTree->GetBlackbaord());
	auto reverseTask = std::make_shared<ReverseTask>(m_BehaviorTree->GetBlackbaord());
	sequence->InsertChildNode(steerTask);
	sequence->InsertChildNode(gearTask);
	sequence->InsertChildNode(accelTask);
	sequence->InsertChildNode(brakeTask);
	sequence->InsertChildNode(reverseTask);
	//sequence->InsertChildNode(driveTask);
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
		m_Car->ctrl.steer = *(tdble*)m_BehaviorTree->GetBlackbaord()->GetVariable(4);
		m_Car->ctrl.gear = *(int*)m_BehaviorTree->GetBlackbaord()->GetVariable(3);
		m_Car->ctrl.brakeCmd = *(tdble*)m_BehaviorTree->GetBlackbaord()->GetVariable(2);
		if (m_Car->ctrl.brakeCmd == 0.0f)
		{
			m_Car->ctrl.accelCmd = *(tdble*)m_BehaviorTree->GetBlackbaord()->GetVariable(1);
		}
		else
		{
			m_Car->ctrl.accelCmd = 0.0f;
		}
	}
	else
	{
		OnReverse();
	}
}

void Robot::OnReverse()
{
	m_Car->ctrl.steer = -m_CarAngle / m_Car->_steerLock;
	m_Car->ctrl.gear = -1;
	m_Car->ctrl.accelCmd = 0.5f;
	m_Car->ctrl.brakeCmd = 0.0f;
}

void Robot::Update(tSituation* Situation)
{
	m_TrackAngle = RtTrackSideTgAngleL(&(m_Car->_trkPos));
	m_CarAngle = m_TrackAngle - m_Car->_yaw;
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
		return sqrt((Friction * GRAVITY_SCALE * Segment->radius) / (1.0f - MIN(1.0f, Segment->radius * m_Downforce * Friction / m_Mass)));
	}
}

float Robot::GetTrackSegmentEndDistance()
{
	if (m_Car->_trkPos.seg->type == TR_STR)
	{
		return m_Car->_trkPos.seg->length - m_Car->_trkPos.toStart;
	}
	else
	{
		return (m_Car->_trkPos.seg->arc - m_Car->_trkPos.toStart) * m_Car->_trkPos.seg->radius;
	}
}

float Robot::GetAcceleration()
{
	if (m_Car->_gear > 0)
	{
		float Speed = GetTrackSegmentSpeed(m_Car->_trkPos.seg);
		float GearRatio = m_Car->_gearRatio[m_Car->_gear + m_Car->_gearOffset];
		float MaxRPM = m_Car->_enginerpmRedLine;
		if (Speed > m_Car->_speed_x + FULL_ACCELERATION)
		{
			return 1.0f;
		}
		else
		{
			return Speed / m_Car->_wheelRadius(REAR_RGT) * GearRatio / MaxRPM;
		}
	}
	else
	{
		return 1.0f;
	}
}

float Robot::GetBraking()
{
	tTrackSeg* Segment = m_Car->_trkPos.seg;
	float CurrentSpeedSq = m_Car->_speed_x * m_Car->_speed_x;
	float Friction = Segment->surface->kFriction;
	float MaxHeading = CurrentSpeedSq / (2.0f * Friction * GRAVITY_SCALE);
	float Heading = GetTrackSegmentEndDistance();

	float TrackSpeed = GetTrackSegmentSpeed(Segment);
	
	if (TrackSpeed < m_Car->_speed_x)
		return 1.0f;

	Segment = Segment->next;
	while (Heading < MaxHeading)
	{
		TrackSpeed = GetTrackSegmentSpeed(Segment);
		if (TrackSpeed < m_Car->_speed_x)
		{
			float c = Friction * GRAVITY_SCALE;
			float d = (m_Downforce * Friction + m_DragForce) / m_Mass;
			float SpeedSq = TrackSpeed * TrackSpeed;
			float vel = CurrentSpeedSq;
			float BrakeDist = -log((c + vel * d) / (c + SpeedSq * d)) / (2.0f * d);
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

float Robot::GetSteering()
{
	float SteerAngle = m_CarAngle - m_Car->_trkPos.toMiddle / m_Car->_trkPos.seg->width;
	m_Car->ctrl.steer = SteerAngle / m_Car->_steerLock;
	return SteerAngle;
}

int Robot::GetGear()
{
	if (m_Car->_gear <= 0)
		return 1;

	float GearUp = m_Car->_gearRatio[m_Car->_gear + m_Car->_gearOffset];
	float Omega = m_Car->_enginerpmRedLine / GearUp;
	float WheelRadius = m_Car->_wheelRadius(2);

	if (Omega * WheelRadius * SHIFT < m_Car->_speed_x)
	{
		return m_Car->_gear + 1;
	}
	else
	{
		float GearDown = m_Car->_gearRatio[m_Car->_gear + m_Car->_gearOffset - 1];
		Omega = m_Car->_enginerpmRedLine / GearDown;
		if (m_Car->_gear > 1 && Omega * WheelRadius * SHIFT > m_Car->_speed_x + SHIFT_MARGIN)
		{
			return m_Car->_gear - 1;
		}

		return m_Car->_gear;
	}
}

float Robot::GetABS(float brake)
{
	// If the car is driving slow don't apply ABS.
	if (m_Car->_speed_x < ABS_MINSPEED)
	{
		return brake;
	}

	// Calculate the average slip on all of the cars four wheels.
	float slip = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		slip += m_Car->_wheelSpinVel(i) * m_Car->_wheelRadius(i) / m_Car->_speed_X;
	}

	slip = slip / 4.0f;
	if (slip < ABS_SLIP)
	{
		brake = brake * slip;
	}

	return brake;
}

float Robot::GetTractionControl(float accel)
{
	if (m_Car->_speed_x < TCL_MINSPEED)
	{
		return accel;
	}

	float slip = m_Car->_speed_x / (this->*GET_DRIVEN_WHEEL_SPEED)();
	if (slip < TCL_SLIP)
	{
		accel = 0.0f;
	}

	return accel;
}

void Robot::InitTractionControl()
{
	const char* TerrainType = GfParmGetStr(m_Car->_carHandle, SECT_DRIVETRAIN, PRM_TYPE, VAL_TRANS_RWD);
	if (strcmp(TerrainType, VAL_TRANS_RWD) == 0)
	{
		GET_DRIVEN_WHEEL_SPEED = &Robot::TCLRearWheelDrive;
	}
	else if (strcmp(TerrainType, VAL_TRANS_FWD) == 0)
	{
		GET_DRIVEN_WHEEL_SPEED = &Robot::TCLFrontWheelDrive;
	}
	else if (strcmp(TerrainType, VAL_TRANS_4WD) == 0)
	{
		GET_DRIVEN_WHEEL_SPEED = &Robot::TCLFourWheelDrive;
	}
}

float Robot::TCLRearWheelDrive()
{
	return (m_Car->_wheelSpinVel(REAR_RGT) + m_Car->_wheelSpinVel(REAR_LFT)) * m_Car->_wheelRadius(REAR_LFT) / 2.0f;
}

float Robot::TCLFrontWheelDrive()
{
	return (m_Car->_wheelSpinVel(FRNT_RGT) + m_Car->_wheelSpinVel(FRNT_LFT)) * m_Car->_wheelRadius(FRNT_LFT) / 2.0f;
}

float Robot::TCLFourWheelDrive()
{
	return (m_Car->_wheelSpinVel(FRNT_RGT) + m_Car->_wheelSpinVel(FRNT_LFT)) * m_Car->_wheelRadius(FRNT_LFT) / 4.0f + 
		(m_Car->_wheelSpinVel(REAR_RGT) + m_Car->_wheelSpinVel(REAR_LFT)) * m_Car->_wheelRadius(REAR_LFT) / 4.0f;
}

void Robot::CalculateDownforce()
{
	char* WheelSections[4] = { SECT_FRNTRGTWHEEL, SECT_FRNTLFTWHEEL, SECT_REARRGTWHEEL, SECT_REARLFTWHEEL };
	float RearWingArea = GfParmGetNum(m_Car->_carHandle, SECT_REARWING, PRM_WINGAREA, (char*)nullptr, 0.0f);
	float RearWingAngle = GfParmGetNum(m_Car->_carHandle, SECT_REARWING, PRM_WINGANGLE, (char*)nullptr, 0.0f);
	float WingCoefficient = 1.23f * RearWingArea * sin(RearWingAngle);
	float FrontWing = GfParmGetNum(m_Car->_carHandle, SECT_AERODYNAMICS, PRM_FCL, (char*)nullptr, 0.0f) + GfParmGetNum(m_Car->_carHandle, SECT_AERODYNAMICS, PRM_RCL, (char*)nullptr, 0.0f);
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
	m_DragForce = 0.645f * AirResistance * FrontArea;
}

bool Robot::IsStuck() const
{
	if (fabs(m_CarAngle) > MAX_UNSTUCK_ANGLE && m_Car->_speed_x < MAX_UNSTUCK_SPEED && fabs(m_Car->_trkPos.toMiddle) > MIN_UNSTUCK_DIST)
	{
		if (m_StuckCount > m_MaxStuckCount && m_Car->_trkPos.toMiddle * m_CarAngle < 0.0f)
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
