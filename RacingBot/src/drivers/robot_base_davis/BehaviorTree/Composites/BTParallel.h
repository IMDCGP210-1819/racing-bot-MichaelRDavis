#pragma once

#include "BTComposite.h"

enum class EPolicy : uint8_t
{
	ERequireOne,
	ERequireAll,
};

/**
 * Parallel nodes tick all of their child nodes at the same time.
 */
class BTParallel : public BTComposite
{
public:
	BTParallel(EPolicy Success, EPolicy Failure);
	virtual ~BTParallel();

	virtual EStatus OnUpdate() override;
	virtual void OnTerminate(EStatus status);

protected:
	EPolicy m_SuccessPolicy;
	EPolicy m_FailurePolicy;
};