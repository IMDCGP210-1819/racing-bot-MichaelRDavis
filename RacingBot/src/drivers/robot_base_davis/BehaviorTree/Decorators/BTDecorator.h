#pragma once

#include "../BTTask.h"
#include <memory>

/**
 * Decorator nodes wrap functionality of underlying nodes.
 */
class BTDecorator : public BTTask
{
public:
	/** Default BTDecorator constructor. */
	BTDecorator();

	/** Default BTDecorator destructor. */
	virtual ~BTDecorator();

	/** Sets the child node to a new node. */
	inline void SetChildNode(std::shared_ptr<BTTask> NewTaskNode)
	{
		m_ChildNode = NewTaskNode;
	}

	/** Retunrs true if task has a child node. */
	inline bool HasChildNode() const
	{
		return m_ChildNode != nullptr;
	}

protected:
	/** Smart pointer to the current child node. */
	std::shared_ptr<BTTask> m_ChildNode;
};