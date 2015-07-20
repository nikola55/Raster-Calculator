#ifndef _LEXER_H_
#define _LEXER_H_

#include <list>
#include <string>
#include "Token.h"

namespace cproc {
	
class Lexer {
	
	std::string input;
	int currPos;
	
	Token currTok;
	std::list<Token> tokBuff;
	
	bool oper();
	bool assign();
	bool paren();
	bool seq();
	bool end();
	bool number();
	bool name();
	bool string();
	bool endprog();
	
	// After this function the 
	// tokBuff contains all the 
	// tokens or error has occured
	bool tokenize();
	
	void trimFront();
	
public:
	
	Lexer(const std::string &input);
	
	// True if more tokens remaining
	// to be read. False otherwise.
	bool hasMore();
	
	// Removes and returns the current
	// token.
	Token next();
	
	// Only Returns the current token.
	Token top();
	
	// Adds the token to the top 
	// of the list, next() must 
	// return this token.
	void pushBack(Token tok);
};
	
}
#endif