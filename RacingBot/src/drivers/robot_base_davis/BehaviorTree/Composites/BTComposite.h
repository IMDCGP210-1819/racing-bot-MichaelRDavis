#pragma once

#include <vector>
#include <memory>
#include "../BTTask.h"

/**
 * 
 */
class BTComposite : public BTTask
{
public:
	BTComposite();
	virtual ~BTComposite();
	void InsertChildNode(std::shared_ptr<BTTask> NewTaskNode);

	inline bool HasChildNodes() const
	{
		return !m_Children.empty();
	}

protected:
	std::vector<std::shared_ptr<BTTask>> m_Children;
	std::vector<std::shared_ptr<BTTask>>::iterator it;
};