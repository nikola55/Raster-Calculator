#include <Runtime.h>
#include <Type.h>
#include <Function.h>
#include <Context.h>
#include <stdexcept>
#include <iostream>

/// For debuging only 
//#include <Parser.h>

runtime::Runtime::Runtime() {
	cntx = new Context();
	outerContext = false;
}
runtime::Runtime::Runtime(Context*c)
	: outerContext(true), cntx(c) {
	
}

runtime::Runtime::~Runtime() {
	if(!outerContext) {
		delete cntx;
	}
}


void runtime::Runtime::execute(const std::vector<cproc::Node*> &stmtList) {
	for(int i = 0 ; i < stmtList.size() ; i++) {
		//printStatement(stmtList[i], "");
		Type * res = execute(stmtList[i]);
		if(res->temporary()) {
			delete res;
		}
	}
}

runtime::Type * runtime::Runtime::execute(cproc::Node* node) {

	Type * ret_type;

	switch(node->type()) {
		case cproc::OPER_NODE: {
			// Evaluate the operands and apply the
			// operation in it.
            // assign temporary.
			ret_type =
				oper(static_cast<cproc::Oper*>(node));
            ret_type->temporary(true);
			break;
		}
		case cproc::FUNCTION_NODE: {
			// Execute the function and return the result.
            // assign temporary.
			ret_type =
				function(static_cast<cproc::Function*>(node));
            ret_type->temporary(true);
			break;
		}
		case cproc::ASSIGNMENT: {
			// create variable in the context.
			ret_type = 
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
			// set temporary flag
			cproc::Number * numn =
				static_cast<cproc::Number*>(node);
			ret_type = new Number(numn->value());
			ret_type->temporary(true);
			break;
		}
		case cproc::STRING_NODE: {
			// return string;
			// set temporary flag.
			cproc::String_Node * strn =
				static_cast<cproc::String_Node*>(node);
			ret_type = new String(strn->value());
			ret_type->temporary(true);
			break;
		}
		default :
			throw std::runtime_error("Unknown Node type.");
	}
	delete node;
	return ret_type;
}

runtime::Type* runtime::Runtime::assign(cproc::Assign *node) {
	const std::string &varnm = node->name();
	Type * tp = execute(node->rightHand());
	tp->temporary(false);
	cntx->add(varnm, tp);
	return tp;
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
	
	Function * func = resolve(cntx, nm, argList);
	func->execute();
    Type * res = func->result();
    for(int i = 0 ;i  < argList.size() ; i++) {
        if(argList[i]->temporary()) {
            delete argList[i];
        }
    }

	delete func;
	return res;
}

runtime::Type* runtime::Runtime::oper(cproc::Oper *node) {

	cproc::Oper::OperType type = node->operType();

	Type * left = execute(node->left());
	Type * right = execute(node->right());
	
	// TODO :
	// Execute operation 
	//  R + N (yes)
	//  N + R (no)
	//  R - N (yes)
	//  N - R (no)
	//  R * N (yes)
	//  N * R (no)
	// 
	if( left->type() == Type::NUMBER && right->type() == Type::NUMBER ) {
		
	} else if (left->type() == Type::NUMBER && right->type() == Type::RASTER) {
		throw std::runtime_error("operation not defined.");
	} else if ( left->type() == Type::RASTER && right->type() == Type::NUMBER ) {
		// RASTER OPER NUMBER
	} else if ( left->type() == Type::RASTER && right->type() == Type::RASTER ) {
		// RASTER OPER RASTER
	} else throw std::runtime_error("not valid operands."); 
	
	if(left->temporary()) {
		delete left;
	}
	if(right->temporary()) {
		delete right;
	}
	
	return 0;
}
