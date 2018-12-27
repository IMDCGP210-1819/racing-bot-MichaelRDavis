#pragma once

#include "BTComposite.h"

enum class EPolicy : uint8_t
{
	ERequireOne,
	ERequireAll,
};

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