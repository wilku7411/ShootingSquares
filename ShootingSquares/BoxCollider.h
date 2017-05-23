#pragma once

class BoxCollider
{
public:
	float left = 0, right = 0, top = 0, bottom = 0;

private:
	sf::Vector2f m_top_left_corner = { 0.0f, 0.0f };
	sf::RectangleShape m_collider_debug_gizmo;
	static constexpr bool m_in_debug = true;
	sf::Vector2f m_size = { 0.0f, 0.0f };
	std::shared_ptr<sf::RectangleShape> m_ref_to_parent = nullptr;
	bool m_is_initialized = false;

public:

	/// Getters

	sf::RectangleShape getRect();
	sf::Vector2f getPostion();

	/// Setters

	void setRect(sf::RectangleShape aRect);
	void setPosition(sf::Vector2f aPosition);

	// Updates
	void Update(sf::Vector2f position);

	/// Methods

	// Returns true if collidion is detected between given colliders
	static bool CollisionDetected(const BoxCollider& a, const BoxCollider& b);

	// Returns true if this collides with given box collider
	bool Collides(const std::shared_ptr<BoxCollider>& other) const;
	
	// Returns true if this collides with given sfml rectangle shape
	bool Collides(const sf::RectangleShape& other) const;
	
	// Method with a reference to an object to follow
	void AttachTo(std::shared_ptr<sf::RectangleShape>& object);
	
	//Draws debug gizmo
	void Draw(sf::RenderWindow &aWindow);

	///Constructors 

	// Default constructor initializes without attaching to object
	BoxCollider();

	/// Not so handy constructor after all :c
	// @param position - position of object to attach to
	// @param size - size of object to attach to
	// @param aInDebug - if true will be drawn, else invisible
	BoxCollider(sf::Vector2f position, sf::Vector2f size, bool aInDebug = false);
};

