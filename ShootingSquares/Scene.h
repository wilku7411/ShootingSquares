#pragma once

class Scene
{
private:
	std::vector<Player>& ptr_player;

	size_t _MAX = 15,							// Max number of entities of each kind to draw from
		_P,										// Number of pick-ups
		_K;										// Number of killers

	std::vector<PickUp> mPickups;
	std::vector<Killer> mKillers;
	std::vector<BoxCollider> mPickupsColliders;
	std::vector<BoxCollider> mKillersColliders;

	std::vector<sf::Vector2f> bulletsPositions;
	std::vector<sf::RectangleShape> quads;

	// "Features"
	static constexpr size_t NumberOfStars = 500;
	int starsSpeed = 0;
	std::vector<sf::CircleShape> Stars;			// Little random stars in background



public:
	/// Getters 

	size_t getNumberOfEntities() const;
	size_t getPickUpsQuantity() const;
	size_t getKillersQuantity() const;
	auto getPickUpsRef() const;
	auto getKillersRef() const;
	auto getPickUpsCollidersRef() const;
	auto getKillersCollidersRef() const;

	/// Initializers

	void Init();
	void SetupPlayer(std::vector<Player>& a_player);

	/// Updates

	void Update();
	void UpdateBackground();

	/// Methods

	void CheckInteractionBetweenEntities();
	
	/// Drawing 

	void Draw(sf::RenderWindow& aWindow);

	// Default ctor for scene with items alone (without players)
	Scene();
	// Constructor overload for vector of players
	Scene(std::vector<Player>& a_player_ref);
};


