#include "BTRepeatDecorator.h"

BTRepeatDecorator::BTRepeatDecorator()
	: BTDecoratorNode()
{
	
}

void BTRepeatDecorator::OnInitialize()
{
	m_Counter = 0;
}

EStatus BTRepeatDecorator::OnUpdate()
{
	while (true)
	{
		m_ChildNode->Tick();
		if (m_ChildNode->GetStatus() == EStatus::ERunning)
		{
			return EStatus::ERunning;
			break;
		}
		if (m_ChildNode->GetStatus() == EStatus::EFailure)
		{
			return EStatus::EFailure;
		}
		if (++m_Counter == m_Limit)
		{
			return EStatus::ESuccess;
		}
		m_ChildNode->ResetTask();
		return EStatus::EInvalid;
	}
}
