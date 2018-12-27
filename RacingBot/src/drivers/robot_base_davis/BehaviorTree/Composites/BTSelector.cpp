#include "BTSelector.h"

void BTSelector::OnInitialize()
{
	it = m_Children.begin();
}

EStatus BTSelector::OnUpdate()
{
	while (it != m_Children.end())
	{
		EStatus status = (*it)->Tick();
		if (status == EStatus::EFailure)
		{
			return status;
		}

		it++;
	}

	return EStatus::EFailure;
}

void BTSelector::OnTerminate(EStatus status)
{

}
