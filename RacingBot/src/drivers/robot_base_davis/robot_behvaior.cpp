#include "../robot_base_davis/robot_behavior.h"
#include "../robot_base_davis/robot.h"

robotFSM::robotFSM(Robot* owner)
	: m_owner(owner)
{
	m_currentState = eRobotState::eStart;
}

robotFSM::~robotFSM()
{

}

void robotFSM::update()
{
	if (m_owner != nullptr)
	{
		if (m_owner->canDrive())
		{
			setState(eRobotState::eForward);
			if (m_currentState == eRobotState::eForward)
			{
				m_owner->driveRobot();
			}
		}
		if (m_owner->canAccel())
		{
			setState(eRobotState::eAccel);
			if (m_currentState == eAccel)
			{
				m_owner->driveRobot();
				m_owner->accelRobot();
			}
		}
		if (m_owner->isStuck())
		{
			setState(eRobotState::eReverse);
			if (m_currentState == eRobotState::eReverse)
			{
				m_owner->reverseRobot();
			}
		}
	}
}

void robotFSM::setState(eRobotState newState)
{
	m_currentState = newState;
}

eRobotState robotFSM::getCurrentState() const
{
	return m_currentState;
}