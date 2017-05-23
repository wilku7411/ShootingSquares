#include "AllHeaders.h"

/// Initializers

void PickUp::Instantiate()
{
	m_body->setPosition((float)(rand() % 1800 + 120), (float)(rand() % 1000 + 80));
	setItemTexture("Resources\\first_aid.png");
}

/// Overrides

void PickUp::MyAction()
{
	//Tools::DebugMessageBox("Healed!");
}

// Constructor
PickUp::PickUp() : Item()
{
	Instantiate();
}


