#pragma once

#include <cstdint>
#include "../BehaviorTree/BTNode.h"

/** Task status */
enum class EStatus : uint8_t
{
	EInvalid,
	ESuccess,
	EFailure,
	ERunning,
};

/**
 * 
*/
class BTTaskNode : public BTNode
{
public:
	/** Default BTTaskNode constructor. */
	BTTaskNode();

	/** Default BTtaskNode destructor. */
	~BTTaskNode();

	/** Update the current task, ideally called once per frame. */
	EStatus Tick();

	/** Update the current task */
	virtual EStatus OnUpdate() = 0;

	/** Initialize the current task. */
	virtual void OnInitialize() = 0;

	/** Terminate the current task.
	*	@param status - Status of the current task.
	*/
	virtual void OnTerminate(EStatus status) = 0;

	/** Return true if the current task ran successfully. */
	inline bool IsSuccess() const
	{
		return m_Status == EStatus::ESuccess;
	}

	/** Return true if the current task failed to run. */
	inline bool IsFailure() const
	{
		return m_Status == EStatus::EFailure;
	}

	/** Return true if the current task is currently running. */
	inline bool IsRunning() const
	{
		return m_Status == EStatus::ERunning;
	}

	/** Return true if current task terminated. */
	inline bool IsTarminated() const
	{
		return IsSuccess() || IsFailure();
	}

	/** Reset the status of the current task. */
	inline void ResetTask()
	{
		m_Status = EStatus::EInvalid;
	}

	/** Get the current task status */
	inline EStatus GetStatus() const
	{
		return m_Status;
	}

protected:
	/** Current task status */
	EStatus m_Status;
};