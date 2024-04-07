#include<iostream>
#include<fstream>
#include "image.h"
#include "point.h"
#include "rectangle.h"
Image::Image()
{
	m_width = 0;
	m_height = 0;
	m_data = nullptr;
}

Image::Image(unsigned int w, unsigned int h)
{
	m_width = w;
	m_height = h;
	m_data = new unsigned char* [m_height];
	for (unsigned int i = 0; i < m_height; i++)
		m_data[i] = new unsigned char[m_width];
}

Image::Image(const Image& other)
{
	m_height = other.m_height;
	m_width = other.m_width;
	m_data = new unsigned char*[other.m_height];
	for (unsigned int i = 0; i < m_height; i++)
		m_data[i] = new unsigned char[m_width];
	for (unsigned int i = 0; i < m_height; i++)
		for (unsigned int j = 0; j < m_width; j++)
			m_data[i][j] = other.m_data[i][j];
}

/*Image::Image(Size size)
{
	m_width = size.width;
	m_height = size.height; 
		m_data = new unsigned char* [m_height];
		for (unsigned int i = 0; i < m_height; i++)
			m_data[i] = new unsigned char[m_width];
}*/

Image::~Image()
{
	release();
}

bool Image::load(std::string imagePath)
{
	std::ifstream file(imagePath, std::ios::binary);
	if (!file) {
		std::cerr << "Cannot open: " << imagePath << std::endl;
		return false;
	}

	std::string type;
	file >> type;
	if (type != "P2")
	{
		std::cerr << "Unsupported PGM file: " << imagePath << std::endl;
		file.close();
		return false;
	}

	if (m_width == 0 && m_height == 0)
		file >> m_width >> m_height;

	unsigned int mx = 0;
	file >> mx;
	if (mx > 255)
		mx = 255;
	if (mx < 0)
		mx = 0;
	
	m_data = new unsigned char* [m_height];
	for (unsigned int i = 0; i < m_height; i++)
		m_data[i] = new unsigned char[m_width];

	for (unsigned int i = 0; i < m_height; i++)
		file.read(reinterpret_cast<char*>(m_data[i]), m_width);

	file.close();
	return true;
}

bool Image::save(std::string imagePath)
{
	std::ofstream file(imagePath, std::ios::binary);
	if (!file.is_open()){
		std::cerr << "Cannot open: " << imagePath << std::endl;
		return false;
	}
	std::cout << m_width;
	std::cout << m_height;
	file << "P2\n" << m_width << " " << m_height << "\n255\n";

	for (unsigned int i = 0; i < m_height; i++) {
		for (unsigned int j = 0; j < m_width; j++)
			file << (int)m_data[i][j] << " ";
		file << std::endl;
	}

	file.close();
	return true;
}

Image& Image::operator=(const Image& other)
{
	if (this == &other)
		return *this;
	for(int i = 0;i < this->m_height;i++)
		delete[] this->m_data[i];
	delete[] this->m_data;

	this->m_width = other.m_width;
	this->m_height = other.m_height;

	this->m_data = new unsigned char* [this->m_height];
	for (unsigned int i = 0; i < this->m_height; i++)
		this->m_data[i] = new unsigned char[this->m_width];
	for (unsigned int i = 0; i < this->m_height; i++)
		for (unsigned int j = 0; j < this->m_width; j++)
			this->m_data[i][j] = other.m_data[i][j];

	return *this;

}

Image Image::operator+(const Image& i)
{
	if (m_width == i.m_width && m_height == i.m_height) {
		Image img = Image{ m_width,m_height };
		for (unsigned int x = 0; x < m_height; x++)
			for (unsigned int j = 0; j < m_width; j++)
				img.m_data[x][j] = m_data[x][j] + i.m_data[x][j];

		return img;
	}
	else
		return *this;
}

Image Image::operator-(const Image& i)
{
	if (m_width == i.m_width && m_height == i.m_height) {
		Image img = Image{ m_width,m_height };
		for (unsigned int x = 0; x < m_height; x++)
			for (unsigned int j = 0; j < m_width; j++)
				img.m_data[x][j] = m_data[x][j] - i.m_data[x][j];

		return img;
	}
	else
		return *this;
}

Image Image::operator*(const Image& i)
{
	if (m_width == i.m_width && m_height == i.m_height) {
		Image img = Image{ m_width,m_height };
		for (unsigned int x = 0; x < m_height; x++)
			for (unsigned int j = 0; j < m_width; j++)
				img.m_data[x][j] = m_data[x][j] * i.m_data[x][j];

		return img;
	}
	else
		return *this;
}

