#ifndef _RASTER_H_
#define _RASTER_H_
namespace raster {
enum RasterType {
	RASTER_RGB,
	RASTER_GRAY,
	RASTER_BINARY
};

class Raster {
	RasterType t;
protected:
	Raster(RasterType t) : t(t) {
	}
public:
	virtual RasterType type() {
		return t;
	}
    virtual ~Raster(){};
};

class RasterRGB : public Raster {
protected:
	RasterRGB() : Raster(RASTER_RGB) {
	}
};

class RasterGray : public Raster {
protected:
	RasterGray() : Raster(RASTER_GRAY) {
	}
};

class RasterBinary : public Raster {
protected:
	RasterBinary() : Raster(RASTER_BINARY) {
	}
};

}
#endif
