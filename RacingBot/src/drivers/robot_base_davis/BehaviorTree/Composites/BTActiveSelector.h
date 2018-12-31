#pragma once

#include "BTSelector.h"

class BTActiveSelector : public BTSelector
{
public:
	virtual void OnInitialize() override;
	virtual EStatus OnUpdate() override;
};