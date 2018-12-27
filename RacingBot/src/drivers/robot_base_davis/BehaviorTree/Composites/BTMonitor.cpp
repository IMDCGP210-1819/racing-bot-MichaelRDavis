#include "BTMonitor.h"

BTMonitor::BTMonitor()
	: BTParallel(EPolicy::ERequireOne, EPolicy::ERequireOne)
{

}

void BTMonitor::AddCondition(std::shared_ptr<BTTask> Condition)
{
	m_Children.insert(m_Children.begin(), Condition);
}

void BTMonitor::AddTask(std::shared_ptr<BTTask> Task)
{
	m_Children.push_back(Task);
}
