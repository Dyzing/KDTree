#pragma once
#include <iostream>
#include <vector>
#include <string>


class Point
{
private:
	std::string pointName;
	std::vector<int> coord;
	int nb_dim;

public:
	Point(int const& nb_d);
	~Point();
	Point(std::string const & pn, std::vector<int> const& c, int const & nb_d);

	std::string getPointName() const { return pointName; };
	void setPointName(std::string const & s);
	std::vector<int> getCoord() const{ return coord; };
	void setCoord(std::vector<int> const& new_coord);
	bool isPointEquals(Point const& p2) const;
	Point& operator=(Point const& p);
};

