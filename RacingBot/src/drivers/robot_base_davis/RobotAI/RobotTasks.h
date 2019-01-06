#pragma once

#include "../BehaviorTree/BTTask.h"
#include "../Robots/Robot.h"

class DriveTask : public BTTask
{
public:
	DriveTask(const std::shared_ptr<Blackboard>& Board)
		: BTTask(Board)
	{

	}

	void OnInitialize() override
	{
		
	}

	EStatus OnUpdate() override
	{
		Robot* robot = (Robot*)m_Blackboard->GetVariable(0);
		if (robot)
		{
			robot->OnDrive();
			return EStatus::ESuccess;
		}

		return EStatus::EInvalid;
	}

	void OnTerminate(EStatus status) override
	{

	}
};