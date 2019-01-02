#pragma once

#include "BTComposite.h"

/**
 * Sequence nodes tick all of their child nodes in sequence. 
 */
class BTSequence : public BTComposite
{
public:
	BTSequence();
	virtual ~BTSequence();

	virtual void OnInitialize() override;
	virtual EStatus OnUpdate() override;
};