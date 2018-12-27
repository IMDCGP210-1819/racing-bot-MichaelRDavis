#pragma once

#include "BTParallel.h"

/**
 * 
 */
class BTMonitor : public BTParallel
{
public:
	BTMonitor();

	void AddCondition(std::shared_ptr<BTTask> Task);
	void AddTask(std::shared_ptr<BTTask> Task);
};