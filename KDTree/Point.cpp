#include "Point.h"


Point::Point(int const& nb_d)
	: nb_dim(nb_d)
{
}

Point::~Point()
{
	pointName = "";
	if(coord.size() <= nb_dim)
		coord.clear();
	else
	{
		coord.resize(nb_dim);
		coord.clear();
	}
}

Point::Point(std::string const& pn, std::vector<int>const& c, int const & nb_d)
	: pointName(pn) ,coord(c), nb_dim(nb_d)
{
}

void Point::setPointName(std::string const& s)
{
	pointName = s;
}

void Point::setCoord(std::vector<int> const& new_coord)
{
	coord = new_coord;
}

bool Point::isPointEquals(Point const& p2) const
{
	return std::equal(coord.begin(), coord.end(), p2.getCoord().begin());
}

Point& Point::operator=(Point const& p)
{
	this->pointName = p.pointName;
	this->coord = p.coord;
	this->nb_dim = p.nb_dim;
	return *this;
}

