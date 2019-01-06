#pragma once

#include <cstdint>
#include <unordered_map>

/**
 * Blackboard stores memory values has keyed pairs.
 */
class Blackboard
{
public:
	void SetVariable(uint32_t Key, void* Type);
	void* GetVariable(uint32_t Key);
	bool HasType(uint32_t Key);

protected:
	std::unordered_map<uint32_t, void*> m_Variables;
};