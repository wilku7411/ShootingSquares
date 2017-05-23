#pragma once

class Item
{
protected:
	std::shared_ptr<sf::RectangleShape> m_body = nullptr;
	std::shared_ptr<BoxCollider> m_collider = nullptr;
	std::shared_ptr<sf::Texture> m_texture = nullptr;
	std::shared_ptr<sf::Sprite> m_sprite = nullptr;

public:

	/// Getters

	std::shared_ptr<sf::RectangleShape> getBody();
	std::shared_ptr<BoxCollider> getCollider() const;
	std::shared_ptr<sf::Texture> getItemTexture() const;
	std::shared_ptr<sf::Sprite>	getItemSprite() const;

	/// Setters

	void setBody(std::shared_ptr<sf::RectangleShape> a_body);
	void setCollider(std::shared_ptr<BoxCollider> a_collider);
	void setItemTexture(std::string a_texture_location);
	
	/// Interface

	virtual void MyAction() = 0;

	/// Methods

	void InitializeAllFields();	
	
	// Creates default item
	void CreateItemPrefab(sf::Uint8 opacity = 32);

	/// Updates

	void Update();

	// Constructor
	Item();

	// Virtual destructor
	virtual ~Item() {};
};