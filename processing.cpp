#include "processing.h"

void BCA::process(const Image& src, Image& dst)
{
	dst = src;
	for (unsigned int i = 0; i < dst.height(); i++)
		for (unsigned int j = 0; j < dst.width(); j++) {
			if (gain * dst.at(i, j) + bias < 0)
				dst.at(i, j) = 0;
			else if (gain * dst.at(i, j) + bias > 255)
				dst.at(i, j) = 255;
			else
                dst.at(i, j) = static_cast<unsigned char>(std::round(gain * dst.at(i, j) + bias));
		}
}

void Gamma::process(const Image& src, Image& dst)
{
	dst = src;
	if (gam == 1)
		return;
    for (unsigned int i = 0; i < dst.height(); i++)
        for (unsigned int j = 0; j < dst.width(); j++)
            dst.at(i,j) = pow(dst.at(i, j), gam);
}

void Convolution::process(const Image& src, Image& dst)
{
    Image img(src.width(), src.height());
    int k_width = kernel[0].size();
    int k_height = kernel.size();
    int k_centerx = k_width / 2;
    int k_centery = k_height / 2;
    dst = src;
    for (int i = 0; i < static_cast<int>(src.height()); i++)
        for (int j = 0; j < static_cast<int>(src.width()); j++) {
            float sum = 0;
            for (int ki = 0; ki < k_height; ki++)
                for (int kj = 0; kj < k_width; kj++) {
                    int imgx = k_centerx - j + kj;
                    int imgy = k_centery - i + ki;
                    if (imgx >= 0 && imgx < static_cast<int>(src.width()) && imgy >= 0 && imgy < static_cast<int>(src.height()))
                        sum += dst.at(imgx, imgy) * kernel[ki][kj];
                }
            img.at(j, i) = static_cast<unsigned char>(std::round(sum));
        }
    dst = img;
}

