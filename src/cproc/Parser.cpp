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
 #ifdef DEBUG
 cout << "func_prime(Lexer &lex)" << endl; 
#endif
 
	Token name = lex.next();
	if(name.type != NAME) return 0;
	Function * func = new Function(name.value);
	Token next = lex.next();
	if(next.type != LPAREN) {
		delete func;
		return 0;
	}
	if(lex.top().type == RPAREN) { // No arguments.
	 #ifdef DEBUG
 cout << "func_prime(Lexer &lex) next.type == RPAREN valid function" << endl; 
			cout << "exit func_prime(Lexer &lex)" << endl; 
#endif
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
			
 #ifdef DEBUG
 cout << "func_prime(Lexer &lex) next.type == RPAREN valid function" << endl; 
			cout << "exit func_prime(Lexer &lex)" << endl; 
#endif
 
			return func;
		}
		if(next.type != SEQ) {
			destroyTree(node);
			return 0;
		}
	}
	 
}

Node * prime(Lexer &lex) {
 #ifdef DEBUG
 cout << "prime(Lexer &lex)" << endl; 
#endif
 	
	Token tok = lex.next();
	
	switch(tok.type) {
		case NUMBER: {
			Number * num = new Number(atof(tok.value.c_str()));
			
 #ifdef DEBUG
 cout << "case NUMBER: " << num->value() << endl; 
#endif
 

			return num;
		}
		case NAME : {
			Token nxt = lex.next();
			
 #ifdef DEBUG
 cout << "NAME " << tok.value << endl; 
#endif
 

			if(nxt.type == LPAREN) {
				lex.pushBack(nxt);
				lex.pushBack(tok);
				
 #ifdef DEBUG
 cout << "nxt.type == LPAREN(Function call)" << endl; 
#endif
 

				Function * n = func_prime(lex);
				
 #ifdef DEBUG
 cout << "return Function * n" << endl; 
				cout << "exit prime(Lexer &lex)" << endl; 
#endif

				return n;
			} else if (nxt.type == ASSIGN) {
				Assign * n = new Assign(tok.value);
				
 #ifdef DEBUG
 cout << "nxt.type == ASSIGN" << endl; 
#endif
 

				n->rightHand(sub_expr_or(lex));
				#ifdef DEBUG
 cout << "exit prime(Lexer &lex)" << endl; 
#endif

				return n;
			} else {
				Name * n = new Name(tok.value);
				
 #ifdef DEBUG
 cout << "case NAME (Only name)" << endl; 
#endif
 

				lex.pushBack(nxt);
				#ifdef DEBUG
 cout << "Next " << type_to_name(lex.top()) << endl;
				cout << "exit prime(Lexer &lex)" << endl; 
#endif

				return n;
			}
		}
		case NOT : {
			 Function * n = new Function("NOT");
			 n->addArg(prime(lex));
			 #ifdef DEBUG
 cout << "exit prime(Lexer &lex)" << endl; 
#endif

			 return n;
		}
		case LPAREN : {
			
 #ifdef DEBUG
 cout << "case LPAREN" << endl; 
#endif
 

			Node * n = sub_expr_or(lex);
			
 #ifdef DEBUG
 cout << type_to_name(lex.top()) << endl; 
#endif
 

			if(lex.top().type != RPAREN) {
				throw std::runtime_error("case PAREN: ) expected.");
			}
			lex.next();
			#ifdef DEBUG
 cout << "exit prime(Lexer &lex)" << endl; 
#endif

			return n;
		}
		default :
			throw std::runtime_error("Primary expected.");
	}
	 	
}

Node * term(Lexer &lex) {
 #ifdef DEBUG
 cout << "term(Lexer &lex)" << endl; 
#endif
 
	Node * left = prime(lex);
	for(;;) {
		Token nxt = lex.next();
		switch(nxt.type) {
			case MUL: case DIV: {
				
 #ifdef DEBUG
 cout << "case MUL: case DIV:" << endl; 
#endif
 

				Oper *n = new Oper( nxt.type == MUL ? Oper::MUL : Oper::DIV );
				n->left(left);
				n->right(term(lex));
				left = n;
				break;
			}
			default :
				lex.pushBack(nxt);
				#ifdef DEBUG
 cout << "exit term(Lexer &lex)" << endl; 
#endif
 
				return left;
		}
	}
}

Node * expression(Lexer &lex) {
 #ifdef DEBUG
 cout << "expression(Lexer &lex)" << endl; 
#endif
 
	Node *left = term(lex);
	for(;;) {
		Token nxt = lex.next();
		switch(nxt.type) {
			case PLUS: case MINUS: {
				
 #ifdef DEBUG
 cout << "case PLUS: case MINUS:" << endl; 
#endif
 

				Oper *n = new Oper( nxt.type == PLUS ? Oper::ADD : Oper::SUB );
				n->left(left);
				n->right(term(lex));
				left = n;
				break;
			}
			default:
				lex.pushBack(nxt);
				#ifdef DEBUG
 cout << "exit expression(Lexer &lex)" << endl; 
#endif
 
				return left;
		}
	}
	
}

