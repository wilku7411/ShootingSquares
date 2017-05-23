#pragma once

class Weapon
{
private:
	sf::Clock CLOCK;

	size_t m_weapon_owner_id = 0;
	static constexpr int mMaxBullets = 50;
	std::vector<sf::RectangleShape> mBullets = std::vector<sf::RectangleShape>(mMaxBullets);
	std::vector<BoxCollider> m_bullets_colliders = std::vector<BoxCollider>(mMaxBullets);
	std::vector<sf::Vector2f> mBulletDirection = std::vector<sf::Vector2f>(mMaxBullets);

	float mBulletSpeed = 10.f;
	bool mFirstBulletFired = false;

	bool isClipEmpty = false;
	int mBulletsShot = 0;
	float mFireRate = 10;	// Express how many bullets will be shot per second

	// Weapon sound
	sf::SoundBuffer mSoundBuffer;
	sf::Sound mLaserSound;

public:

	/// Getters 

	std::vector<sf::RectangleShape> getBullets();
	size_t getWeaponOwnerId() const;

	/// Setters 

	void setWeaponOwnerId(size_t ownerId);

	/// Methods

	void Shoot(const sf::Vector2f& a_player_pos, const sf::Vector2f& a_shooting_direction);

	/// Drawing

	void Update();
	
	/// Update

	void Draw(sf::RenderWindow& aRenderWindow);
	
	// Constructor
	Weapon();
};

