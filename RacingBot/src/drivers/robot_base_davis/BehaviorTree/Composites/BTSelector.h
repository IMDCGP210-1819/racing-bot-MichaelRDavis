#pragma once

#include "../Composites/BTComposite.h"

/**
 * 
 */
class BTSelector : public BTComposite
{
public:
	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};