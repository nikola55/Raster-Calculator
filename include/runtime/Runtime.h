#ifndef _RUNTIME_H_
#define _RUNTIME_H_
#include <vector>
#include <string>
#include <Node.h>

namespace runtime {

    class Context;
    class Type;

class Runtime {
	bool outerContext;
	Context * cntx;
	Type* name(cproc::Name *node);
	void assign(cproc::Assign *node);
	Type* function(cproc::Function *node);
	Type* oper(cproc::Oper *node);
	Type* execute(cproc::Node* node);
public:
	Runtime();
	Runtime(Context*);
	~Runtime();
	void execute(const std::vector<cproc::Node*> &stmtList);
};

}
#endif
