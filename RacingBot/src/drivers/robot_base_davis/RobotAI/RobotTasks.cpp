#include "../RobotAI/RobotTasks.h"
#include "../BehaviorTree/Blackboard.h"

DriveTask::DriveTask(const std::shared_ptr<Blackboard>& Board)
	: BTTask(Board)
{

}
void DriveTask::OnInitialize()
{

}

EStatus DriveTask::OnUpdate()
{
	Robot* robot = (Robot*)m_Blackboard->GetVariable(0);
	//tdble accel = *(tdble*)m_Blackboard->GetVariable(1);
	//tdble brake = *(tdble*)m_Blackboard->GetVariable(2);
	//int gear = *(int*)m_Blackboard->GetVariable(3);
	if (robot->CanDrive())
	{
		robot->OnDrive();
		//accel = (tdble)robot->GetAcceleration(robot->m_Car);
		//brake = (tdble)robot->GetBraking(robot->m_Car);
		//gear = (int)robot->GetGear(robot->m_Car);
		//robot->OnDrive(accel, brake, gear);
		return EStatus::ESuccess;
	}

	return EStatus::EInvalid;
}

void DriveTask::OnTerminate(EStatus status)
{

}

ReverseTask::ReverseTask(const std::shared_ptr<Blackboard>& Board)
	: BTTask(Board)
{

}

void ReverseTask::OnInitialize()
{

}

EStatus ReverseTask::OnUpdate()
{
	Robot* robot = (Robot*)m_Blackboard->GetVariable(0);
	if (robot->IsStuck())
	{
		robot->OnReverse();
		return EStatus::ESuccess;
	}

	return EStatus::EInvalid;
}

void ReverseTask::OnTerminate(EStatus status)
{

}

AccelerateTask::AccelerateTask(const std::shared_ptr<Blackboard>& Board)
	: BTTask(Board)
{

}

void AccelerateTask::OnInitialize()
{

}

EStatus AccelerateTask::OnUpdate()
{
	Robot* robot = (Robot*)m_Blackboard->GetVariable(0);
	tdble accel = *(tdble*)m_Blackboard->GetVariable(1);
	if (robot)
	{
		robot->OnDrive();
		robot->GetAcceleration(robot->m_Car);
		robot->m_Car->ctrl.accelCmd = accel;
		return EStatus::ESuccess;
	}

	return EStatus::EInvalid;
}

void AccelerateTask::OnTerminate(EStatus status)
{

}

BrakeTask::BrakeTask(const std::shared_ptr<Blackboard>& Board)
	: BTTask(Board)
{

}

void BrakeTask::OnInitialize()
{

}

EStatus BrakeTask::OnUpdate()
{
	Robot* robot = (Robot*)m_Blackboard->GetVariable(0);
	tdble brake = *(tdble*)m_Blackboard->GetVariable(2);
	if (robot)
	{
		robot->OnDrive();
		robot->GetBraking(robot->m_Car);
		robot->m_Car->ctrl.brakeCmd = brake;
		return EStatus::ESuccess;
	}

	return EStatus::EInvalid;
}

void BrakeTask::OnTerminate(EStatus status)
{

}

ShiftGearTask::ShiftGearTask(const std::shared_ptr<Blackboard>& Board)
	: BTTask(Board)
{

}

void ShiftGearTask::OnInitialize()
{

}

EStatus ShiftGearTask::OnUpdate()
{
	Robot* robot = (Robot*)m_Blackboard->GetVariable(0);
	int gear = *(int*)m_Blackboard->GetVariable(3);
	if (robot)
	{
		robot->OnDrive();
		robot->GetGear(robot->m_Car);
		robot->m_Car->ctrl.gear = gear;
		return EStatus::ESuccess;
	}

	return EStatus::EInvalid;
}

void ShiftGearTask::OnTerminate(EStatus status)
{

}
