#pragma once
#include"image.h"
#include"rectangle.h"
#include"point.h"

class Drawing {
	friend class Image;
	friend class Point;
	friend class Rectangle;
public:
	Drawing() {}
	void drawCircle(Image& img, Point center, int radius, unsigned char color);
	void drawLine(Image& img, Point p1, Point p2, unsigned char color);
	void drawRectangle(Image& img, Rectangle r, unsigned char color);
	void drawRectangle(Image& img, Point tl, Point br, unsigned char color);
};