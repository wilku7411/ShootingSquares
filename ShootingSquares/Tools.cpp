#include "AllHeaders.h"

sf::Vector2f Tools::NormalizeVector(sf::Vector2f toNormalize)
{
	return (toNormalize / sqrt(pow(toNormalize.x, 2) + pow(toNormalize.y, 2)));
}

sf::Vector2f Tools::CalculatePlayerSpawnPoint(float _radius, int _numberOfPlayers, float _currentPlayer)
{
	if (_numberOfPlayers == 0)
		_numberOfPlayers = 1;

	sf::Vector2f position;
	double _phi = (360.0f / _numberOfPlayers) * (PI / 180);
	_radius = abs(_radius);
	position.x = _radius * cos((float)_phi * (_currentPlayer + 1)) + (SCREENWIDTH / 2);
	position.y = _radius * sin((float)_phi * (_currentPlayer + 1)) + (SCREENHEIGHT / 2);

	return position;
}

void Tools::DebugMessageBox(string aMessage)
{
	MessageBoxA(NULL, aMessage.c_str(), "Debug message box", MB_OK | MB_ICONINFORMATION);
}

void Tools::DebugMessageBox(int aMessage)
{
	string text = to_string(aMessage);

	MessageBoxA(NULL, text.c_str(), "Debug message box", MB_OK | MB_ICONINFORMATION);
}

void Tools::AngularMovement(sf::Vector2f& outCurrentPosition, double speed)
{
	float _radius = 0;
	sf::Vector2f Center = { SCREENWIDTH / 2, SCREENHEIGHT / 2 };

	_radius = GetMagnitude(outCurrentPosition, Center);

	float tempCos = outCurrentPosition.x / _radius;
	float tempSin = outCurrentPosition.y / _radius;

	sf::Vector2f vectorX = { 0.f, 0.f };

	float cosPhi = (outCurrentPosition.x * 1.0f + outCurrentPosition.y * 0.0f) / (_radius * 1);

	double _phi = cosPhi * speed * (PI / 180);

	outCurrentPosition.x = _radius * cos((float)_phi) + Center.x;
	outCurrentPosition.y = _radius * sin((float)_phi) + Center.y;
}

sf::Vector2f Tools::VersorToCenter(sf::Vector2f currentPosition, double speed)
{
	sf::Vector2f ThatVersor;
	speed /= 100;
	sf::Vector2f Center = { SCREENWIDTH / 2, SCREENHEIGHT / 2 };

	ThatVersor = NormalizeVector(sf::Vector2f(Center - currentPosition)) * (float)speed;

	if (ThatVersor.x > 0 && ThatVersor.y > 0 || ThatVersor.x < 0 && ThatVersor.y < 0)
		ThatVersor.x += ThatVersor.x * -1.0f;

	if (ThatVersor.x > 0 && ThatVersor.y < 0 || ThatVersor.x < 0 && ThatVersor.y > 0)
		ThatVersor.y += ThatVersor.y * -1.0f;

	return ThatVersor;
}

float Tools::GetMagnitude(sf::Vector2f vectorA, sf::Vector2f vectorB)
{
	return sqrt(pow(vectorA.x - vectorB.x, 2) + pow(vectorA.y - vectorB.y, 2));
}

bool Tools::FileExist(const std::string& path)
{
	ifstream f(path.c_str());
	return f.good();
}