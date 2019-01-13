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
	tdble accel = *(tdble*)m_Blackboard->GetVariable(1);
	tdble brake = *(tdble*)m_Blackboard->GetVariable(2);
	int gear = *(int*)m_Blackboard->GetVariable(3);
	if (robot)
	{
		robot->m_Acceleration = (tdble)robot->GetAcceleration(robot->m_Car);
		robot->m_Brake = (tdble)robot->GetBraking(robot->m_Car);
		robot->m_Gear = (int)robot->GetGear(robot->m_Car);
		robot->OnDrive();
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
		accel = robot->GetAcceleration(robot->m_Car);
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
		brake = robot->GetBraking(robot->m_Car);
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
		gear = robot->GetGear(robot->m_Car);
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
		float SteerAngle = robot->m_CarAngle - robot->m_Car->_trkPos.toMiddle / robot->m_Car->_trkPos.seg->width;
		robot->m_Car->ctrl.steer = SteerAngle / robot->m_Car->_steerLock;
	}

	return EStatus::ESuccess;
}

void SteerTask::OnTerminate(EStatus status)
{

}
