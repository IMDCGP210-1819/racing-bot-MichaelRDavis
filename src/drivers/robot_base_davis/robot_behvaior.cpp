#include "../robot_base_davis/robot_behavior.h"
#include "../robot_base_davis/robot.h"

robotFSM::robotFSM(robot* owner)
	: m_owner(owner)
{
	currentState = eRobotState::eStart;
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
			if (currentState == eRobotState::eForward)
			{
				m_owner->driveRobotForward();

			}
		}	
		if (m_owner->isStuck())
		{
			setState(eRobotState::eReverse);
			if (currentState == eRobotState::eReverse)
			{
				m_owner->driveRobotBackward();
			}
		}
	}
}

void robotFSM::setState(eRobotState newState)
{
	currentState = newState;
}

eRobotState robotFSM::getCurrentState() const
{
	return currentState;
}