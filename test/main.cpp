#include <Lexer.h>
#include <Parser.h>
#include <Runtime.h>
#include <iostream>

using namespace cproc;
using namespace runtime;
using namespace std;

int main(void) {
	
	std::string expr="Gray = load('c:/Program Files/Commons/IE7/Images/sm.jpeg', 'jpeg');"
					 "NOTED = threshold(NOT edge(Gray, LOG));"
					 "ANDED = dilate(dilate(r)) AND erode(erode(r));";
	
	
	Lexer lex = Lexer(expr);
	vector<Node*> parseTree = parse(lex);
	
	Runtime rt;
	
	rt.execute(parseTree);
	
	
	
}