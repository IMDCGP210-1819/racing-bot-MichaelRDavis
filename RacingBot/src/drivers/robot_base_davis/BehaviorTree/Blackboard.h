#pragma once

#include <cstdint>

/**
 * 
 */
template<typename T>
class Blackboard
{
public:
	Blackboard()
	{

	}

	void SetVariable(uint32_t TypeID, const& T Type)
	{
		it = std::find(m_VariableArray.begin(), m_VariableArray.end, Type);
		if (it != m_VariableArray.end())
		{
			it->second = Type;
		}


	}

	T GetVariable(uint32_t TypeID, T& Type) const
	{

	}

protected:
	std::pair<uint32_t, T> m_VariableID;
	std::vector<std::pair<uint32_t, T>> m_VariableArray;
	std::vector<std::pair<uint32_t, T>>::iterator it;
};
