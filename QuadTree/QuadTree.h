#pragma once
#include <vector>


struct Vec2
{
	Vec2(int _x, int _y)
		: x(_x), y(_y)
	{
	}

	Vec2()
	{
		x = 0;
		y = 0;
	}

	int x;
	int y;
};

class Rectangle
{
public:
	Rectangle(Vec2 _topLeft, Vec2 _bottomRight)
		: topLeft(_topLeft), bottomRight(_bottomRight)
	{
		centre = Vec2(_topLeft.x + (_bottomRight.x - topLeft.x) / 2, bottomRight.y + (topLeft.y - bottomRight.y) / 2);
	}

	Vec2 topLeft;
	Vec2 bottomRight;
	Vec2 centre;

	bool contains(Vec2 _point);
};


class QuadTree
{
public:
	QuadTree(Rectangle _boundary, int _capacity)
		: boundary(_boundary), capacity(_capacity)
	{
		NW = NULL;
		NE = NULL;
		SW = NULL;
		SE = NULL;

		subdivided = false;
	}
	Rectangle boundary;
	int capacity;

	bool subdivided;

	std::vector<Vec2> GetPointsInBounds(Rectangle _rect);

	std::vector<Vec2> points;

	QuadTree* NW;
	QuadTree* NE;
	QuadTree* SW;
	QuadTree* SE;

	void Subdivide();
	void Insert(Vec2 _point);
};