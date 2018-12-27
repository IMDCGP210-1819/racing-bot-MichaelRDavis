#include "BTTask.h"

BTTask::BTTask()
{
	m_Status = EStatus::EInvalid;
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
