#ifndef _RASTER_PIXES_H_
#define _RASTER_PIXES_H_
namespace raster {
	
class RasterPixesRGB : public RasterRGB {
public:
	pix::Matrix * r, * g, * b;
	RasterPixesRGB(pix::Matrix*r, pix::Matrix*g, pix::Matrix*b) :
		r(r), g(g), b(b) {
	}
};
	
class RasterPixesGray : public RasterGray {
public:
	pix::Matrix *g;
	RasterPixesGray(pix::Matrix *g) :
		g(g) {
	}
};
	
class RasterPixesBinary : public RasterBinary {
public:
	pix::Matrix *b;
	RasterPixesBinary(pix::Matrix *b) :
		b(b) {
	}
};
	
}
#endif