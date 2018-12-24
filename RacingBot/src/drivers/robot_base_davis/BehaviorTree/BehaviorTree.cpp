#include "BehaviorTree.h"

BehaviorTree::BehaviorTree()
	: m_Blackboard(nullptr)
{

}

BehaviorTree::~BehaviorTree()
{

}

void BehaviorTree::Update()
{
	m_RootNode->Tick();
}

void BehaviorTree::SetRootNode(const std::shared_ptr<BTTaskNode>& NewNode)
{
	m_RootNode = NewNode;
}
