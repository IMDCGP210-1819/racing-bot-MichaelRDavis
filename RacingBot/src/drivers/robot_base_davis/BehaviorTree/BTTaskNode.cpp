#include "BTTaskNode.h"

BTTaskNode::BTTaskNode()
{
	m_Status = EStatus::EInvalid;
}

BTTaskNode::~BTTaskNode()
{

}

EStatus BTTaskNode::Tick()
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
