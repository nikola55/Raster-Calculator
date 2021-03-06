#ifndef _TYPE_H_
#define _TYPE_H_
#include <string>
#include <cstring>
#include <../raster/Raster.h>

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
	virtual std::string string() const = 0;
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
	
	virtual std::string string() const {
		return "[ Raster :" + r->details() + " ]";
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
	virtual std::string string() const {
		char buff[20];
		sprintf(buff, "%f", v);
		return std::string(buff);
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
	virtual std::string string() const {
		return str;
	}
};

class Void : public Type {
public:
	Void() : Type(VOID) {
	}
	virtual std::string string() const {
		return "[Void]";
	}
};

// The function is not an ordinary
// type so it doesn't inherits from Type
class Function {
protected:
	const char * funcName;
	int minArgc;
	int argc;
public:
	Function(const char * fn, int mac, int ac);
	virtual void execute() = 0;
	virtual int nArgs();
	virtual void addArg(int pos, Type *t) = 0;
	virtual Type * arg(int pos) = 0;
	virtual Type * result() = 0;
	virtual const char * name();
};
}
#endif
