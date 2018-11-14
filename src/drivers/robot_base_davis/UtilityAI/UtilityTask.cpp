#include "../UtilityAI/UtilityTask.h"
#include "../UtilityAI/UtilityCondition.h"

UtilityTask::UtilityTask()
{

}

void UtilityTask::EvaluateTask()
{
	std::list<UtilityCondition>::const_iterator it;
	for (it = m_UtilityConditions.begin(); it != m_UtilityConditions.end(); it++)
	{

	}
}

void UtilityTask::AddCondition(UtilityCondition condition)
{
	m_UtilityConditions.push_back(condition);
}

void UtilityTask::SetPriority(float newPriority)
{
	m_TaskPriority = newPriority;
}

float UtilityTask::GetTaskPriority()
{
	return m_TaskPriority;
}