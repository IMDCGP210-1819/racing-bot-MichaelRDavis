#pragma once

#include "BTDecoratorNode.h"

class BTRepeatDecorator : public BTDecoratorNode
{
public:
	BTRepeatDecorator();

	virtual void OnInitialize() override;
	virtual EStatus OnUpdate() override;

	inline void SetCount(int32_t Count)
	{
		m_Limit = Count;
	}

protected:
	int32_t m_Limit;
	int32_t m_Counter;
};