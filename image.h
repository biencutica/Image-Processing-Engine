#pragma once
#include<iostream>
#include"rectangle.h"
#include"point.h"
#include"drawing.h"

class Image
{
public:
    friend class Drawing;
    Image();
    Image(unsigned int w, unsigned int h);
    Image(const Image& other); //copy constructor

    ~Image();

    bool load(std::string imagePath);
    bool save(std::string imagePath);

    Image& operator=(const Image& other); //assignment operator

    Image operator+(const Image& i);
    Image operator-(const Image& i);
    Image operator*(const Image& i);

    Image operator+(unsigned int scalar);
    Image operator-(unsigned int scalar);
    Image operator*(unsigned int scalar);

    bool getROI(Image& roiImg, Rectangle roiRect);
    bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

    bool isEmpty() const;


    unsigned int width() const;
    unsigned int height() const;

    unsigned char& at(unsigned int x, unsigned int y);
    unsigned char& at(Point pt);

    unsigned char* row(int y);

    void release();

    friend std::ostream& operator<<(std::ostream& os, const Image& dt);
    friend std::istream& operator>>(std::istream& is, Image& dt);

    static Image zeros(unsigned int width, unsigned int height);
    static Image ones(unsigned int width, unsigned int height);

protected:
    unsigned char** m_data;
    unsigned int m_width;
    unsigned int m_height;
};

class Size {
    friend class Image;
public:
    Size() { width = 0, height = 0; }
    Size(unsigned int w, unsigned int h) { width = w, height = h; }
protected:
    unsigned int width;
    unsigned int height;

};