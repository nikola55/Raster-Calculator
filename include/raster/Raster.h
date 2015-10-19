#ifndef _RASTER_H_
#define _RASTER_H_
#include <string>
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
	virtual std::string details() const = 0;
};

class RasterRGB : public Raster {
protected:
	RasterRGB() : Raster(RASTER_RGB) {
	}
	virtual std::string details() const {
		return "RasterRGB";
	}
};

class RasterGray : public Raster {
protected:
	RasterGray() : Raster(RASTER_GRAY) {
	}
	virtual std::string details() const {
		return "RasterGray";
	}
};

class RasterBinary : public Raster {
protected:
	RasterBinary() : Raster(RASTER_BINARY) {
	}
	virtual std::string details() const {
		return "RasterBinary";
	}
};

}
#endif
