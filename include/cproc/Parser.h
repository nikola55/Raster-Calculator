#ifndef _PARSER_H_
#define _PARSER_H_
#include <vector>
#include <string>
namespace cproc {
	
	class Node;
	class Lexer;
	
	std::vector<Node*> parse(const Lexer&);
	
	void printStatement(const Node* stmt, const std::string &spaces);
	
}
#endif 