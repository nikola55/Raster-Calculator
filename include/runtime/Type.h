#ifndef _TYPE_H_
#define _TYPE_H_
#include <string>
namespace runtime{
// There are 3 types :
// Raster, Number, String
// + Function that returns
// any of the 3 types or returns
// nothing. So nothing is also
// a type that indicates nothing

class Type {
public:
	enum Type_type {
		RASTER,
		NUMBER,
		STRING,
		VOID
	};
	Type(Type_type t) :
		t(t) {	
	}
private:
	Type_type t;
};

class Raster : public Type {
	std::string nm;
public:
	Raster(const std::string &nm) :
		Type(RASTER), nm(nm) {	
	}
	const std::string & name() const {
		return nm;
	}
};

class Number : public Type {
	double v;
public:
	Number(double v) :
		Type(NUMBER), v(v) {	
	}
	const double value() const {
		return v;
	}
};

class String : public Type {
	std::string str;
public:
	String(const std::string &str) :
		str(str), Type(STRING) {	
	}
	const std::string& value() const {
		return str;
	}
};

class Void : public Type {
public:
	Void() : Type(VOID) {
	}
};

// The function is not an ordinary 
// type so it not inherits from Type
class Function {
public:
	virtual void execute() = 0;
	virtual int nArgs() = 0;
	virtual void addArg(int pos, Type *t) = 0;
	virtual Type * arg(int pos) = 0;
	virtual Type * result() = 0;
};
}
#endif