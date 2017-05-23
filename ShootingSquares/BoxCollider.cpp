#include "AllHeaders.h"

/// Getters

sf::RectangleShape BoxCollider::getRect()
{
	return m_collider_debug_gizmo;
}
sf::Vector2f BoxCollider::getPostion()
{
	return m_collider_debug_gizmo.getPosition();
}

/// Setters

void BoxCollider::setRect(sf::RectangleShape aRect)
{
	m_collider_debug_gizmo = aRect;
}
void BoxCollider::setPosition(sf::Vector2f aPosition)
{
	m_collider_debug_gizmo.setPosition(aPosition);
}

// Update
void BoxCollider::Update(sf::Vector2f position)
{
	left = position.x;
	right = position.x + m_size.x;
	top = position.y;
	bottom = position.y + m_size.y;

	m_top_left_corner = position;
	m_collider_debug_gizmo.setPosition(m_top_left_corner);
	if (!m_is_initialized) m_is_initialized = true;
}

// Returns true if collidion is detected between given colliders
bool BoxCollider::CollisionDetected(const BoxCollider& a, const BoxCollider& b)
{
	if ((a.left + a.right) / 2.0f > b.left && (a.left + a.right) / 2.0f < b.right
		&& (a.top + a.bottom) / 2.0f > b.top && (a.top + a.bottom) / 2.0f < b.bottom)
		return true;
	else return false;
}

// Returns true if this collides with given box collider
bool BoxCollider::Collides(const std::shared_ptr<BoxCollider>& other) const
{
	if (other == nullptr)
	{
		Tools::DebugMessageBox("""Other"" is null pointer!");
		return false;
	}

	if ((this->left + this->right) / 2.0f > other->left && (this->left + this->right) / 2.0f < other->right
		&& (this->top + this->bottom) / 2.0f > other->top && (this->top + this->bottom) / 2.0f < other->bottom)
		return true;
	else return false;
}

// Returns true if this collides with given Rectangle
bool BoxCollider::Collides(const sf::RectangleShape & other) const
{
	if ((this->left + this->right) / 2.0f > other.getPosition().x && (this->left + this->right) / 2.0f < other.getPosition().x + other.getSize().x
		&& (this->top + this->bottom) / 2.0f > other.getPosition().y && (this->top + this->bottom) / 2.0f < other.getPosition().y + other.getSize().y)
		return true;
	else return false;
}

// Method with a reference to an object to follow
void BoxCollider::AttachTo(std::shared_ptr<sf::RectangleShape>& object)
{
	m_ref_to_parent = object;
	m_size = m_ref_to_parent->getSize();

	left = m_ref_to_parent->getPosition().x;
	right = m_ref_to_parent->getPosition().x + m_size.x;
	top = m_ref_to_parent->getPosition().y;
	bottom = m_ref_to_parent->getPosition().y + m_size.y;

	if (m_in_debug)
	{
		m_collider_debug_gizmo.setPosition(sf::Vector2f(left, top));
		m_collider_debug_gizmo.setSize(m_size);
		m_collider_debug_gizmo.setFillColor(sf::Color::Transparent);
		m_collider_debug_gizmo.setOutlineThickness(10.0f);
		m_collider_debug_gizmo.setOutlineColor(sf::Color::Magenta);
	}

}

// Draws debug gizmo
void BoxCollider::Draw(sf::RenderWindow &aWindow)
{
	if (m_in_debug)
		aWindow.draw(m_collider_debug_gizmo);
}

// Default constructor 
BoxCollider::BoxCollider()
{
	//m_in_debug = true;
}

// Not so handy constructor after all
BoxCollider::BoxCollider(sf::Vector2f position, sf::Vector2f size, bool aInDebug)
{
	m_size = size;

	left = position.x;
	right = position.x + size.x;
	top = position.y;
	bottom = position.y + size.y;

	if (aInDebug)
	{
		m_collider_debug_gizmo.setPosition(sf::Vector2f(left, top));
		m_collider_debug_gizmo.setSize(size);
		m_collider_debug_gizmo.setFillColor(sf::Color::Transparent);
		m_collider_debug_gizmo.setOutlineThickness(1.0f);
		m_collider_debug_gizmo.setOutlineColor(sf::Color::Magenta);
	}
}