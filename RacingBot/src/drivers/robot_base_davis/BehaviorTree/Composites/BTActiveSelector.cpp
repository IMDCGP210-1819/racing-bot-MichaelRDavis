#include "BTActiveSelector.h"

void BTActiveSelector::OnInitialize()
{
	it = m_Children.begin();
}

EStatus BTActiveSelector::OnUpdate()
{
	std::vector<std::shared_ptr<BTTask>>::iterator prev = it;

	BTSelector::OnInitialize();
	EStatus Result = BTSelector::OnUpdate();

	if (prev != m_Children.end() && it != prev)
	{
		(*prev)->OnTerminate(EStatus::EAborted);
	}

	return Result;
}
