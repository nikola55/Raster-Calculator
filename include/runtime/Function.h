#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <vector>
#include <Type.h>
namespace runtime {
// Creates a function object based on the name and the
// argument list. The caller only needs to call execute
// on the object.
Function * resolve(	const std::string &name, 
					const std::vector<Type*> &args
				   );
}
#endif