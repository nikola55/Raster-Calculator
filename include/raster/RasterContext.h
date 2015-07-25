#ifndef _RASTER_CONTEXT_H_
#define _RASTER_CONTEXT_H_
#include <Raster.h>
#include <string>
#include <map>
namespace raster {
class RasterContext {
	std::map<std::string, Raster*> m;
public:
	void add(Raster*r, const std::string &nm) {
		if(m.find(nm) != m.end()) {
			throw std::runtime_error(
									"add(Raster*, const std::string &nm) "
									"Raster: "+nm+
									" Already in context");
		}
		m[nm]=r;
	}
	Raster* get(const std::string &nm) {
		std::map<std::string, Raster*>::iterator it =
			m.find(nm);
		if(it == m.end()) {
			throw std::runtime_error(
									"get(const std::string &nm) "
									"Raster: "+nm+
									" Not in context");
		}
		return it->second;
	}
	void del(const std::string &nm) {
		std::map<std::string, Raster*>::iterator it =
			m.find(nm);
		if(it == m.end()) {
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
