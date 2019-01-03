#include "BTSequence.h"

void BTSequence::OnInitialize()
{
	it = m_Children.begin();
}

EStatus BTSequence::OnUpdate()
{
	while (it != m_Children.end())
	{
		EStatus Status = (*it)->Tick();
		if (Status != EStatus::ESuccess)
		{
			return Status;
		}

		it++;
	}

	return EStatus::ESuccess;
}

void BTSequence::OnTerminate(EStatus status)
{

}
