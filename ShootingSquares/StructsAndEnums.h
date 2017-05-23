#pragma once


struct RESOLUTION
{
	int WIDTH = 1920;
	int HEIGHT = 1200;
};


struct VOLUME
{
	float MUSIC = 20;
	float EFFECTS = 20;
};


struct GUI_INFO
{
	int ID = 0;
	float HP = 0;
	sf::Vector2f POSITION = { 0.f, 0.f };
	sf::RectangleShape HEALTH_BAR;
	sf::RectangleShape HEALTH_BAR_FRAME;

	GUI_INFO() {};
	void GUI_INIT(int id, float hp, sf::Vector2f pos, sf::RectangleShape hpBar, sf::RectangleShape hpBarFrame)
	{
		ID = id;
		HP = hp;
		POSITION = pos;
		HEALTH_BAR = hpBar;
		HEALTH_BAR_FRAME = hpBarFrame;
	};
};


struct QTPoint
{
	float x, y;
	QTPoint(float x = 0, float y = 0) :x(x), y(y) {};
};


struct AABB
{
	QTPoint center;
	QTPoint halfSize;

	AABB(QTPoint center = QTPoint(), QTPoint halfSize = QTPoint()) : center(center), halfSize(halfSize) {};

	bool contains(const QTPoint& a) const
	{
		if (a.x < center.x + halfSize.x && a.x > center.x - halfSize.x)
		{
			if (a.y < center.y + halfSize.y && a.y > center.y - halfSize.y)
			{
				return true;
			}
		}
		return false;
	}

	bool intersects(const AABB& other) const
	{
		if (center.x + halfSize.x > other.center.x - other.halfSize.x || center.x - halfSize.x < other.center.x + other.halfSize.x)
		{
			if (center.y + halfSize.y > other.center.y - other.halfSize.y || center.y - halfSize.y < other.center.y + other.halfSize.y)
			{
				return true;
			}
		}
		return false;
	}
};


template <typename T>
struct QTData
{
	QTPoint pos;
	T* load;
	int id;

	QTData(QTPoint pos = QTPoint(), T* data = nullptr, int aId = -1) : pos(pos), load(data), id(aId) {};
};

