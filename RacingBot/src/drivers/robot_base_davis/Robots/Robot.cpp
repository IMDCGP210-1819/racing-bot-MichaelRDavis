#include "Robot.h"
#include "../BehaviorTree/BehaviorTree.h"
#include "../BehaviorTree/Composites/BTSelector.h"
#include "../RobotAI/RobotTasks.h"

int Robot::m_StuckCount = 0;

Robot::Robot()
{
	m_BehaviorTree = std::make_unique<BehaviorTree>();
}

Robot::~Robot()
{

}

void Robot::CreateBehaviorTree()
{
	auto sequence = std::make_shared<BTSelector>();
	sequence->InsertChildNode(std::make_shared<DriveTask>(this));
	m_BehaviorTree->SetRootNode(sequence);
}

void Robot::Initialize(tCarElt* Car)
{
	m_Car = Car;
}

void Robot::Update()
{
	m_BehaviorTree->Update();
}

void Robot::Drive()
{
	if (CanDrive())
	{
		m_AngleToTrack = RtTrackSideTgAngleL(&(m_Car->_trkPos)) - m_Car->_yaw;
#pragma warning(push)
#pragma warning(disable : 4305)
		NORM_PI_PI(m_AngleToTrack);
#pragma warning(pop)
		m_AngleToTrack -= STEERING_CONTROL * m_Car->_trkPos.toMiddle / m_Car->_trkPos.seg->width;

		m_Car->ctrl.steer = m_AngleToTrack / m_Car->_steerLock;
		m_Car->ctrl.gear = 1;
		m_Car->ctrl.accelCmd = 0.3f;
		m_Car->ctrl.brakeCmd = 0.0f;
	}
	else
	{
		m_AngleToTrack = -RtTrackSideTgAngleL(&(m_Car->_trkPos)) + m_Car->_yaw;
#pragma warning(push)
#pragma warning(disable : 4305)
		NORM_PI_PI(m_AngleToTrack);
#pragma warning(pop)

		m_Car->ctrl.steer = m_AngleToTrack / m_Car->_steerLock;
		m_Car->ctrl.gear = -1;
		m_Car->ctrl.accelCmd = 0.5f;
		m_Car->ctrl.brakeCmd = 0.0f;
	}
}

bool Robot::IsStuck() const
{
	if (fabs(m_AngleToTrack) > MAX_UNSTUCK_ANGLE && m_Car->_speed_x < MAX_UNSTUCK_SPEED && fabs(m_Car->_trkPos.toMiddle) > MIN_UNSTUCK_DIST)
	{
		if (m_StuckCount > MAX_UNSTUCK_COUNT && m_Car->_trkPos.toMiddle * m_AngleToTrack < 0.0f)
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
