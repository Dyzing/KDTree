#pragma once
#include <iostream>
#include <vector>
#include <string>

class Point
{
private:
	std::string pointName;
	std::vector<int> coord;


public:
	Point();
	~Point();
	Point(std::string const & pn, std::vector<int> const& c);

	std::string getPointName() const { return pointName; };
	std::vector<int> getCoord() const{ return coord; };
	bool isPointEquals(Point const& p2) const;
};

