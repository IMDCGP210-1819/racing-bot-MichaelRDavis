#pragma once

#include "../BehaviorTree/BTTaskNode.h"
#include <memory>

class BTDecoratorNode : public BTTaskNode
{
public:
	BTDecoratorNode()
		: m_ChildNode(nullptr)
	{

	}

	virtual ~BTDecoratorNode()
	{
		
	}

	void SetChildNode(std::shared_ptr<BTTaskNode> NewTaskNode)
	{
		m_ChildNode = NewTaskNode;
	}

	inline bool HasChildNode() const
	{
		return m_ChildNode != nullptr;
	}

protected:
	std::shared_ptr<BTTaskNode> m_ChildNode;
};