#pragma once

#include "BTDecorator.h"

/**
 * 
 */
class BTRepeat : public BTDecorator
{
public:
	BTRepeat();

	// BTTask Interface.
	virtual void OnInitialize() override;
	virtual EStatus OnUpdate() override;

	/** Set the limit on the number of counts. */
	inline void SetCount(int32_t Count)
	{
		m_Limit = Count;
	}

protected:
	int32_t m_Limit;
	int32_t m_Counter;
};