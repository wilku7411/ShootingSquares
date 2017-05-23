#include"AllHeaders.h"

// Getters
sf::Uint32 Controller::getID() const
{
	return joystickId;
}
sf::Vector2f Controller::getCurrentJoystickXY() const
{
	return currentJoystickXY;
}
sf::Vector2f Controller::getCurrentJoystickUR() const
{
	return currentJoystickUR;
}
float Controller::getCurrentJoystickZ() const
{
	return currentJoystickZ;
}
float Controller::getAxisTolerance() const
{
	return axisTolerance;
}
float Controller::getSensitivity() const
{
	return sensitivity;
}

/// Setters
void Controller::setID(sf::Uint32 a_id)
{
	if (a_id >= 0)
		joystickId = a_id;
}
void Controller::setCurrentJoystickXY(sf::Vector2f a_XY)
{
	currentJoystickXY = a_XY;
}
void Controller::setCurrentJoystickUR(sf::Vector2f a_UR)
{
	currentJoystickUR = a_UR;
}
void Controller::setCurrentJoystickZ(float a_Z)
{
	currentJoystickZ = a_Z;
}
void Controller::setAxisTolerance(float a_tolerance)
{
	axisTolerance = std::abs(a_tolerance);
}
void Controller::setSensitivity(float a_sensitivity)
{
	sensitivity = std::abs(a_sensitivity);
}

/// Methods

// Movement according to joystick input
void Controller::Move(sf::RectangleShape& a_player)
{
	if (
		axisTolerance < currentJoystickXY.x
		|| currentJoystickXY.x < -axisTolerance
		|| axisTolerance < currentJoystickXY.y
		|| currentJoystickXY.y < -axisTolerance
		)
		a_player.move(currentJoystickXY / sensitivity);
}

bool Controller::AllowedToShoot()
{
	if (
		axisTolerance < currentJoystickUR.x
		|| currentJoystickUR.x < -axisTolerance
		|| axisTolerance < currentJoystickUR.y
		|| currentJoystickUR.y < -axisTolerance
		)
		return true;

	return false;
}

// Called every tick
void Controller::Update()
{
	currentJoystickXY = { sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Axis::X) , sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Axis::Y) };
	currentJoystickUR = { sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Axis::U) , sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Axis::R) };
	currentJoystickZ = { sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Axis::Z) };
}