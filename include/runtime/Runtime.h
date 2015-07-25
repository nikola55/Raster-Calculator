#ifndef _RUNTIME_H_
#define _RUNTIME_H_
#include <vector>
#include <string>
#include <Node.h>
#include <Context.h>
#include <Type.h>
#include <RasterContext.h>
namespace runtime {

class Runtime {
	Context * cntx;
	Type* name(cproc::Name *node);
	void assign(cproc::Assign *node);
	Type* function(cproc::Function *node);
	Type* oper(cproc::Oper *node);
	Type* execute(cproc::Node* node);
public:
	Runtime();
	Runtime(Context*);
	void execute(const std::vector<cproc::Node*> &stmtList);
};

}
#endif
