#pragma once

#include <cstdint>
#include <unordered_map>

/**
 * Blackboard stores memory values has keyed pairs.
 */
class Blackboard
{
public:
	/** Sets the key value of variable added to the blackboard. */
	void SetVariable(uint32_t Key, void* Type);

	/** Retunrs a variable stored in the blackboard via its key. */
	void* GetVariable(uint32_t Key);

	/** Retunrs true if variable type is in the blackboard via its key. */
	bool HasType(uint32_t Key);

protected:
	/** Map of variables stored in the blackboard. */
	std::unordered_map<uint32_t, void*> m_Variables;
};