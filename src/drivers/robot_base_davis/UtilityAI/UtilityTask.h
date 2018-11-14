#pragma once

#include <list>

class UtilityCondition;

class UtilityTask
{
public:
	UtilityTask();

	void EvaluateTask();

	void AddCondition(UtilityCondition condition);
	void SetPriority(float newPriority);

	float GetTaskPriority();

private:
	std::list<UtilityCondition> m_UtilityConditions;
	float m_TaskPriority;
};