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

class ReverseTask : public BTTask
{
public:
	ReverseTask(const std::shared_ptr<Blackboard>& Board);

	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};

class AccelerateTask : public BTTask
{

};

class BrakeTask : public BTTask
{

};

class ShiftGearTask : public BTTask
{

};