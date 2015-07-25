#include <Function.h>
#include <iostream>
#include <ImageIO.h>
#include <ConvolveUtils.h>
#include "../raster/Raster_pixes.h"
namespace runtime {
// A set of the current build in functions
enum Function_Type {
        /* IO */
	IO_LOAD=0, IO_SAVE,
/* Algebra */
	ALG_ADD,ALG_SUB,ALG_DIV,
	ALG_AND,ALG_OR,ALG_XOR,
	ALG_NOT,
/* Filter */
	FIL_BLUR,FIL_EDGE,FIL_CUSTOM,
/* Transform */
	TRF_SCALE,TRF_ROTATE,
	TRF_TRANSLATE,
/* Morphology */
	MRP_DILATE,MRP_ERODE,
	MRP_OPEN,MRP_CLOSE,
/* Misc */
	MSC_UNWRAP,	MSC_THRESH
};
}

static std::string names[19] = {
	"load",
	"save",
};
namespace runtime {

class LoadFunc : public Function {
    std::string fnm;
    Raster * res;
public:
    LoadFunc(const std::vector<Type*> &args) {
        for(int i = 0 ;i  < args.size() ; i++) {
            if(args[i]->type()==Type::STRING) {
                fnm = static_cast<String*>(args[i])->value();
                break;
            }
        }
    }
    void execute() {

        raster::RasterPixesRGB *rgb =
            new raster::RasterPixesRGB(new pix::Matrix(1,1),
                                        new pix::Matrix(1,1),
                                        new pix::Matrix(1,1));
        pix::loadFromFile(fnm.c_str(), *rgb->r, *rgb->g, *rgb->b);
        res = new Raster("", rgb);

    }
    int nArgs() {return 1;}
    void addArg(int pos, Type *t) {}
    Type * arg(int pos) {}
    Type * result() { return res; }
};

class SaveFunc : public Function {
    std::string nm;
    std::string format;
    Raster * r;
public:
    SaveFunc(const std::vector<Type*> args) {
        if(args.size()!=3) {
            throw std::runtime_error("SaveFunc(): Not valid number of arguments.");
        }
        r = (Raster*)args[0];
        nm = dynamic_cast<String*>(args[1])->value();
        format = dynamic_cast<String*>(args[2])->value();
        std::cout << nm << " " << format << std::endl;
    }
    void execute() {
        switch(r->raster()->type()) {
            case raster::RASTER_RGB: {
                raster::RasterPixesRGB *rgb =
                    dynamic_cast<raster::RasterPixesRGB*>(r->raster());
                saveToFile(*rgb->r, *rgb->g, *rgb->b, nm.c_str(), format.c_str());
                break;
            }
            case raster::RASTER_GRAY: {
                raster::RasterPixesGray *rgb =
                    dynamic_cast<raster::RasterPixesGray*>(r->raster());
                saveToFile(*rgb->g, *rgb->g, *rgb->g, nm.c_str(), format.c_str());
                break;
            }
            case raster::RASTER_BINARY: {
                break;
            }
            default : throw std::runtime_error("SaveFunc::execute() Not valid raster type.");
        }
    }
    int nArgs() {return 3;}
    void addArg(int pos, Type *t) {}
    Type * arg(int pos) {}
    Type * result() { return new Void(); }
};

class EdgeFunc : public Function {
    Raster * r;
    Raster * res;
public:
    EdgeFunc(const std::vector<Type*> args) {
        if(args.size()<1) {
            throw std::runtime_error("EdgeFunc(): Not valid number of arguments.");
        }
        r = dynamic_cast<Raster*>(args[0]);
    }
     void execute() {
        switch(r->raster()->type()) {
            case raster::RASTER_RGB: {

                raster::RasterPixesRGB *rgb =
                    dynamic_cast<raster::RasterPixesRGB*>(r->raster());

                pix::Matrix * newR = new pix::Matrix(rgb->r->nCols, rgb->r->nRows);
                pix::Matrix * newG = new pix::Matrix(rgb->g->nCols, rgb->g->nRows);
                pix::Matrix * newB = new pix::Matrix(rgb->b->nCols, rgb->b->nRows);

                pix::edgeDetect(*rgb->r, *newR, pix::SOBEL);
                pix::edgeDetect(*rgb->g, *newG, pix::SOBEL);
                pix::edgeDetect(*rgb->b, *newB, pix::SOBEL);

                raster::RasterPixesRGB *result = new raster::RasterPixesRGB(newR, newG, newB);
                res = new Raster("", result);
            }
            case raster::RASTER_GRAY: {

                break;
            }
            case raster::RASTER_BINARY: {

                break;
            }
            default : throw std::runtime_error("SaveFunc::execute() Not valid raster type.");
        }
    }
    int nArgs() {return 3;}
    void addArg(int pos, Type *t) {}
    Type * arg(int pos) {}
    Type * result() { return res; }
};

}

runtime::Function *
runtime::resolve( Context * ctx,
				  const std::string &name,
				  const std::vector<Type*> &args
				 ) {

	if(name == names[IO_LOAD]) {
        LoadFunc * lf = new LoadFunc(args);
        return lf;
	} else if (name == names[IO_SAVE]) {
		return new SaveFunc(args);
	} else if (name == std::string("edge")) {
		return new EdgeFunc(args);
	}
	return 0;
}
