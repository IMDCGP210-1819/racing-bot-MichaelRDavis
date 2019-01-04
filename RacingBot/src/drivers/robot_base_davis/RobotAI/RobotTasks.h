#pragma once

#include "../BehaviorTree/BTTask.h"
#include "../Robots/Robot.h"

class DriveTask : public BTTask
{
public:
	void OnInitialize() override
	{
		
	}

	EStatus OnUpdate() override
	{
		Robot* bt = (Robot*)m_Blackboard->GetVariable(0);
		if (bt)
		{
			bt->OnDrive();
			return EStatus::ESuccess;
		}

		return EStatus::EInvalid;
	}

	void OnTerminate(EStatus status) override
	{

	}
};