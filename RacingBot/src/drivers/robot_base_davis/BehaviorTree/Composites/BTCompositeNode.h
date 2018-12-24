#pragma once

#include <vector>
#include <memory>
#include "../BTTaskNode.h"

class BTCompositeNode : public BTTaskNode
{
public:
	BTCompositeNode()
		: it(m_Children.begin())
	{

	}

	virtual ~BTCompositeNode()
	{
		m_Children.clear();
	}

	void InsertChildNode(std::shared_ptr<BTTaskNode> NewTaskNode)
	{
		m_Children.push_back(NewTaskNode);
	}

	inline bool HasChildNodes() const
	{
		return !m_Children.empty();
	}

protected:
	std::vector<std::shared_ptr<BTTaskNode>> m_Children;
	std::vector<std::shared_ptr<BTTaskNode>>::iterator it;
};