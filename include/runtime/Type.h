#ifndef _TYPE_H_
#define _TYPE_H_
#include <string>
#include <Raster.h>
namespace runtime{
class Type {
public:
	enum Type_type {
		RASTER,
		NUMBER,
		STRING,
		VOID
	};
	Type(Type_type t) :
		t(t), tmp(false) {
	}
    virtual Type_type type() {
        return t;
    }
    virtual bool temporary() const {
        return tmp;
    }
    virtual void temporary(bool t) {
        tmp = t;
    }
    virtual ~Type(){}
private:
	Type_type t;
// This flag is used to indicate
// that an Object holds a temporary
// result, usually result of function
// or operation if the result is not
// assigned to a variable, then it
// is deleted after it is used.
    bool tmp;
};

class Raster : public Type {
	std::string nm;
    raster::Raster * r;
public:
	Raster(
           const std::string &nm,
           raster::Raster * r) :
		Type(RASTER), nm(nm), r(r) {
	}
	const std::string & name() const {
		return nm;
	}
	raster::Raster * raster() {
        return r;
	}
    virtual ~Raster() { delete r; }
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
