#pragma once

#include "../robot_base_davis/BehaviorTree/BTCompositeNode.h"

class BTCompositeSelector : public BTCompositeNode
{
public:
	void OnInitialize() override
	{
		it = m_Children.begin();
	}

	EStatus OnUpdate() override
	{
		while (it != m_Children.end())
		{
			EStatus status = (*it)->Tick();
			if (status == EStatus::ESuccess)
			{
				return status;
			}

			it++;
		}

		return EStatus::ESuccess;
	}

	void OnTerminate(EStatus status) override
	{

	}
};