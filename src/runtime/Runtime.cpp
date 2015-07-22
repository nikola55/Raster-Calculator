#include <Runtime.h>
#include <Function.h>
#include <stdexcept>

runtime::Runtime::Runtime() {
	cntx = new Context();
}
runtime::Runtime::Runtime(Context*c) 
	: cntx(c) {

}

void runtime::Runtime::execute(const std::vector<cproc::Node*> &stmtList) {
	for(int i = 0 ; i < stmtList.size() ; i++) {
		execute(stmtList[i]);
	}
}

runtime::Type * runtime::Runtime::execute(cproc::Node* node) {
	
	Type * ret_type;
	
	switch(node->type()) {
		case cproc::OPER_NODE: {
			// Evaluate the operands and apply the 
			// operation in it.
			ret_type = 
				oper(static_cast<cproc::Oper*>(node));
			break;
		}
		case cproc::FUNCTION_NODE: {
			// Execute the function and return the result.
			ret_type = 
				function(static_cast<cproc::Function*>(node));
			break;
		}
		case cproc::ASSIGNMENT: {
			// Usually create variable in the context.
			assign(static_cast<cproc::Assign*>(node));
			break;
		}
		case cproc::NAME_NODE: {
			// Search the context for a variable with
			// the name.
			ret_type = 
				name(static_cast<cproc::Name*>(node));
			break;
		}
		case cproc::NUMBER_NODE: {
			// return number
			cproc::Number * numn = 
				static_cast<cproc::Number*>(node);
			ret_type = new Number(numn->value());
			break;
		}
		case cproc::STRING_NODE: {
			// return string;
			cproc::String_Node * strn = 
				static_cast<cproc::String_Node*>(node);
			ret_type = new String(strn->value());
			break;
		}
		default :
			throw std::runtime_error("Unknown Node type.");
	}
	delete node;
	return ret_type;
}

void runtime::Runtime::assign(cproc::Assign *node) {
	const std::string &varnm = node->name();
	Type * tp = execute(node->rightHand());
	cntx->add(varnm, tp);
}

runtime::Type* runtime::Runtime::name(cproc::Name *node) {
	const std::string &nm = node->name();
	return cntx->get(nm);
}

runtime::Type* runtime::Runtime::function(cproc::Function *node) {
	const std::string &nm = node->name();
	std::vector<Type*> argList;
	for(int i = 0 ; i < node->nArgs() ; i++) {
		cproc::Node * arg = node->getArg(i);
		argList.push_back(execute(arg));
	}
	Function * func = resolve(nm, argList);
	// Remove this if.
	if(func) {
		func->execute();
		Type * res = func->result();
		return res;
	}
	return 0;
}

runtime::Type* runtime::Runtime::oper(cproc::Oper *node) {

	cproc::Oper::OperType type = node->operType();
	
	Type * left = execute(node->left());
	Type * right = execute(node->right());
	
	
	
	return 0;
}