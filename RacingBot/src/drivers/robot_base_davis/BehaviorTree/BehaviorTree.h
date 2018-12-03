#pragma once

class BehaviorTree
{
public:
	BehaviorTree()
	{

	}

	~BehaviorTree()
	{

	}

	virtual void Tick() = 0;
};