#pragma once
#include"point.h"
#include"image.h"

class Rectangle {
	friend class Image;
	friend class Point;
public:
	Rectangle() { x = 0, y = 0, width = 0, height = 0; }
	Rectangle(int coord_x, int coord_y, int w, int h);
	Rectangle(Point top_left, Point bottom_right);

	friend std::ostream& operator<<(std::ostream& os, const Rectangle& dt);
	friend std::istream& operator>>(std::istream& is, Rectangle& dt);

	Rectangle operator+(const Rectangle& r);
	Rectangle operator-(const Rectangle& r);
	Rectangle operator&(const Rectangle& r);
	Rectangle operator|(const Rectangle& r);

	int x, y;
	int width, height;
};