#pragma once
#include "image.h"
#include <vector>
class ImageProcessing {
public:
	virtual void process(const Image& src, Image& dst) = 0;
};

class BCA : public ImageProcessing {
public:
	BCA() {gain = 1, bias = 0;}
	BCA(float g, float b) { gain = g, bias = b; }
	
	void process(const Image& src, Image& dst) override;

private:
	float gain;
	float bias;
};

class Gamma : public ImageProcessing {
public:
	Gamma() { gam = 1; }
	Gamma(float gamma) { gam = gamma; }
	virtual void process(const Image& src, Image& dst) override;

private:
	float gam;
};

class Convolution : public ImageProcessing {
public:
	Convolution(std::vector<std::vector <float>> ker) : kernel(ker) {}
	virtual void process(const Image& src, Image& dst) override;

private:
	std::vector<std::vector <float>> kernel;
};