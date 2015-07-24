#ifndef _RASTER_MANAGER_H
#define _RASTER_MANAGER_H
#include <Raster.h>
namespace raster {
struct RasterSpec {
	int width, height;
	RasterType type;
	RasterSpec( int width, 
				int height, 
				RasterType type) :
				width(width), 
				height(height), 
				type(type) {
	}
};

Raster * create(RasterSpec);
void destroy(Raster*);

};
#endif