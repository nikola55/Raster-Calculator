#ifndef _RASTER_FUNCTIONS_H
#define _RASTER_FUNCTIONS_H
#include <Raster.h>
#include <string>
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

enum BlurType{};
Raster* blur(const Raster*, BlurType);
enum EdgeType{};
Raster* edge(const Raster*, EdgeType);
//Raster* custom(const Raster*, );
struct ScaleOpt{};
Raster* scale(const Raster*, ScaleOpt);
struct RotateOpt{};
Raster* rotate(const Raster*, RotateOpt);
struct TranslOpt{};
Raster* translate(const Raster*, TranslOpt);
struct DilateOpt{};
Raster* dilate(const RasterBinary*, DilateOpt);
struct ErodeOpt{};
Raster* erode(const RasterBinary*, ErodeOpt);

Raster* close(const RasterBinary*);
Raster* open(const RasterBinary*);

}
#endif
