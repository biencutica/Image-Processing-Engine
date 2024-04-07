#include"image.h"
#include"drawing.h"
#include<cmath>

void Drawing::drawCircle(Image& img, Point center, int radius, unsigned char color)
{
	for (int i = 0; i < img.height(); i++)
		for (int j = 0; j < img.width(); j++) {
			float dist = std::sqrt(std::pow(i - center.x, 2) + std::pow(j - center.y, 2));
			if (std::abs(dist - radius) <= 1.0f)
				img.at(i,j) = color;
		}
}

void Drawing::drawLine(Image& img, Point p1, Point p2, unsigned char color)
{
	int dist_x = abs(p2.x - p1.x);
	int dist_y = abs(p2.y - p1.y);
	int dist = sqrt(dist_x * dist_x + dist_y * dist_y);

	for (int i = 0; i < dist; i++) {
		int x = round((float)p1.x + i * ((float)p2.x - (float)p1.x) / dist);
		int y = round((float)p1.y + i * ((float)p2.y - (float)p1.y) / dist);

		unsigned char* row = img.row(y);
		row[x] = color;
	}
}

void Drawing::drawRectangle(Image& img, Rectangle r, unsigned char color)
{
	for (int i = 0; i < img.height(); i++)
		for (int j = 0; j < img.width(); j++)
			if (j >= r.x && j < r.x + r.width && i >= r.y && i < r.y + r.height)
				img.m_data[i][j] = color;
}

void Drawing::drawRectangle(Image& img, Point tl, Point br, unsigned char color)
{
	int width = abs(br.x - tl.x);
	int height = abs(br.y - tl.y);

	int x = std::min(tl.x, br.x);
	int y = std::min(tl.y, br.y);

	for (int i = y; i < y + height; i++) 
		for (int j = x; j < x + width; j++) 
			if (i >= y && i < y + height && j >= x && j < x + width) 
				img.m_data[i][j] = color;
}
