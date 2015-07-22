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
	Type * add(const std::string &nm, Type * t) {
		
	}
	Type * get(const std::string &nm) {
		
	}
	void del(const std::string &nm) {
		
	}
};
	
}
#endif
