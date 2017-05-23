#include "AllHeaders.h"

void Game::Update(sf::RenderWindow& aWindow)
{
	for (size_t i = 0, j = howManyPlayers - 1; i < howManyPlayers; i++, j--)
	{
		players[i].Update();
	}

	for (size_t i = 0; i < players.size(); i++)
	{
		Info[i].HP = players[i].getPlayerHP();
		Info[i].POSITION = players[i].getRect().getPosition();
	}

	GameGUI.Update(Info);

	ptr_scene->Update();

	Draw(aWindow);
}

void Game::Draw(sf::RenderWindow& aWindow)
{
	if (InDebug)
		if (!players[0].inDebug)
			players[0].inDebug = true;

	// Draw GUI
	GameGUI.Draw(aWindow);

	// Draw scene
	ptr_scene->Draw(aWindow);

	// Draw players
	for (size_t i = 0; i < howManyPlayers; i++)
	{
		players[i].Draw(aWindow);
	}
}

Config& Game::AccessConfigs()
{
	return GameConfig;
}

Game::Game(bool debug_flag)
{
	if (players.size() != howManyPlayers)
		for (size_t i = 0; i < howManyPlayers; i++)
		{
			// Creating player
			players.push_back(Player());

			players[i].setID(i);
			players[i].setRectPos(Tools::CalculatePlayerSpawnPoint(SCREENHEIGHT / 3, howManyPlayers, (float)i));
			players[i].FirstUpdate();
		}

	// Creating scene
	if (ptr_scene == nullptr)
		this->ptr_scene = std::shared_ptr<Scene>(new Scene(players));


	// Initializing GUI
	Info.resize(players.size());

	for (size_t i = 0; i < players.size(); i++)
	{
		Info[i].ID = players[i].getID();
		Info[i].HP = players[i].getPlayerHP();
		Info[i].POSITION = players[i].getRect().getPosition();
	}

	GameGUI.Init(Info);

	// Setting background music
	if (Tools::FileExist("Resources\\10_hours.wav"))
	{
		bg_music.openFromFile("Resources\\10_hours.wav");
		bg_music.setVolume(GameConfig.getVol().MUSIC);
		bg_music.play();
	}
	else Tools::DebugMessageBox("Music file not found!");
}
