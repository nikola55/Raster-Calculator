#ifndef _RASTER_FUNCTIONS_H
#define _RASTER_FUNCTIONS_H
namespace raster {

RasterRGB * IOLoad(const std::string&);
void IOSave(const Raster*, const std::string&);

Raster * add(const Raster*, const Raster*);
Raster * add(const Raster *, float);

Raster * sub(const Raster*, const Raster*);
Raster * sub(const Raster *, float);

Raster * div(const Raster*, const Raster*);
Raster * div(const Raster *, float);

Raster * andR(const RasterBinary*, const RasterBinary*);
Raster * orR(const RasterBinary*, const RasterBinary*);
Raster * xorR(const RasterBinary*, const RasterBinary*);
Raster * notR(const RasterBinary*);


Raster* blur(const Raster*, BlurType);
Raster* edge(const Raster*, EdgeType);
//Raster* custom(const Raster*, );

Raster* scale(const Raster*, ScaleOpt);
Raster* rotate(const Raster*, RotateOpt);
Raster* translate(const Raster*, TranslOpt);

Raster* dilate(const RasterBinary*, DilateOpt);
Raster* erode(const RasterBinary*, ErodeOpt);

Raster* close(const RasterBinary*);
Raster* open(const RasterBinary*);

}
#endif