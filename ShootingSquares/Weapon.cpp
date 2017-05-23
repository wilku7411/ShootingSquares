#include "AllHeaders.h"
#include "Weapon.h"

/// Getters

std::vector<sf::RectangleShape> Weapon::getBullets()
{
	return mBullets;
}
size_t Weapon::getWeaponOwnerId() const
{
	return m_weapon_owner_id;
}

/// Setters

void Weapon::setWeaponOwnerId(size_t ownerId)
{
	m_weapon_owner_id = ownerId;
}

void Weapon::Update()
{
	if (mFirstBulletFired)
	{
		if (mBulletsShot + 1 == mMaxBullets)
			isClipEmpty = true;

		if (isClipEmpty)
			for (int i = 0; i < mMaxBullets; i++)
			{
				mBullets[i].move(Tools::NormalizeVector(mBulletDirection[i]) * mBulletSpeed);
			}
		else {
			for (int i = 0; i < mBulletsShot; i++)
			{
				mBullets[i].move(Tools::NormalizeVector(mBulletDirection[i]) * mBulletSpeed);
			}
		}
	}
}

void Weapon::Draw(sf::RenderWindow & aRenderWindow)
{
	if (mFirstBulletFired)
		for (int i = 0; i < mMaxBullets; i++)
			aRenderWindow.draw(mBullets[i]);
}

void Weapon::Shoot(const sf::Vector2f& a_player_pos, const sf::Vector2f& a_shooting_direction)
{
	if (!(CLOCK.getElapsedTime().asSeconds() >(1 / mFireRate)))
		return;

	sf::Vector2f Aim = Tools::NormalizeVector(a_shooting_direction) * 33.0f;

	if (!mFirstBulletFired) mFirstBulletFired = true;

	mLaserSound.play();

	for (int i = mBulletsShot; i < mBulletsShot + 1; i++) {
		mBulletDirection[i] = Aim;
		mBullets[i].setPosition((a_player_pos + sf::Vector2f(20.f - 5.f, 20.f - 5.f)) + Aim);
	}
	mBulletsShot = (mBulletsShot + 1) % mMaxBullets;

	CLOCK.restart();
}

Weapon::Weapon()
{
	if (Tools::FileExist("Resources\\basic_laser.wav"))
	{
		mSoundBuffer.loadFromFile("Resources\\basic_laser.wav");
		mLaserSound.setBuffer(mSoundBuffer);
		mLaserSound.setVolume(10);
	}
	else Tools::DebugMessageBox("Sound file not found!");

	for (auto&& bullet : mBullets)
	{
		bullet.setPosition(sf::Vector2f(-100.f, -100.f));
		bullet.setFillColor(sf::Color::Red);
		bullet.setSize({ 10.f,10.f });
	}
}
