#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <string>

namespace cproc {

enum TokenType {
	BEGINPRG,
	ENDPRG,
	STRING,
	NAME,
	NUMBER,
	OR,
	AND,
	XOR,
	NOT,
	PLUS = '+',
	MINUS = '-',
	END_STMT = ';',
	DIV = '/',
	MUL = '*',
	ASSIGN = '=',
	SEQ = ',',
	LPAREN = '(',
	RPAREN = ')'
};

struct Token {
	TokenType type;
	std::string value;
};
#ifdef COMMAND_PROC_DEBUG
inline
std::string type_to_name(const Token &tok) {
	switch(tok.type) {
		case BEGINPRG : { return "BEGINPRG";  break; }
		case ENDPRG : { return "ENDPRG";  break; }
		case STRING: { return "STRING";  break; }
		case NAME : { return "NAME";  break; }
		case NUMBER : { return "NUMBER";  break; }
		case OR : { return "OR";  break; }
		case AND : { return "AND";  break; }
		case XOR : { return "XOR";  break; }
		case NOT : { return "NOT";  break; }
		case PLUS : { return "PLUS";  break; }
		case MINUS : { return "MINUS";  break; }
		case END_STMT : { return "END_STMT";  break; }
		case DIV : { return "DIV";  break; }
		case MUL : { return "MUL";  break; }
		case ASSIGN : { return "ASSIGN";  break; }
		case SEQ : { return "SEQ";  break; }
		case LPAREN : { return "LPAREN";  break; }
		case RPAREN : { return "RPAREN";  break; }
		default : { return "Invalid"; break; }
	}
}
#endif
}
#endif
