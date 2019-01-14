#pragma once

#include "../BehaviorTree/BTTask.h"
#include "../Robots/Robot.h"

/** Drive the car forward around a trajectory around the track. */
class DriveTask : public BTTask
{
public:
	DriveTask(const std::shared_ptr<Blackboard>& Board);

	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};

/** Steer the car around the track. */
class SteerTask : public BTTask
{
public:
	SteerTask(const std::shared_ptr<Blackboard>& Board);

	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};

/** Reverse the car, if the car is stuck. */
class ReverseTask : public BTTask
{
public:
	ReverseTask(const std::shared_ptr<Blackboard>& Board);

	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};

/** Accelerate the car, apply traction control if necessary. */
class AccelerateTask : public BTTask
{
public:
	AccelerateTask(const std::shared_ptr<Blackboard>& Board);

	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};

/** Apply the cars brakes, apply ABS if necessary. */
class BrakeTask : public BTTask
{
public:
	BrakeTask(const std::shared_ptr<Blackboard>& Board);

	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};

/** Switch the car gears. */
class ShiftGearTask : public BTTask
{
public:
	ShiftGearTask(const std::shared_ptr<Blackboard>& Board);

	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};