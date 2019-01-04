#include "Robot.h"
#include "../BehaviorTree/BehaviorTree.h"
#include "../BehaviorTree/Blackboard.h"
#include "../BehaviorTree/Composites/BTSequence.h"
#include "../RobotAI/RobotTasks.h"

int Robot::m_StuckCount = 0;
const float Robot::MAX_UNSTUCK_ANGLE = 30.0f / 180.0f * PI;
const float Robot::UNSTUCK_TIME_LIMIT = 2.0f;

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
	}
}

void Robot::CreateBehaviorTree()
{
	auto sequence = std::make_shared<BTSequence>();
	sequence->InsertChildNode(std::make_shared<DriveTask>());
	m_BehaviorTree->SetRootNode(sequence);
}

void Robot::UpdateBehaviorTree()
{
	m_BehaviorTree->Update();
}

void Robot::OnDrive()
{
	if (CanDrive())
	{
		float SteerAngle = m_CarAngle - m_Car->_trkPos.toMiddle / m_Car->_trkPos.seg->width;
		m_Car->ctrl.steer = SteerAngle / m_Car->_steerLock;
		m_Car->ctrl.gear = 1;
		m_Car->ctrl.accelCmd = 0.3f;
		m_Car->ctrl.brakeCmd = 0.0f;
	}
	else
	{
		m_Car->ctrl.steer = -m_CarAngle / m_Car->_steerLock;
		m_Car->ctrl.gear = -1;
		m_Car->ctrl.accelCmd = 0.3f;
		m_Car->ctrl.brakeCmd = 0.0f;
	}
}

void Robot::Update(tCarElt* Car, tSituation* Situation)
{
	m_TrackAngle = RtTrackSideTgAngleL(&(Car->_trkPos));
	m_CarAngle = m_TrackAngle - Car->_yaw;
	NORM_PI_PI(m_CarAngle);
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
		return sqrt(Friction * GRAVITY_SCALE * Segment->radius);
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
