#include "AllHeaders.h"


/// Initializers
void Killer::Instantiate()
{
	m_body->setPosition((float)(rand() % 1800 + 120), (float)(rand() % 1000 + 80));
	setItemTexture("Resources\\skull.png");
}

/// Overrides

void Killer::MyAction()
{
	//Tools::DebugMessageBox("Ouch!");
}

// Constructor
Killer::Killer() : Item()
{
	Instantiate();
}