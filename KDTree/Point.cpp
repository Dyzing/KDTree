#include "Point.h"

Point::Point()
{
}

Point::~Point()
{
	pointName = "";
	coord.clear();
}

Point::Point(std::string const& pn, std::vector<int>const& c)
	: pointName(pn) ,coord(c)
{
}

bool Point::isPointEquals(Point const& p2) const
{
	return std::equal(coord.begin(), coord.end(), p2.getCoord().begin());
}

