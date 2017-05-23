#pragma once

class PickUp : public Item
{
public:

	/// Initializers

	void Instantiate();

	/// Overrides

	virtual void MyAction() override;

	// Constructor
	PickUp();
};


