#include "rectangle.h"

Rectangle::Rectangle(int coord_x, int coord_y,int w, int h)
{
	x = coord_x;
	y = coord_y;
	width = w;
	height = h;
}

Rectangle::Rectangle(Point top_left, Point bottom_right)
{
	width = bottom_right.x - top_left.x;
	height = bottom_right.y - top_left.y;	
}

std::ostream& operator<<(std::ostream& os, const Rectangle& dt) {
	os << "Rectangle(" << dt.x << ", " << dt.y << ") with resolution " << dt.width << ":" << dt.height << ".";
	return os;
}

std::istream& operator>>(std::istream& is, Rectangle& dt) {
	int x, y, w, h;
	is >> x >> y >> w >> h;
	dt = Rectangle(x, y, w, h);
	return is;
}

Rectangle Rectangle::operator+(const Rectangle& r)
{
	Rectangle rec = Rectangle();
	rec.x = std::min(x, r.x);
	rec.y = std::min(y, r.y);
	int right = std::max(x + width, r.x + r.width);
	int bottom = std::max(y + height, r.y + r.height);
	rec.width = right - rec.x;
	rec.height = bottom - rec.y;
	return rec;
}

Rectangle Rectangle::operator-(const Rectangle& r)
{
	Rectangle rec = Rectangle();
	rec.x = x - r.x;
	rec.y = y - r.y;
	rec.height = height - r.height;
	rec.width = width - r.width;

	return rec;
}

Rectangle Rectangle::operator&(const Rectangle& r)
{
	if (width == 0 || height == 0 || r.width == 0 || r.height == 0)
		return Rectangle();
	if (x > r.x + r.width || r.x > x + width)
		return Rectangle();
	if (y - height > r.y || r.y - r.height > y)
		return Rectangle();

	int x1 = std::max(x, r.x);
	int x2 = std::min(x + width, r.x + r.width);
	int y1 = std::min(y, r.y);
	int y2 = std::max(y - height, r.y - r.height);

	return Rectangle(x1, y1, x2 - x1, y1 - y2);
}

Rectangle Rectangle::operator|(const Rectangle& r)
{
	int min_x = std::min(x, r.x);
	int min_y = std::min(y, r.y);
	int max_x = std::max(x + width, r.x + r.width);
	int max_y = std::max(y - height, r.y - r.height);

	Rectangle rec = Rectangle();
	rec.x = min_x;
	rec.y = min_y;
	rec.width = max_x - min_x;
	rec.height = max_y - min_y;

	return rec;
}
