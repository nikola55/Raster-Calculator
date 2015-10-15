#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include <map>
#include <string>
#include <stdexcept>
#include <Type.h>

namespace runtime {

class Context {
	std::map<std::string, Type*> vars;
public:

	~Context() {
		for(std::map<std::string, Type*>::iterator i = vars.begin() ;
			i != vars.end(); i++) {
			delete i->second;
		}
	}

	Type * add(const std::string &nm, Type * t) {
		if(vars.find(nm) != vars.end()) {
			throw std::runtime_error("add(const std::string &nm, Type * t)"
									 "Variable already in the map.");
		}
		vars[nm] = t;
	}
	Type * get(const std::string &nm) {
        std::map<std::string, Type*>::iterator it
                = vars.find(nm);
		if(it == vars.end()) {
			throw std::runtime_error("get(const std::string &nm)"
									 "No variable with this name in the map.");
		}
		return it->second;
	}
	void del(const std::string &nm) {
		std::map<std::string, Type*>::iterator it =
			vars.find(nm);
		if(it == vars.end()) {
			throw std::runtime_error("del(const std::string &nm)"
									 "No variable with this name in the map.");
		}
		vars.erase(it);
	}
};

}
#endif