Image Image::operator+(unsigned int scalar)
{
	Image img = Image{ m_width, m_height };
	for (unsigned int x = 0; x < m_height; x++)
		for (unsigned int j = 0; j < m_width; j++)
			img.m_data[x][j] = m_data[x][j] + scalar;
	return img;
}

Image Image::operator-(unsigned int scalar)
{
	Image img = Image{ m_width, m_height };
	for (unsigned int x = 0; x < m_height; x++)
		for (unsigned int j = 0; j < m_width; j++)
			img.m_data[x][j] = m_data[x][j] - scalar;
	return img;
}

Image Image::operator*(unsigned int scalar)
{
	Image img = Image{ m_width, m_height };
	for (unsigned int x = 0; x < m_height; x++)
		for (unsigned int j = 0; j < m_width; j++)
			img.m_data[x][j] = m_data[x][j] * scalar;
	return img;
}

bool Image::getROI(Image& roiImg, Rectangle roiRect)
{
	if (roiRect.x + roiRect.width > static_cast<int>(m_width) || roiRect.y + roiRect.height > static_cast<int>(m_height)) {
		return false;
	}

	roiImg = Image(roiRect.width, roiRect.height);

	unsigned char** img_l = m_data + roiRect.y;
	unsigned char* img_c = *img_l + roiRect.x;
	unsigned char** roi_l = roiImg.m_data;
	unsigned char* roi_c = *roi_l;

	for (int i = 0; i < roiRect.height; i++) {
		for (int j = 0; j < roiRect.width; j++) {
			*roi_c++ = *img_c++;
		}
		img_l++;
		roi_l++;
		img_c = *img_l + roiRect.x;
		roi_c = *roi_l;
	}

	return true;
}

bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	if (x + width > m_width || y + height > m_height) {
		return false;
	}

	roiImg = Image(width, height);

	unsigned char** img_l = m_data + y;
	unsigned char* img_c = *img_l + x;
	unsigned char** roi_l = roiImg.m_data;
	unsigned char* roi_c = *roi_l;

	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			*roi_c++ = *img_c++;
		}
		img_l++;
		roi_l++;
		img_c = *img_l + x;
		roi_c = *roi_l;
	}

	return true;
}


bool Image::isEmpty() const
{
	if (m_data == nullptr)
		return true;
	else
		return false;
}

/*Size Image::sz() const
{
	return Size(m_width, m_height);
}*/

unsigned int Image::width() const
{
	return m_width;
}

unsigned int Image::height() const
{
	return m_height;
}

unsigned char& Image::at(unsigned int x, unsigned int y)
{
	return m_data[y][x];
}

unsigned char& Image::at(Point pt)
{
	return m_data[pt.y][pt.x];
}

unsigned char* Image::row(int y)
{
	return m_data[y];
}

void Image::release()
{
	for (unsigned int i = 0; i < m_height; i++)
		delete[] m_data[i];
	delete[] m_data;
	m_data = nullptr;
}

Image Image::zeros(unsigned int width, unsigned int height)
{
	Image img = Image{ width, height };
	for (unsigned int i = 0; i < height; i++)
		img.m_data[i] = new unsigned char[width];
	for (unsigned int i = 0; i < height; i++)
		for (unsigned int j = 0; j < width; j++)
			img.m_data[i][j] = 0;

	return img;
}

Image Image::ones(unsigned int width, unsigned int height)
{
	Image img = Image{ width, height };
	for (unsigned int i = 0; i < height; i++)
		img.m_data[i] = new unsigned char[width];
	for (unsigned int i = 0; i < height; i++)
		for (unsigned int j = 0; j < width; j++)
			img.m_data[i][j] = 1;

	return img;
}

//stream insertion
std::ostream& operator<<(std::ostream& os, const Image& dt)
{
	for (unsigned int i = 0; i < dt.m_height; i++) {
		for (unsigned int j = 0; j < dt.m_width; j++)
			os << dt.m_data[i][j] << " ";
		os << std::endl;
	}
	os << std::endl;
	return os;
}

//stream extraction
std::istream& operator>>(std::istream& is, Image& dt)
{
	int w,h;
	is >> w;
	is >> h;
	dt = Image(w,h);
	return is;
}