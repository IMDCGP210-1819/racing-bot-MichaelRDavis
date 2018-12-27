#pragma once

#include "../BehaviorTree/BTTask.h"
#include "../Robots/Robot.h"

class Robot;

class DriveTask : public BTTask
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