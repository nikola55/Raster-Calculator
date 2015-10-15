#include <Lexer.h>
#include <Parser.h>
#include <Runtime.h>
#include <iostream>

using namespace cproc;
using namespace runtime;
using namespace std;

int main(void) {

	std::string expr = "save(edge(load('C:/Users/nikola.petkanski/mingw/pixes-master/f8iaAQQ.jpg'), 'SOBEL') + 1, 'saved.jpg', 'jpeg');";

	// VOID
	
	Lexer lex = Lexer(expr);
	vector<Node*> stmtList  = parse(lex);

	Runtime rt;

	rt.execute(stmtList);
}
