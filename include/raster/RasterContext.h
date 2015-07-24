#ifndef _RASTER_CONTEXT_H_
#define _RASTER_CONTEXT_H_
#include 
namespace raster {
class RasterContext {
	std::map<std::string nm, Raster*> m;
public:
	void add(Raster*r, const std::string &nm) {
		if(map.find(nm) != map.end()) {
			throw std::runtime_error(
									"add(Raster*, const std::string &nm) "
									"Raster: "+nm+
									" Already in context");
		}
		m[nm]=r;
	}
	Raster* get(const std::string &nm) {
		std::map<std::string nm, Raster*>::iterator it = 
			map.find(nm);
		if(it == map.end()) {
			throw std::runtime_error(
									"get(const std::string &nm) "
									"Raster: "+nm+
									" Not in context");
		}
		return *it;
	}
	void del(const std::string &nm) {
		std::map<std::string nm, Raster*>::iterator it = 
			map.find(nm);
		if(it == map.end()) {
			throw std::runtime_error(
									"del(const std::string &nm) "
									"Raster: "+nm+
									" Not in context");
		}
		m.erase(it);
	}
};
}
#endif