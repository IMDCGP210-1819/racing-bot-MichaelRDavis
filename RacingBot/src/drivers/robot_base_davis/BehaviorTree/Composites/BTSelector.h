#pragma once

#include "../Composites/BTComposite.h"

/**
 *	Selector nodes Tick all of their child nodes in order.
 *	If the child node is successful or currently running, Tick will return either status.
 *	On next Tick update the selector node will Tick all of it's child nodes again.
 *	If the child node fails, the selector will terminate.
 */
class BTSelector : public BTComposite
{
public:
	void OnInitialize() override;
	EStatus OnUpdate() override;
	void OnTerminate(EStatus status) override;
};