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
		accel = (tdble)robot->GetAcceleration(robot->m_Car);
		brake = (tdble)robot->GetBraking(robot->m_Car);
		gear = (int)robot->GetGear(robot->m_Car);
		robot->OnDrive(accel, brake, gear);
		return EStatus::ESuccess;
	}

	return EStatus::EInvalid;
}

void DriveTask::OnTerminate(EStatus status)
{

}

ReverseTask::ReverseTask(const std::shared_ptr<Blackboard>& Board)
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
		return EStatus::ESuccess;
	}

	return EStatus::ESuccess;
}

void ReverseTask::OnTerminate(EStatus status)
{

}
