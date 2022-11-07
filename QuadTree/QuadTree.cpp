#include "QuadTree.h"


int main(int argc, char** argv)
{
	Rectangle boundary = Rectangle(Vec2(0, 100), Vec2(100, 0));
	QuadTree* QT = new QuadTree(boundary, 1);
 	
	QT->Insert(Vec2(10, 10)); // ROOT (South West)
	QT->Insert(Vec2(70, 70)); // North East
	QT->Insert(Vec2(20, 40)); // South West
	QT->Insert(Vec2(10, 60)); // North West
	QT->Insert(Vec2(20, 10)); // South West - South West
	QT->Insert(Vec2(70, 90)); // North East - North West

	Rectangle SouthWest(Vec2(0, 50), Vec2(50, 0)); // South West

	std::vector<Vec2> PointInBounds = QT->GetPointsInBounds(SouthWest);

}

std::vector<Vec2> QuadTree::GetPointsInBounds(Rectangle _rect)
{
	std::vector<Vec2> returnArray;
	if (points.size() > 0)
	{
		for (int i{}; i < points.size(); i++)
		{
			if (_rect.contains(points[i]))
			{
				returnArray.push_back(points[i]);
			}
		}
		if (NW != NULL)
		{
			if (_rect.contains(NW->boundary.centre))
			{
				std::vector<Vec2> NWArray = NW->GetPointsInBounds(_rect);
				for (int i{}; i < NWArray.size(); i++)
				{
					returnArray.push_back(NWArray[i]);
				}
			}
		}
		if (NE != NULL)
		{
			if (_rect.contains(NE->boundary.centre))
			{
				std::vector<Vec2> NEArray = NE->GetPointsInBounds(_rect);
				for (int i{}; i < NEArray.size(); i++)
				{
					returnArray.push_back(NEArray[i]);
				}
			}
		}
		if (SW != NULL)
		{
			if (_rect.contains(SW->boundary.centre))
			{
				std::vector<Vec2> SWArray = SW->GetPointsInBounds(_rect);
				for (int i{}; i < SWArray.size(); i++)
				{
					returnArray.push_back(SWArray[i]);
				}
			}
		}
		if (SE != NULL)
		{
			if (_rect.contains(SE->boundary.centre))
			{
				std::vector<Vec2> SEArray = SE->GetPointsInBounds(_rect);
				for (int i{}; i < SEArray.size(); i++)
				{
					returnArray.push_back(SEArray[i]);
				}
			}
		}
	}
	

	return returnArray;
}

void QuadTree::Subdivide()
{
	Rectangle NorthWest = Rectangle(boundary.topLeft,																	// TopLeft
		Vec2(boundary.topLeft.x + (boundary.bottomRight.x - boundary.topLeft.x) / 2, boundary.bottomRight.y + (boundary.topLeft.y - boundary.bottomRight.y) / 2));	// BottomRight
	NW = new QuadTree(NorthWest, capacity);

	Rectangle NorthEast = Rectangle(Vec2(boundary.topLeft.x + (boundary.bottomRight.x - boundary.topLeft.x) / 2, boundary.topLeft.y),		// TopLeft
		Vec2(boundary.bottomRight.x, boundary.bottomRight.y + (boundary.topLeft.y - boundary.bottomRight.y) / 2));								// BottomRight
	NE = new QuadTree(NorthEast, capacity);

	Rectangle SouthWest = Rectangle(Vec2(boundary.topLeft.x, boundary.bottomRight.y + (boundary.topLeft.y - boundary.bottomRight.y) / 2),		// TopLeft
		Vec2(boundary.topLeft.x + (boundary.bottomRight.x - boundary.topLeft.x) / 2, boundary.bottomRight.y));								// BottomRight
	SW = new QuadTree(SouthWest, capacity);

	Rectangle SouthEast = Rectangle(Vec2(boundary.topLeft.x + (boundary.bottomRight.x - boundary.topLeft.x) / 2, boundary.bottomRight.y + (boundary.topLeft.y - boundary.bottomRight.y) / 2),		// TopLeft
		boundary.bottomRight);							// BottomRight
	SE = new QuadTree(SouthEast, capacity);

	subdivided = true;
}

void QuadTree::Insert(Vec2 _point)
{
	if (!boundary.contains(_point))
	{
		return;
	}


	if (points.size() < capacity)
	{
		points.push_back(_point);
		return;
	}
	else
	{
		if (!subdivided)
		{
			Subdivide();
		}
	}

	NW->Insert(_point);
	NE->Insert(_point);
	SW->Insert(_point);
	SE->Insert(_point);
}

bool Rectangle::contains(Vec2 _point)
{
	return (_point.x >= topLeft.x && _point.x <= bottomRight.x
			&& _point.y >= bottomRight.y && _point.y <= topLeft.y);
}
