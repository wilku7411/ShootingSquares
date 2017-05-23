
#pragma once

class GUI
{
private:
	size_t mHowManyPlayers = 0;
	std::vector<sf::Vector2f> anchorToPlayer;

	// All info needed to properly draw GUI
	std::vector<GUI_INFO> all_players_info;

	// Score
	std::vector<float> mScore;

	sf::Font mFont;
	sf::Text mScoreText;
	float mHpBarModifier = 6.0f;

public:

	/// Initializers
	void Init(std::vector<GUI_INFO>& allplayers);

	/// Methods 
	void Draw(sf::RenderWindow &aWindow);

	/// Updates 
	void Update(std::vector<GUI_INFO>& players);

	/// Constructor
	GUI();
};

