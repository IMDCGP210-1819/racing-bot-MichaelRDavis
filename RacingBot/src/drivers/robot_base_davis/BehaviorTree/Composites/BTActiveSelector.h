#pragma once

#include "BTSelector.h"

class BTActiveSelector : public BTSelector
{
public:
	// BTTask Interface.
	virtual void OnInitialize() override;
	virtual EStatus OnUpdate() override;
};