#pragma once

#include "BTComposite.h"

/**
 * Sequence nodes tick all of their child nodes in sequence. 
 */
class BTSequence : public BTComposite
{
public:
	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};