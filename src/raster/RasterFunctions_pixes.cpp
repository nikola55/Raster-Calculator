#include <iostream>

#include <Function.h>
#include <RasterManager.h>

#include "Raster_pixes.h"

#include <ImageIO.h>
#include <ConvolveUtils.h>

namespace runtime {

class LoadFunc : public Function {
    std::string fnm;
    Raster * res;
public:
    LoadFunc(const std::vector<Type*> &args) {
        if(args.size() != 1) {
            throw std::runtime_error("LoadFunc(): Not valid number of arguments.");
        }
        fnm = dynamic_cast<String*>(args[0])->value();
    }
    void execute() {
        raster::RasterPixesRGB *rgb =
                dynamic_cast<raster::RasterPixesRGB*> (
                raster::create(
                        raster::RasterSpec(1,1, raster::RASTER_RGB))
                );
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
        if(args[0]->type() != Type::RASTER ||
           args[1]->type() != Type::STRING ||
           args[2]->type() != Type::STRING ) {
            throw std::runtime_error("SaveFunc(): Not valid argument type.");
        }
        r = dynamic_cast<Raster*>(args[0]);
        nm = dynamic_cast<String*>(args[1])->value();
        format = dynamic_cast<String*>(args[2])->value();
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
    pix::EdgeDetectType t;
public:
    EdgeFunc(const std::vector<Type*> args) {
        if(args.size()<1) {
            throw std::runtime_error("EdgeFunc(): Not valid number of arguments.");
        }
        r = dynamic_cast<Raster*>(args[0]);
        if(args.size() == 2 && args[1]->type() == Type::STRING) {

            const std::string &edgeAlg =
                dynamic_cast<String*>(args[1])->value();
            t =  pix::SOBEL;
            if(edgeAlg == "SOBEL") {
                t = pix::SOBEL;
            } else if(edgeAlg == "LOG") {
                t =  pix::LOG;
            } else {
                throw std::runtime_error("EdgeFunc(): unknown edge detection.");
            }
        }
    }
    void execute() {
        switch(r->raster()->type()) {
            case raster::RASTER_RGB: {

                raster::RasterPixesRGB *rgb =
                    dynamic_cast<raster::RasterPixesRGB*>(r->raster());

                raster::RasterPixesRGB *result =
                    dynamic_cast<raster::RasterPixesRGB *>(
                        raster::create(raster::RasterSpec(
                            rgb->r->nCols, rgb->r->nRows, raster::RASTER_RGB))
                   );

                pix::edgeDetect(*rgb->r, *result->r, t);
                pix::edgeDetect(*rgb->g, *result->g, t);
                pix::edgeDetect(*rgb->b, *result->b, t);

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

	if(name == std::string("load")) {
        return new LoadFunc(args);
	} else if (name == std::string("save")) {
		return new SaveFunc(args);
	} else if (name == std::string("edge")) {
		return new EdgeFunc(args);
	}
	return 0;
}
