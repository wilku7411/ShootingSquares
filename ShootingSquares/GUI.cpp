#include "AllHeaders.h"

void GUI::Init(std::vector<GUI_INFO>& allplayers)
{
	all_players_info.resize(allplayers.size());

	for (size_t i = 0; i < all_players_info.size(); i++)
	{
		all_players_info[i] = allplayers[i];
	}

	for (size_t i = 0; i < all_players_info.size(); i++)
	{
		sf::RectangleShape tmp_rect_frame;
		sf::RectangleShape tmp_rect;

		anchorToPlayer.push_back(sf::Vector2f(0.f, 0.f));

		all_players_info[i].HEALTH_BAR_FRAME.setSize(sf::Vector2f(100.0f, 10.0f));
		all_players_info[i].HEALTH_BAR_FRAME.setOutlineThickness(2.0f);
		all_players_info[i].HEALTH_BAR_FRAME.setOutlineColor(sf::Color::White);
		all_players_info[i].HEALTH_BAR_FRAME.setFillColor(sf::Color::Transparent);

		all_players_info[i].HEALTH_BAR.setOutlineThickness(2.0f);
		all_players_info[i].HEALTH_BAR.setOutlineColor(sf::Color::White);
		all_players_info[i].HEALTH_BAR.setFillColor(sf::Color::Green);
	}
}

void GUI::Draw(sf::RenderWindow &aWindow)
{
	for (size_t i = 0; i < all_players_info.size(); i++)
	{
		aWindow.draw(all_players_info[i].HEALTH_BAR);
		aWindow.draw(all_players_info[i].HEALTH_BAR_FRAME);
	}
}

void GUI::Update(std::vector<GUI_INFO>& players)
{
	for (size_t i = 0; i < all_players_info.size(); i++)
	{
		all_players_info[i].HP = players[i].HP;
		all_players_info[i].POSITION = players[i].POSITION;

		all_players_info[i].HEALTH_BAR_FRAME.setPosition(sf::Vector2f(all_players_info[i].POSITION.x - 25.f, all_players_info[i].POSITION.y - 40));

		all_players_info[i].HEALTH_BAR.setPosition(sf::Vector2f(all_players_info[i].POSITION.x - 25.f, all_players_info[i].POSITION.y - 40));
		all_players_info[i].HEALTH_BAR.setSize(sf::Vector2f(all_players_info[i].HP, 10.0f));
	}
}

GUI::GUI()
{
	mFont.loadFromFile("consola.ttf");
	mScoreText.setFont(mFont);
}