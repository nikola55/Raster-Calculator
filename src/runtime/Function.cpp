#include <Function.h>
#include <iostream>
namespace runtime {
// A set of the current build in functions
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
}

static std::string names[19] = {
	"load",
	"save"
};

runtime::Function * 
runtime::resolve(const std::string &name, 
				const std::vector<Type*> &args) {
	
	if(name == names[IO_LOAD]) {
		std::cout << "Loading.." << std::endl;
	} else if (name == names[IO_SAVE]) {
		std::cout << "Saving.." << std::endl;
	} else {
		std::cout <<"Unknown function"<<std::endl;
	}
	return 0;
}