#include "AllHeaders.h"

/// Getters

std::shared_ptr<sf::RectangleShape> Item::getBody()
{
	return m_body;
}
std::shared_ptr<BoxCollider> Item::getCollider() const
{
	return m_collider;
}
std::shared_ptr<sf::Texture> Item::getItemTexture() const
{
	return m_texture;
}
std::shared_ptr<sf::Sprite> Item::getItemSprite() const
{
	return m_sprite;
}

/// Setters

void Item::setBody(std::shared_ptr<sf::RectangleShape> a_body)
{
	m_body = std::move(a_body);
}
void Item::setCollider(std::shared_ptr<BoxCollider> a_collider)
{
	m_collider = a_collider;
}
void Item::setItemTexture(std::string a_texture_location)
{
	m_texture->loadFromFile(a_texture_location);
	m_sprite->setTexture(*m_texture);
}

/// Initializers

void Item::InitializeAllFields()
{
	m_body = std::make_shared<sf::RectangleShape>();
	m_collider = std::make_shared<BoxCollider>();
	m_texture = std::make_shared<sf::Texture>();
	m_sprite = std::make_shared<sf::Sprite>();
	CreateItemPrefab();
}

void Item::CreateItemPrefab(sf::Uint8 opacity)
{
	sf::Vector2f defaultSize{ 50.0f, 50.0f };
	sf::Vector2f defaultPosition{ SCREENWIDTH / 2, SCREENHEIGHT / 2 };

	m_body->setPosition(defaultPosition);
	m_body->setSize(defaultSize);
	m_body->setFillColor(sf::Color(128, 32, 255, opacity));

	m_collider->AttachTo(m_body);
}

/// Updates

void Item::Update()
{
	m_collider->Update(m_body->getPosition());
	m_sprite->setPosition(m_body->getPosition());
}

// Constructor
Item::Item()
{
	InitializeAllFields();
}