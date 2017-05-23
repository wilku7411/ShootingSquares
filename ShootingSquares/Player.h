#pragma once

class Player
{
public:
	// For debuging purposes
	bool inDebug = false;

private:
	// Basic player information
	int mId = 0;
	float mScore = 0;
	float mPlayerHP = 100.0f;

	//Attached controller 
	Controller m_controller;

	/// Player graphical manifestation
	/// includes players basic body and collider 
	sf::RectangleShape mRect;
	sf::Vector2f mRectCenter = { 0.0f, 0.0f };
	std::shared_ptr<BoxCollider> mRectCollider;
	sf::Vector2f mColliderOffset = { 10.0f, 10.0f };

	sf::Vector2f mPreviousPosition;
	sf::Vector2f m_speed;

	Weapon mPlayerWeapon;

	// Fields used for borderless, passable walls
	// should not be here 
	// TODO move 
	enum class TouchedBorder { TOP, BOTTOM, LEFT, RIGHT, NONE };
	TouchedBorder mTouchedWall = TouchedBorder::NONE;
	bool mPassableWalls = false;
	sf::Vector2f mTeleportationPoint = { 0.0f,0.0f };

public:

	/// Getters

	const Player* getRefToPlayer() const;
	sf::RectangleShape getRect();
	std::shared_ptr<BoxCollider> getPlayerCollider() const;
	int getID();
	float getPlayerHP() const;
	Weapon getWeapon() const;

	/// Setters

	void setRectPos(sf::Vector2f aPos);
	void setID(int aID);
	void setPlayerHP(float aHP);

	/// Methods 

	// Manages users input
	void PlayerController();

	// This one will probably be moved somewhere else TODO: move this function
	void CheckMapBorders(bool aPassableWalls = false);
	
	// Deals damage to player
	void TakeDmg(float hpDecrease);
	
	// Heals player
	void Heal(float hpIncrease);

	/// Drawing 

	void Draw(sf::RenderWindow& aRenderWindow);
	
	///Updates
	void FirstUpdate();
	void Update();
	void UpdateSpeed();

	// Constructor
	Player();
};

