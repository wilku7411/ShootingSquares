#pragma once
class Game
{
public:
	// Debug only
	bool InDebug = false;

private:

	// Config section
	Config GameConfig;
	GUI GameGUI;
	std::vector<GUI_INFO> Info;

	// Player section
	static constexpr size_t howManyPlayers = 2;
	std::vector<Player> players;

	// Scene section
	std::shared_ptr<Scene> ptr_scene = nullptr;
	sf::Music bg_music;

public:

	/// Updates

	void Update(sf::RenderWindow& aWindow);

	/// Drawing

	void Draw(sf::RenderWindow& aWindow);

	/// Methods 

	// Access to Configs section
	Config& AccessConfigs();

	Game(bool debug_flag = false);
};

