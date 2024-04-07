#include "point.h"
#include<iostream>
Point::Point(int coord_x, int coord_y)
{
	x = coord_x;
	y = coord_y;
}

std::ostream& operator<<(std::ostream& os, const Point& dt){
	os << "Point("<<dt.x << ", " << dt.y<<")"<<std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Point& dt)
{
	int x, y;
	is >> x >> y;
	dt = Point(x, y);
	return is;
}
