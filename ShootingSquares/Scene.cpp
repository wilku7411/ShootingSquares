#include "AllHeaders.h"

// Getters 
size_t Scene::getNumberOfEntities() const
{
	return _MAX;
}
size_t Scene::getPickUpsQuantity() const
{
	return _P;
}
size_t Scene::getKillersQuantity() const
{
	return _K;
}
auto Scene::getPickUpsRef() const
{
	return &mPickups;
}
auto Scene::getKillersRef() const
{
	return &mKillers;
}
auto Scene::getPickUpsCollidersRef() const
{
	return &mPickupsColliders;
}
auto Scene::getKillersCollidersRef() const
{
	return &mKillersColliders;
}

/// Initializers

void Scene::Init()
{
	_P = rand() % _MAX + 1;
	_K = rand() % _MAX + 1;

	for (size_t i = 0; i < _P; i++)
	{
		mPickups.push_back(PickUp());
		mPickupsColliders.push_back(*(mPickups[i].getCollider()));
	}
	for (size_t i = 0; i < _K; i++)
	{
		mKillers.push_back(Killer());
		mKillersColliders.push_back(*(mKillers[i].getCollider()));
	}

	for (size_t i = 0; i < NumberOfStars; i++)
	{
		Stars.push_back(sf::CircleShape(1.f));

		int x = std::rand() % SCREENWIDTH;
		int y = std::rand() % SCREENHEIGHT;

		int stars_opacity = rand() % 255;

		Stars[i].setPosition((float)x, (float)y);
		Stars[i].setFillColor(sf::Color(255, 255, 255, stars_opacity));
	}
}

void Scene::SetupPlayer(std::vector<Player>& a_player)
{
	ptr_player = a_player;
}

/// Updates

void Scene::Update()
{
	for (auto item : mPickups)
		item.Update();

	for (auto item : mKillers)
		item.Update();


	ptr_player[0].getRect().setFillColor(sf::Color::Blue);
	CheckInteractionBetweenEntities();
}

void Scene::UpdateBackground()
{
	// TODO sparkling
}

/// Methods

void Scene::Draw(sf::RenderWindow& aWindow)
{
	if (DEBUG)
	{
		for (auto&& quad : quads)
		{
			aWindow.draw(quad);
		}
	}

	for (size_t i = 0; i < _P; i++)
	{
		aWindow.draw(*(mPickups[i].getBody()));
		aWindow.draw(*(mPickups[i].getItemSprite()));
	}
	for (size_t i = 0; i < _K; i++)
	{
		aWindow.draw(*(mKillers[i].getBody()));
		aWindow.draw(*(mKillers[i].getItemSprite()));
	}

	for (size_t i = 0; i < NumberOfStars; i++)
	{
		aWindow.draw(Stars[i]);
	}
}

void Scene::CheckInteractionBetweenEntities()
{
	/*

	Test:
	Checking if I can use QuadTree to check collisions between moivng objects.
	The idea is to:
	-insert data into QT											DONE
	-check collisions by query range								DONE
	-dispose QT														DONE

	This operation will be executed about once every 1-3 frames		UNDONE

	Implement scoring for players that hit other players			UNDONE

	*/



	// Preparing vector of all items taken under consideration in quadtree
	std::vector<QTData<AABB>> qtDataVector;
	std::vector<AABB> boundingBoxes;

	// Creating data based on every bullet of every player
	for (auto&& player : ptr_player)
	{
		int i = 0;
		for (auto&& bullet : player.getWeapon().getBullets())
		{
			QTPoint center =
			{
				bullet.getPosition().x + bullet.getSize().x / 2.0f,
				bullet.getPosition().y + bullet.getSize().y / 2.0f
			};

			QTPoint halfSize =
			{
				bullet.getSize().x / 2.0f,
				bullet.getSize().y / 2.0f
			};

			boundingBoxes.push_back(AABB{ center, halfSize });

			QTData<AABB> item = { center, &boundingBoxes[i], player.getID() };

			qtDataVector.push_back(item);
			++i;
		}
	}

	// Preparing quadtree
	QTNode<AABB> quadTree =
	{
		AABB
	{
		QTPoint{ (float)SCREENWIDTH / 2.0f, (float)SCREENHEIGHT / 2.0f },
		QTPoint{ (float)SCREENWIDTH / 2.0f, (float)SCREENHEIGHT / 2.0f }
	}
	};

	for (auto&& item : qtDataVector)
	{
		quadTree.insert(item);
	}

	// Preparing a vector that will contain all the query resaults (bullets that may overlap players).
	std::vector<QTData<AABB>> queryResaults;

	for (auto&& player : ptr_player)
	{
		AABB playersAABB =
		{
			QTPoint
		{
			player.getRect().getSize().x / 2.0f + player.getRect().getPosition().x,
			player.getRect().getSize().y / 2.0f + player.getRect().getPosition().y
		},
			QTPoint
		{
			player.getRect().getSize().x / 2.0f,
			player.getRect().getSize().y / 2.0f
		}
		};

		queryResaults = quadTree.queryRange(playersAABB);

		quads = quadTree.getQuadsBoundries();

		for (auto&& bullet : queryResaults)
		{
			if (player.getID() != bullet.id)
				player.TakeDmg(1.0f);
		}
	}



	for (size_t i = 0, ii = 1; i < ptr_player.size(); i++, ii--)
	{
		for (size_t j = 0; j < _K; j++)
		{
			if (ptr_player[i].getPlayerCollider()->Collides(mKillers[j].getCollider()))
			{
				ptr_player[i].TakeDmg(20.f);
				mKillers[j].getBody()->setPosition(-1000.f, -1000.f);
			}
		}
		for (size_t j = 0; j < _P; j++)
		{
			if (ptr_player[i].getPlayerCollider()->Collides(mPickups[j].getCollider()))
			{
				ptr_player[i].Heal(5.f);
				mPickups[j].getBody()->setPosition(-1000.f, -1000.f);
			}
		}

		/* Disabled for testing purposes
		* bruteforce collision checks

		Weapon tmp_weapon = ptr_player[ii].getWeapon();

		for (size_t j = 0; j < tmp_weapon.getBullets().size(); j++)
		{
		if (ptr_player[i].getPlayerCollider()->Collides(tmp_weapon.getBullets()[j]))
		ptr_player[i].TakeDmg(10.f);

		}
		*/
	}

}

// Default ctor for scene with items only (without players)
Scene::Scene() : ptr_player(std::vector<Player>(1))
{
	Scene::Init();
}

// Constructor overload for vector of players
Scene::Scene(std::vector<Player>& a_player_ref) : ptr_player(a_player_ref)
{
	ptr_player = a_player_ref;

	Scene::Init();
}

