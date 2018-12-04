#pragma once

#include "../robot_base_davis/BehaviorTree/BTTaskNode.h"
#include "../robot_base_davis/Robot.h"

class Robot;

class DriveTask : public BTTaskNode
{
public:
	DriveTask(Robot* robot)
	{
		m_Robot = robot;
	}

	void OnInitialize() override
	{
		
	}

	EStatus OnUpdate() override
	{
		if (m_Robot)
		{
			m_Robot->Drive();
			return EStatus::ESuccess;
		}

		return EStatus::EInvalid;
	}

	void OnTerminate(EStatus status) override
	{

	}

private:
	Robot* m_Robot;
};