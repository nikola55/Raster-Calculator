#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <vector>
#include <string>
namespace runtime {

class Context;
class Function;
class Type;

// The set of the current build in functions
enum Function_Type {
	ALG_ADD,ALG_SUB,ALG_DIV,
	ALG_AND,ALG_OR,ALG_XOR,
	ALG_NOT
};
// Creates a function object based on the name and the
// argument list. The caller only needs to call execute
// on the object.
Function * resolve(	Context * ctx,
					const std::string &name,
					const std::vector<Type*> &args
				   );
}
#endif
