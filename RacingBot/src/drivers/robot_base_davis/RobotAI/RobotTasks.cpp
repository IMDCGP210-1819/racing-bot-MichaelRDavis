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
	if (robot)
	{
		if (robot->CanDrive())
		{
			robot->OnDrive();
		}
		else
		{
			robot->OnReverse();
		}
	}

	return EStatus::ESuccess;
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
	}

	return EStatus::ESuccess;
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
		accel = robot->GetTractionControl(robot->GetAcceleration());
		if (robot->m_Car->ctrl.brakeCmd == 0.0f)
		{
			robot->m_Car->ctrl.accelCmd = accel;
		}
		else
		{
			robot->m_Car->ctrl.accelCmd = 0.0f;
		}
	}

	return EStatus::ESuccess;
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
		brake = robot->GetABS(robot->GetBraking());
		robot->m_Car->ctrl.brakeCmd = brake;
	}

	return EStatus::ESuccess;
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
		gear = robot->GetGear();
		robot->m_Car->ctrl.gear = gear;
	}

	return EStatus::ESuccess;
}

void ShiftGearTask::OnTerminate(EStatus status)
{

}

SteerTask::SteerTask(const std::shared_ptr<Blackboard>& Board)
	: BTTask(Board)
{

}

void SteerTask::OnInitialize()
{

}

EStatus SteerTask::OnUpdate()
{
	Robot* robot = (Robot*)m_Blackboard->GetVariable(0);
	tdble steer = *(tdble*)m_Blackboard->GetVariable(4);
	if (robot)
	{
		steer = robot->GetSteering();
		robot->m_Car->ctrl.steer = steer;
	}

	return EStatus::ESuccess;
}

void SteerTask::OnTerminate(EStatus status)
{

}
