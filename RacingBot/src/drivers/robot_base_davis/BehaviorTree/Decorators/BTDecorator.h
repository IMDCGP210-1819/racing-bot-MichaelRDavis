#pragma once

#include "../BTTask.h"
#include <memory>

/**
 * 
 */
class BTDecorator : public BTTask
{
public:
	BTDecorator();
	virtual ~BTDecorator();

	inline void SetChildNode(std::shared_ptr<BTTask> NewTaskNode)
	{
		m_ChildNode = NewTaskNode;
	}

	inline bool HasChildNode() const
	{
		return m_ChildNode != nullptr;
	}

protected:
	std::shared_ptr<BTTask> m_ChildNode;
};