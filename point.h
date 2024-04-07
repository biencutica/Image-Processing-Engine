#pragma once
#include"image.h"
class Point {
	friend class Image;
	friend class Rectangle;
public:
	Point() { x = 0, y = 0; }
	Point(int coord_x, int coord_y);

	friend std::ostream& operator<<(std::ostream& os, const Point& dt);
	friend std::istream& operator>>(std::istream& is, const Point& dt);

	int x, y;
};