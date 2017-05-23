#pragma once

class Tools
{
public:
	//Returns direction of given vector
	static sf::Vector2f NormalizeVector(sf::Vector2f toNormalize);

	// Calculates position for players (from polar coordinates to cartezian)
	static sf::Vector2f CalculatePlayerSpawnPoint(float _radius, int _numberOfPlayers, float _currentPlayer);

	// Debug message box (2 overloads)

	static void DebugMessageBox(std::string aMessage);
	static void DebugMessageBox(int aMessage);

	// Moves over arc towards center			[UNDONE - final effect wasn't something that I wanted to achieve]
	static void AngularMovement(sf::Vector2f& outCurrentPosition, double speed);

	// Move towards center						[UNDONE - final effect wasn't something that I wanted to achieve]
	static sf::Vector2f VersorToCenter(sf::Vector2f currentPosition, double speed);

	// Calculates distance between two given vectors
	static float GetMagnitude(sf::Vector2f endPoint, sf::Vector2f startPoint);

	// Used to check if file of given path exist
	static bool FileExist(const std::string& path);
};