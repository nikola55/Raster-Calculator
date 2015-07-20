#include <Lexer.h>
#include <Parser.h>
#include <iostream>

using namespace cproc;
using namespace std;

int main(void) {
	
	std::string expr="Gray = load();"
					 "NOTED = threshold(NOT edge(Gray, LOG));"
					 "ANDED = dilate(dilate(r)) AND erode(erode(r));";
	
	
	Lexer lex = Lexer(expr);
	
	// while(lex.hasMore()) {
		// cout << type_to_name(lex.next()) << endl;
	// }
	
	vector<Node*> parseTree = parse(lex);
	for(int i = 0 ; i < parseTree.size() ; i++) {
		printStatement(parseTree[i], "");
	}
}