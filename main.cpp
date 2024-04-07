#define _CRTDBG_MAP_ALLOC
#include "image.h"
#include "drawing.h"
#include "processing.h"
#include <vector>
#include <stdlib.h>
#include <crtdbg.h>
#include<iostream>

int main() {
    Image img;
    std::string imagePath = "C:\\Users\\Bianca\\Downloads\\feep.ascii.pgm";
    img.load(imagePath);
    std::cout << "'feep.ascii.pgm' successfully loaded.\n";

    Image img1;
    std::string imagePath1 = "C:\\Users\\Bianca\\Downloads\\brain_398.ascii.pgm";
    img1.load(imagePath1);
    Point p1 = Point(300, 200);
    Drawing obj;
    obj.drawCircle(img1, p1, 100, 255);
    img1.save(imagePath1);
    std::cout << "'brain_398.ascii.pgm' Circle successfully drawn.\n";

    std::string imagePath2 = "C:\\Users\\Bianca\\Downloads\\venus2.ascii.pgm";
    Image img2;
    img2.load(imagePath2);
    Image img2_1{ img2 };
    BCA b = BCA(1, -2);
    b.process(img2, img2_1);
    img2_1.save(imagePath2);
    std::cout << "'venus2.ascii.pgm' Brightness(+10) and Contrast(-20) successfully modified.\n";

    /*std::string imagePath3 = "C:\\Users\\Bianca\\Downloads\\screws.ascii.pgm";
    Image img3;
    Image img3_1{ img3 };
    img3.load(imagePath3);
    Gamma g = Gamma(2.5);
    g.process(img3, img3_1);
    img3_1.save(imagePath3);
    std::cout << "'screws.ascii.pgm' Gamma(+2.5) successfully modified.\n";

    std::string imagePath4 = "C:\\Users\\Bianca\\Downloads\\mona_lisa.ascii.pgm";
    Image img4;
    Image img4_1{ img4 };
    img4.load(imagePath4);
    std::vector<std::vector<float>> kernel = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    Convolution c = Convolution(kernel);
    c.process(img4, img4_1);
    img4_1.save(imagePath4);
    std::cout << "'mona_lisa.ascii.pgm' Vertical Sobel kernel Convolution successfully applied.\n";
  */
    _CrtDumpMemoryLeaks();
    return 0;
}