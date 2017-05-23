#pragma once
class Controller
{
private:
	sf::Uint32 joystickId = 0;
	sf::Vector2f currentJoystickXY{ 0.f,0.f };
	sf::Vector2f currentJoystickUR{ 0.f,0.f };
	float currentJoystickZ = 0;

	float axisTolerance = 20.f;
	float sensitivity = 20.f;

public:

	/// Getters

	sf::Uint32 getID() const;
	sf::Vector2f getCurrentJoystickXY() const;
	sf::Vector2f getCurrentJoystickUR() const;
	float getCurrentJoystickZ() const;
	float getAxisTolerance() const;
	float getSensitivity() const;

	/// Setters

	void setID(sf::Uint32 a_id);
	void setCurrentJoystickXY(sf::Vector2f a_XY);
	void setCurrentJoystickUR(sf::Vector2f a_UR);
	void setCurrentJoystickZ(float a_Z);
	void setAxisTolerance(float a_tolerance);
	void setSensitivity(float a_sensitivity);

	/// Methods

	// Movement according to joystick input
	void Move(sf::RectangleShape& a_player);

	// Returns true if right analog stick is moved more than float axisTolerance
	// Created because even untouched analog stick caused minimal movement 
	bool AllowedToShoot();

	/// All updates

	void Update();
};

