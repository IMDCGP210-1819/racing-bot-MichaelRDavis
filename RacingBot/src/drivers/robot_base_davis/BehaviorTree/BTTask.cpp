#include "BTTask.h"
#include "Blackboard.h"

BTTask::BTTask()
{
	m_Status = EStatus::EInvalid;
}

BTTask::BTTask(std::shared_ptr<Blackboard> Board)
{
	m_Blackboard = Board;
}

BTTask::~BTTask()
{

}

EStatus BTTask::Tick()
{
	if (m_Status != EStatus::ERunning)
	{
		OnInitialize();
	}

	m_Status = OnUpdate();

	if (m_Status != EStatus::ERunning)
	{
		OnTerminate(m_Status);
	}

	return m_Status;
}

void BTTask::Abort()
{
	OnTerminate(EStatus::EAborted);
	m_Status = EStatus::EAborted;
}
