#pragma once

#include "../BehaviorTree/BTTask.h"
#include "../Robots/Robot.h"

class DriveTask : public BTTask
{
public:
	DriveTask(const std::shared_ptr<Blackboard>& Board);

	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};