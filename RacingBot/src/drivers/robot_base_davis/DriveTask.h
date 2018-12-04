#pragma once

#include "../robot_base_davis/BehaviorTree/BTTaskNode.h"
#include "../robot_base_davis/Robot.h"

class Robot;

class DriveTask : public BTTaskNode
{
public:
	void OnInitialize() override
	{

	}

	EStatus OnUpdate() override
	{
		m_Robot->Drive();
	}

	void OnTerminate(EStatus status) override
	{

	}

private:
	Robot* m_Robot;
};