#include "BehaviorTree.h"
#include "Blackboard.h"

BehaviorTree::BehaviorTree()
	: m_Blackboard(std::make_shared<Blackboard>())
{

}

BehaviorTree::~BehaviorTree()
{

}

void BehaviorTree::Update()
{
	m_RootNode->Tick();
}

void BehaviorTree::SetRootNode(const std::shared_ptr<BTTask>& NewNode)
{
	m_RootNode = NewNode;
}
