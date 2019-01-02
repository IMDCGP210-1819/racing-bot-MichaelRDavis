#pragma once

#include <cstdint>
#include <unordered_map>

/**
 * Blackboard stores memory values has keyed pairs.
 */
class Blackboard
{
public:
	template<typename T>
	void SetVariable(uint32_t Key, T Type)
	{
		m_Variables[Key] = Type;
	}

	template<typename T>
	T GetVariable(uint32_t Key)
	{
		if (m_Variables.find(key) == m_Variables.end())
		{
			m_Variables[Key] = Type;
		}

		return m_Variables[Key];
	}

protected:
	template<typename T>
	static std::unordered_map<uint32_t, T> m_Variables;
};
