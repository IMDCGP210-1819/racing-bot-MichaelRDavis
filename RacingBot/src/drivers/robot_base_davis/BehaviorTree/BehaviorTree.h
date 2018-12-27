#pragma once

#include <memory>
#include "../BehaviorTree/BTTaskNode.h"

class Blackboard;
class BTTaskNode;

/**
 * 
 */
class BehaviorTree
{
public:
	/** Default BehaviorTree constructor. */
	BehaviorTree();

	/** Default BehaviorTree destructor. */
	~BehaviorTree();

	/** Update BehaviorTree tasks. */
	void Update();

	/** Set the RootNode of the BehaviorTree. */
	void SetRootNode(const std::shared_ptr<BTTaskNode>& NewNode);

	/** Returns the Blackboard object. */
	inline std::shared_ptr<Blackboard> GetBlackbaord() const
	{
		return m_Blackboard;
	}

protected:
	/** RootNode of the behavior tree. */
	std::shared_ptr<BTTaskNode> m_RootNode;

	/** Blackboard associated with this BehaviorTree. */
	std::shared_ptr<Blackboard> m_Blackboard;
};