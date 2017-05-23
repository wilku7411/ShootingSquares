#pragma once
#include "Item.h"
class Killer : public Item
{
public:
	/// Initializers

	void Instantiate();

	/// Overrides

	virtual void MyAction() override;

	// Constructor
	Killer();
};

