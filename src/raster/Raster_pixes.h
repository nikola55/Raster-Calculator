#ifndef _RASTER_PIXES_H_
#define _RASTER_PIXES_H_
#include <Matrix.h>
#include <string>
#include <cstring>

namespace raster {

class RasterPixesRGB : public RasterRGB {
public:
	pix::Matrix * r, * g, * b;
	RasterPixesRGB(pix::Matrix*r, pix::Matrix*g, pix::Matrix*b) :
		r(r), g(g), b(b) {
	}
	~RasterPixesRGB() {
        delete r;
        delete g;
        delete b;
	}
	virtual std::string details() const {
		char buffer[1024];
		sprintf(buffer, "%s:[width=%d, height=%d]", RasterRGB::details().c_str(), r->nCols, r->nRows);
		return std::string(buffer);
	}
};

class RasterPixesGray : public RasterGray {
public:
	pix::Matrix *g;
	RasterPixesGray(pix::Matrix *g) :
		g(g) {
	}
	~RasterPixesGray() {
        delete g;
	}
	virtual std::string details() const {
		char buffer[1024];
		sprintf(buffer, "%s:[width=%d, height=%d]", RasterGray::details().c_str(), g->nCols, g->nRows);
		return std::string(buffer);
	}
};

class RasterPixesBinary : public RasterBinary {
public:
	pix::Matrix *b;
	RasterPixesBinary(pix::Matrix *b) :
		b(b) {
	}
	~RasterPixesBinary() {
        delete b;
	}
	virtual std::string details() const {
		char buffer[1024];
		sprintf(buffer, "%s:[width=%d, height=%d]", RasterBinary::details().c_str(), b->nCols, b->nRows);
		return std::string(buffer);
	}
};

}
#endif
