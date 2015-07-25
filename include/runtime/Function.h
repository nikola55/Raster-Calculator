#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <vector>
#include <Type.h>
#include <Context.h>
#include <RasterContext.h>
namespace runtime {
// The set of the current build in functions
enum Function_Type {
        /* IO */
	IO_LOAD=0, IO_SAVE,
/* Algebra */
	ALG_ADD,ALG_SUB,ALG_DIV,
	ALG_AND,ALG_OR,ALG_XOR,
	ALG_NOT,
/* Filter */
	FIL_BLUR,FIL_EDGE,FIL_CUSTOM,
/* Transform */
	TRF_SCALE,TRF_ROTATE,
	TRF_TRANSLATE,
/* Morphology */
	MRP_DILATE,MRP_ERODE,
	MRP_OPEN,MRP_CLOSE,
/* Misc */
	MSC_UNWRAP,	MSC_THRESH
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
