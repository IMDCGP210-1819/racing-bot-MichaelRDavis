#pragma once

#include <list>

class UtilityTask;

class Utility
{
public:
	Utility();

	virtual void AddTask(UtilityTask* task);

private:
	std::list<UtilityTask> m_Tasks;
};