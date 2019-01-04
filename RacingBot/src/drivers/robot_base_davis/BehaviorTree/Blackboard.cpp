#include "Blackboard.h"

void Blackboard::SetVariable(uint32_t Key, void* Type)
{
	m_Variables[Key] = Type;
}

void* Blackboard::GetVariable(uint32_t Key)
{
	if (m_Variables.find(Key) == m_Variables.end())
	{
		m_Variables[Key] = NULL;
	}

	return m_Variables[Key];
}