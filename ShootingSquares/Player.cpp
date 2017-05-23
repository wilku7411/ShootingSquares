#include "AllHeaders.h"

/// Getters
const Player* Player::getRefToPlayer() const
{
	return this;
}
sf::RectangleShape Player::getRect()
{
	return mRect;
}
std::shared_ptr<BoxCollider> Player::getPlayerCollider() const
{
	return mRectCollider;
}
int Player::getID()
{
	return mId;
}
float Player::getPlayerHP() const
{
	return mPlayerHP;
}
Weapon Player::getWeapon() const
{
	return mPlayerWeapon;
}


/// Setters
void Player::setRectPos(sf::Vector2f aPos)
{
	mRect.setPosition(aPos);
}
void Player::setID(int aID)
{
	mId = aID;
	m_controller.setID(mId);
	if (mPlayerWeapon.getWeaponOwnerId() != mId)
		mPlayerWeapon.setWeaponOwnerId(mId);
}
void Player::setPlayerHP(float aHP)
{
	mPlayerHP = aHP;
}


/// Methods

void Player::PlayerController()
{
	if (!inDebug)
	{
		// Movements 
		if (mPassableWalls && (mTouchedWall != TouchedBorder::NONE))
			mRect.setPosition(mTeleportationPoint);

		m_controller.Move(mRect);

		// Shooting 
		if (m_controller.AllowedToShoot() && m_controller.getCurrentJoystickZ() > 0.5f)
			mPlayerWeapon.Shoot(mRect.getPosition(), m_controller.getCurrentJoystickUR());
	}
	else
	{
		mRect.setPosition((sf::Vector2f)sf::Mouse::getPosition());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mPlayerWeapon.Shoot(mRect.getPosition(), sf::Vector2f(10.f, 0.f));
		}
	}
}

// Does not allow player to get out of screen boundries
void Player::CheckMapBorders(bool aPassableWalls)
{
	mRectCenter = sf::Vector2f(mRect.getPosition().x + mRect.getSize().x / 2.0f, mRect.getPosition().y + mRect.getSize().y / 2.0f);

	mPassableWalls = aPassableWalls;
	mTouchedWall = TouchedBorder::NONE;

	if (mRectCenter.x <= 0)
	{
		if (!mPassableWalls) mRect.setPosition({ 0.0f, mRect.getPosition().y });
		mTouchedWall = TouchedBorder::LEFT;
		mTeleportationPoint = { SCREENWIDTH - mRect.getSize().x, mRect.getPosition().y };
		return;
	}

	if (mRectCenter.x >= SCREENWIDTH)
	{
		if (!mPassableWalls) mRect.setPosition({ SCREENWIDTH - mRect.getSize().x, mRect.getPosition().y });
		mTouchedWall = TouchedBorder::RIGHT;
		mTeleportationPoint = { 0.0f, mRect.getPosition().y };
		return;
	}

	if (mRectCenter.y <= 0)
	{
		if (!mPassableWalls) mRect.setPosition({ mRect.getPosition().x, 0.0f });
		mTouchedWall = TouchedBorder::TOP;
		mTeleportationPoint = { mRect.getPosition().x, SCREENHEIGHT - mRect.getSize().y };
		return;
	}

	if (mRectCenter.y >= SCREENHEIGHT)
	{
		if (!mPassableWalls) mRect.setPosition({ mRect.getPosition().x, SCREENHEIGHT - mRect.getSize().y });
		mTouchedWall = TouchedBorder::BOTTOM;
		mTeleportationPoint = { mRect.getPosition().x, 0.0f };
		return;
	}


}

void Player::Draw(sf::RenderWindow& aRenderWindow)
{
	aRenderWindow.draw(mRect);
	mPlayerWeapon.Draw(aRenderWindow);
}

// Decreases player HP
void Player::TakeDmg(float hpDecrease)
{
	if (mPlayerHP > 1)
		if (mPlayerHP - hpDecrease <= 0)
			this->mPlayerHP = 0;
		else
			this->mPlayerHP -= hpDecrease;
}

// Increases player HP
void Player::Heal(float hpIncrease)
{
	if (mPlayerHP < 100)
		if (mPlayerHP + hpIncrease >= 100.f)
			this->mPlayerHP = 100.f;
		else
			this->mPlayerHP += hpIncrease;
}

/// Updates

void Player::FirstUpdate()
{
	mPreviousPosition.x = mRect.getPosition().x - 20.0f;
	mPreviousPosition.y = mRect.getPosition().y;

	mRectCollider = std::shared_ptr<BoxCollider>(new BoxCollider(mRect.getPosition() - mColliderOffset, mRect.getSize() + 2.0f * mColliderOffset));
	mTeleportationPoint = mRect.getPosition();
}

void Player::Update()
{
	m_controller.Update();
	CheckMapBorders(true);

	PlayerController();
	UpdateSpeed();
	mRectCollider->Update(mRect.getPosition() - mColliderOffset);
	mPlayerWeapon.Update();
}

void Player::UpdateSpeed()
{
	m_speed = mRect.getPosition() - mPreviousPosition;
	mPreviousPosition = mRect.getPosition();
}

// Constructor
Player::Player()
{
	mRect.setSize(sf::Vector2f(40.f, 40.f));
	mRect.setFillColor(sf::Color::Green);
}
