#include <RasterManager.h>
#include <Matrix.h>
#include <stdexcept>
#include "Raster_pixes.h"
raster::Raster * raster::create(RasterSpec spec) {
	int w = spec.width;
	int h = spec.height;
	Raster * ret;
	switch(spec.type) {
		case RASTER_RGB: {
			ret = new RasterPixesRGB(
								new pix::Matrix(h, w), 
								new pix::Matrix(h, w), 
								new pix::Matrix(h, w));
			break;
		}
		case RASTER_GRAY: {
			ret = new RasterPixesGray(
								new pix::Matrix(h, w));
			break;
		}
		case RASTER_BINARY: {
			ret = new RasterPixesBinary(
								new pix::Matrix(h, w));
			break;
		}
		default: {
			throw std::runtime_error("raster::create(RasterSpec spec)"
									 "Unknown Matrix type");
		}
	}
	
	return ret;
}

void raster::destroy(Raster* r) {
	
	RasterType t = r->type();
	
	switch(t) {
		case RASTER_RGB: {
			RasterPixesRGB * rgb = 
				(RasterPixesRGB *) r;
			delete rgb->r;
			delete rgb->g;
			delete rgb->b;
			break;
		}
		case RASTER_GRAY: {
			RasterPixesGray * gray = 
				(RasterPixesGray *) gray;
			delete gray->g;
			break;
		}
		case RASTER_BINARY: {
			RasterPixesBinary * bin = 
				(RasterPixesBinary *) r;
			delete bin->b;
			break;
		}
		default:
			throw std::runtime_error("raster::destroy(Raster* r)"
									 "Unknown Matrix type");
			break;
	}
	
	delete r;
}