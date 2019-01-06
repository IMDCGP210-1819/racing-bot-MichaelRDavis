#include "Blackboard.h"

void Blackboard::SetVariable(uint32_t Key, void* Type)
{
	m_Variables[Key] = Type;
}

void* Blackboard::GetVariable(uint32_t Key)
{
	if (m_Variables.find(Key) == m_Variables.end())
	{
		return m_Variables[Key] = nullptr;
	}

	return m_Variables[Key];
}

bool Blackboard::HasType(uint32_t Key)
{
	return m_Variables.find(Key) != m_Variables.end();
}
