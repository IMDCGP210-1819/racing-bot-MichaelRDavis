#pragma once

#include "BTComposite.h"

/**
 * 
 */
class BTSequence : public BTComposite
{
public:
	BTSequence();
	virtual ~BTSequence();

	virtual void OnInitialize() override;
	virtual EStatus OnUpdate() override;
};