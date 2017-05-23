#pragma once
#include <vector>
#include <iostream>

template <class T>
class QTNode
{
private:

	// 4 children
	QTNode* mTopLeft;
	QTNode* mTopRight;
	QTNode* mBotLeft;
	QTNode* mBotRight;

	// The range of single node
	AABB mBoundry;

	// Array of results
	std::vector<QTData<T>> mObjects;

	// Arbitrary constant to indicate how many elements can be stored in this quad tree node
	static constexpr int kCapacity = 8;

	void subdivide();

public:
	QTNode<T>();
	QTNode<T>(AABB boundary);

	~QTNode();

	bool insert(QTData<T> item);
	std::vector<QTData<T>> queryRange(AABB range);
	std::vector<sf::RectangleShape> getQuadsBoundries();
};


template <class T>
QTNode<T>::QTNode()
{
	mTopLeft = nullptr;
	mTopRight = nullptr;
	mBotLeft = nullptr;
	mBotRight = nullptr;
	mBoundry = AABB();
	mObjects = std::vector<QTData<T>>();
}

template <class T>
QTNode<T>::QTNode(AABB boundary)
{
	mTopLeft = nullptr;
	mTopRight = nullptr;
	mBotLeft = nullptr;
	mBotRight = nullptr;
	this->mBoundry = boundary;
	mObjects = std::vector<QTData<T>>();
}

template <class T>
QTNode<T>::~QTNode()
{
	delete mBotRight;
	delete mBotLeft;
	delete mTopRight;
	delete mTopLeft;
}

template <class T>
void QTNode<T>::subdivide()
{
	QTPoint qSize = QTPoint(mBoundry.halfSize.x, mBoundry.halfSize.y);
	QTPoint qCenter = QTPoint(mBoundry.center.x - qSize.x, mBoundry.center.y - qSize.y);
	mTopLeft = new QTNode(AABB(qCenter, qSize));

	qCenter = QTPoint(mBoundry.center.x + qSize.x, mBoundry.center.y - qSize.y);
	mTopRight = new QTNode(AABB(qCenter, qSize));

	qCenter = QTPoint(mBoundry.center.x - qSize.x, mBoundry.center.y + qSize.y);
	mBotLeft = new QTNode(AABB(qCenter, qSize));

	qCenter = QTPoint(mBoundry.center.x + qSize.x, mBoundry.center.y + qSize.y);
	mBotRight = new QTNode(AABB(qCenter, qSize));
}

template <class T>
bool QTNode<T>::insert(QTData<T> item)
{
	if (!mBoundry.contains(item.pos))
		return false;

	if (mObjects.size() < kCapacity)
	{
		mObjects.push_back(item);
		return true;
	}

	if (mTopLeft == nullptr)
		subdivide();

	if (mTopLeft->insert(item))
		return true;

	if (mTopRight->insert(item))
		return true;

	if (mBotLeft->insert(item))
		return true;

	if (mBotRight->insert(item))
		return true;

	return false;
}

template <class T>
std::vector<QTData<T>> QTNode<T>::queryRange(AABB range)
{
	std::vector<QTData<T>> pInRange = std::vector<QTData<T>>();

	if (!mBoundry.intersects(range))
	{
		return pInRange;
	}

	for (int i = 0; i < mObjects.size(); i++)
	{
		if (range.contains(mObjects.at(i).pos))
		{
			pInRange.push_back(mObjects.at(i));
		}
	}

	if (mTopLeft == nullptr)
	{
		return pInRange;
	}

	std::vector<QTData<T>> temp = mTopLeft->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = mTopRight->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = mBotLeft->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = mBotRight->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	return pInRange;
}

template <class T>
std::vector<sf::RectangleShape> QTNode<T>::getQuadsBoundries()
{
	std::vector<sf::RectangleShape> vectorOfQuads = std::vector<sf::RectangleShape>();
	sf::RectangleShape tempRect;

	if (!mObjects.empty())
	{
		tempRect.setFillColor(sf::Color{ 0, 150, 150, 10 });

		tempRect.setSize(sf::Vector2f{
			mBoundry.halfSize.x * 2.0f,
			mBoundry.halfSize.y * 2.0f
		});

		tempRect.setPosition(sf::Vector2f{
			mBoundry.center.x - mBoundry.halfSize.x,
			mBoundry.center.y - mBoundry.halfSize.y
		});

		vectorOfQuads.push_back(tempRect);
	}

	if (mTopLeft == nullptr)
	{
		return vectorOfQuads;
	}

	std::vector<sf::RectangleShape> tempVect;
	tempVect = mTopRight->getQuadsBoundries();
	vectorOfQuads.insert(vectorOfQuads.end(), tempVect.begin(), tempVect.end());

	tempVect = mTopLeft->getQuadsBoundries();
	vectorOfQuads.insert(vectorOfQuads.end(), tempVect.begin(), tempVect.end());

	tempVect = mBotLeft->getQuadsBoundries();
	vectorOfQuads.insert(vectorOfQuads.end(), tempVect.begin(), tempVect.end());

	tempVect = mBotRight->getQuadsBoundries();
	vectorOfQuads.insert(vectorOfQuads.end(), tempVect.begin(), tempVect.end());

	return vectorOfQuads;
}