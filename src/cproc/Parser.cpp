#include <Parser.h>
#include <Node.h>
#include <Lexer.h>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
namespace parser {
using namespace cproc;
using std::cout; 
using std::endl; 
void destroyTree(Node * n) {
	if(n == 0) return;
	if(n->type() == cproc::FUNCTION_NODE) {
		Function * fn = (Function*)n;
		for(int i = 0 ; i < fn->nArgs() ; i++) {
			destroyTree(fn->getArg(i));
		}
	} else {
		destroyTree(n->left());
		destroyTree(n->right());
	}
	delete n;
}
Node * sub_expr_or(Lexer &lex) ;
// handles function calls
	Function* func_prime(Lexer &lex) {
	Token name = lex.next();
	if(name.type != NAME) return 0;
	Function * func = new Function(name.value);
	Token next = lex.next();
	if(next.type != LPAREN) {
		delete func;
		return 0;
	}
	if(lex.top().type == RPAREN) { // No arguments.
		lex.next();
		return func;
	}
	// Handle the argument list
	// this should be in the form
	// EXPRESSION [SEQ EXPRESSION ...]
	for(;;) {
		Node * node = sub_expr_or(lex);
		func->addArg(node);
		next = lex.next();
		if(next.type == RPAREN) {
			return func;
		}
		if(next.type != SEQ) {
			destroyTree(node);
			return 0;
		}
	}
}
Node * prime(Lexer &lex) {
	Token tok = lex.next();
	switch(tok.type) {
		case NUMBER: {
			Number * num = new Number(atof(tok.value.c_str()));
			return num;
		}
		case NAME : {
			Token nxt = lex.next();
			if(nxt.type == LPAREN) {
				lex.pushBack(nxt);
				lex.pushBack(tok);
				Function * n = func_prime(lex);
				return n;
			} else if (nxt.type == ASSIGN) {
				Assign * n = new Assign(tok.value);
				n->rightHand(sub_expr_or(lex));
				return n;
			} else {
				Name * n = new Name(tok.value);
				lex.pushBack(nxt);
				return n;
			}
		}
		case NOT : {
			 Function * n = new Function("NOT");
			 n->addArg(prime(lex));
			 return n;
		}
		case LPAREN : {
			Node * n = sub_expr_or(lex);
			if(lex.top().type != RPAREN) {
				throw std::runtime_error("case PAREN: ) expected.");
			}
			lex.next();
			return n;
		}
		case STRING : {
			String_Node *n = new String_Node(tok.value);
			return n;
		}
		default :
			throw std::runtime_error("Primary expected.");
	}
}
Node * term(Lexer &lex) {
	Node * left = prime(lex);
	for(;;) {
		Token nxt = lex.next();
		switch(nxt.type) {
			case MUL: case DIV: {
				Oper *n = new Oper( nxt.type == MUL ? Oper::MUL : Oper::DIV );
				n->left(left);
				n->right(term(lex));
				left = n;
				break;
			}
			default :
				lex.pushBack(nxt);
				return left;
		}
	}
}
Node * expression(Lexer &lex) {
	Node *left = term(lex);
	for(;;) {
		Token nxt = lex.next();
		switch(nxt.type) {
			case PLUS: case MINUS: {
				Oper *n = new Oper( nxt.type == PLUS ? Oper::ADD : Oper::SUB );
				n->left(left);
				n->right(term(lex));
				left = n;
				break;
			}
			default:
				lex.pushBack(nxt);
				return left;
		}
	}
}
Node * sub_expr_and(Lexer &lex) {
	Node *left = expression(lex);
	for(;;) {
		Token nxt = lex.next();
		switch(nxt.type) {
			case AND: {
				Node * n = new Oper(Oper::AND);
				n->left(left);
				n->right(expression(lex));
				left = n;
				break;
			}
			default:
				lex.pushBack(nxt);
				return left;
		}
	}
}
// handles the XOR
Node * sub_expr_xor(Lexer &lex) {
	Node * left = sub_expr_and(lex);
	for(;;) {
		Token nxt = lex.next();
		switch(nxt.type) {
			case XOR : {
				Oper * n = new Oper(Oper::XOR);
				n->left(left);
				n->right(sub_expr_and(lex));
				left = n;
				break;
			}
			default :
				lex.pushBack(nxt);
				return left;
		}
	}
}
// Handles the least tight binded OR
Node * sub_expr_or(Lexer &lex) {
	Node* left = sub_expr_xor(lex);
	for(;;) {
		Token nxt = lex.next();
		switch(nxt.type) {
			case OR : {
				Oper * n = new Oper(Oper::OR);
				n->left(left);
				n->right(sub_expr_xor(lex));
				left = n;
				break;
			}
			default :
				lex.pushBack(nxt);
				return left;
		}
	}
}
void cleanUp(std::vector<Node*> &stmts) {
	for(int i = 0 ; i < stmts.size() ; i++) {
		destroyTree(stmts[i]);
	}
	stmts.resize(0);
}
std::vector<Node*> statement_list(Lexer &lex) {
	std::vector<Node*> statements;
	for(;;) {
		Node * expr = sub_expr_or(lex);
		statements.push_back(expr);
		// end of tokens but
		// END_STMT expected.
		if(!lex.hasMore() || lex.top().type!=cproc::END_STMT) {
			cleanUp(statements);
			break;
		}
		// eat the END_STMT
		lex.next();
		if(lex.top().type == ENDPRG) {
			break;
		}
	}
	return statements;
}
std::vector<Node*> program(Lexer &lex) {
	return statement_list(lex);
}
}
std::vector<cproc::Node*> cproc::parse(const Lexer &lex) {
	Lexer l = lex;
	return parser::program(l);
}
#ifdef PARSER_DEBUG
void cproc::printStatement(const Node* stmt, const std::string &spaces) {
	using std::cout; 
	using std::endl; 
	if(stmt->isLeaf()) {
		cout << spaces << "Leaf node: "; 
		printNodeType(stmt->type());
		return;
	}
	else if(stmt->type() == FUNCTION_NODE) {
		Function * f = (Function*)stmt;
		cout << spaces << "Function: " << f->name() << endl; 
		for(int i = 0 ; i < f->nArgs() ; i++) {
			printStatement(f->getArg(i), "  "+spaces);
		}
	}
	else if(stmt->type() == ASSIGNMENT) {
		Assign * a = (Assign*)stmt;
		cout << spaces << "Assign: var: " << a->name() << " " << endl;
		printStatement(a->rightHand(), "  "+spaces);
	}
	else if(stmt->type() == OPER_NODE) {
		Oper * op = (Oper*)stmt;
		cout << spaces << "Operator: "; 
		switch(op->operType()) {
			case Oper::ADD: {
				cout << "Oper::ADD" << endl; 
				break;
			}
			case Oper::MUL: {
				cout << "Oper::MUL" << endl; 
				break;
			}
			case Oper::DIV: {
				cout << "Oper::DIV" << endl; 
				break;
			}
			case Oper::AND: {
				cout << "Oper::AND" << endl; 
				break;
			}
			case Oper::OR: {
				cout << "Oper::OR" << endl; 
				break;
			}
			case Oper::XOR: {
				cout << "Oper::XOR" << endl; 
				break;
			}
			default: {
				cout << "Not valid oper." << endl; 
			}			
		}
		cout << "Left: " << endl; 
		cproc::printStatement(op->left(), "  "+spaces);
		cout << "Right: " << endl; 
		cproc::printStatement(op->right(), "  "+spaces);
	}
}
#endif