Node * sub_expr_and(Lexer &lex) {
 #ifdef DEBUG
 cout << "sub_expr_and(Lexer &lex)" << endl; 
#endif
 
	Node *left = expression(lex);
	for(;;) {
		Token nxt = lex.next();
		switch(nxt.type) {
			case AND: {
				
 #ifdef DEBUG
 cout << "case AND :" << endl; 
 cout << "next:" << type_to_name(lex.top()) << endl; 
#endif
 
				Node * n = new Oper(Oper::AND);
				n->left(left);
				n->right(expression(lex));
				left = n;
 #ifdef DEBUG
 cout << "case AND exit:" << endl; 
#endif
 
				break;
			}
			default:
				lex.pushBack(nxt);
				#ifdef DEBUG
 cout << "exit sub_expr_and(Lexer &lex)" << endl; 
#endif
 
				return left;
		}
	}
	
}

// handles the XOR
Node * sub_expr_xor(Lexer &lex) {
 #ifdef DEBUG
 cout << "sub_expr_xor(Lexer &lex)" << endl; 
#endif
 	
	Node * left = sub_expr_and(lex);
	
	for(;;) {
		Token nxt = lex.next();
		switch(nxt.type) {
			case XOR : {
				
 #ifdef DEBUG
 cout << "case XOR :" << endl; 
#endif
 

				Oper * n = new Oper(Oper::XOR);
				n->left(left);
				n->right(sub_expr_and(lex));
				left = n;
				break;
			}
			default :
				lex.pushBack(nxt);
				#ifdef DEBUG
 cout << "exit sub_expr_xor(Lexer &lex)" << endl; 
#endif
 	
				return left;
		}
	}
}

// Handles the least tight binded OR
Node * sub_expr_or(Lexer &lex) {
 #ifdef DEBUG
 cout << "sub_expr_or(Lexer &lex)" << endl; 
#endif
 	
	Node* left = sub_expr_xor(lex);
	
	for(;;) {
		
		Token nxt = lex.next();
		
		switch(nxt.type) {
			case OR : {
				
 #ifdef DEBUG
 cout << "case OR :" << endl; 
#endif
 

				Oper * n = new Oper(Oper::OR);
				n->left(left);
				n->right(sub_expr_xor(lex));
				left = n;
				break;
			}
			default :
				lex.pushBack(nxt);
				#ifdef DEBUG
 cout << "exit sub_expr_or(Lexer &lex)" << endl; 
#endif
 
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
 #ifdef DEBUG
 cout << "statement_list(Lexer &lex)" << endl; 
#endif
 	
	std::vector<Node*> statements;
	
	for(;;) {
	
		Node * expr = sub_expr_or(lex);
		statements.push_back(expr);
		
 #ifdef DEBUG
 cout << "Successful expresion parse. Next " << type_to_name(lex.top()) << endl; 
#endif
 
 
		// end of tokens but
		// END_STMT expected.
		if(!lex.hasMore() || lex.top().type!=cproc::END_STMT) {
			cleanUp(statements);
			break;
		}
		// eat the END_STMT
		lex.next();
		
 #ifdef DEBUG
 cout << "Next " << type_to_name(lex.top()) << endl; 
#endif
 
 
		if(lex.top().type == ENDPRG) {
			
 #ifdef DEBUG
 cout << "End program num of statements " << statements.size() << endl; 
#endif
 
 
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
		
 #ifdef PARSER_DEBUG
 cout << spaces << "Leaf node: "; 

		printNodeType(stmt->type());
		return;
	}
	else if(stmt->type() == FUNCTION_NODE) {
		Function * f = (Function*)stmt;
		
 cout << spaces << "Function: " << f->name() << endl; 
#endif
 

		for(int i = 0 ; i < f->nArgs() ; i++) {
			printStatement(f->getArg(i), "  "+spaces);
		}
	}
	else if(stmt->type() == ASSIGNMENT) {
		Assign * a = (Assign*)stmt;
		
 #ifdef PARSER_DEBUG
 cout << spaces << "Assign: var: " << a->name() << " " << endl; 
#endif
 

		printStatement(a->rightHand(), "  "+spaces);
	}
	else if(stmt->type() == OPER_NODE) {
		Oper * op = (Oper*)stmt;
		
 #ifdef PARSER_DEBUG
 cout << spaces << "Operator: "; 

		switch(op->operType()) {
			case Oper::ADD: {
				
				cout << "Oper::ADD" << endl; 
#endif
 
				break;
			}
			case Oper::MUL: {
				
 #ifdef PARSER_DEBUG
 cout << "Oper::MUL" << endl; 
#endif
 
break;
			}
			case Oper::DIV: {
				
 #ifdef PARSER_DEBUG
 cout << "Oper::DIV" << endl; 
#endif
 
break;
			}
			case Oper::AND: {
				
 #ifdef PARSER_DEBUG
 cout << "Oper::AND" << endl; 
#endif
 
break;
			}
			case Oper::OR: {
				
 #ifdef PARSER_DEBUG
 cout << "Oper::OR" << endl; 
#endif
 
break;
			}
			case Oper::XOR: {
				
 #ifdef PARSER_DEBUG
 cout << "Oper::XOR" << endl; 
#endif
 
break;
			}
			default: {
				
 #ifdef PARSER_DEBUG
 cout << "Not valid oper." << endl; 
#endif
 
			}			
		}
		
 #ifdef PARSER_DEBUG
 cout << "Left: " << endl; 
#endif
 

		cproc::printStatement(op->left(), "  "+spaces);
		
 #ifdef PARSER_DEBUG
 cout << "Right: " << endl; 
#endif
 

		cproc::printStatement(op->right(), "  "+spaces);
	}
}
#endif