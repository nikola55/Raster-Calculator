#ifndef _RASTER_PIXES_H_
#define _RASTER_PIXES_H_
#include <Matrix.h>
#include <iostream>
namespace raster {

class RasterPixesRGB : public RasterRGB {
public:
	pix::Matrix * r, * g, * b;
	RasterPixesRGB(pix::Matrix*r, pix::Matrix*g, pix::Matrix*b) :
		r(r), g(g), b(b) {
        std::cout << "RasterPixesRGB()" <<std::endl;
	}
	~RasterPixesRGB() {
        delete r;
        delete g;
        delete b;
        std::cout << "~RasterPixesRGB()" <<std::endl;
	}
};

class RasterPixesGray : public RasterGray {
public:
	pix::Matrix *g;
	RasterPixesGray(pix::Matrix *g) :
		g(g) {
        std::cout << "RasterPixesGray()" <<std::endl;
	}
	~RasterPixesGray() {
	    std::cout << "~RasterPixesGray()" <<std::endl;
        delete g;
	}
};

class RasterPixesBinary : public RasterBinary {
public:
	pix::Matrix *b;
	RasterPixesBinary(pix::Matrix *b) :
		b(b) {
        std::cout << "RasterPixesBinary()" <<std::endl;
	}
	~RasterPixesBinary() {
	    std::cout << "~RasterPixesBinary()" <<std::endl;
        delete b;
	}
};

}
#endif
