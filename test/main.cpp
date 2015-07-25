#include <Lexer.h>
#include <Parser.h>
#include <Runtime.h>
#include <iostream>

using namespace cproc;
using namespace runtime;
using namespace std;

int main(void) {

	std::string expr="Img = load('poptest.jpg');"
                     "Edge = edge(Img, 'SOBEL');"
                     "save(Edge, 'saved.jpg', 'jpeg');";

	Lexer lex = Lexer(expr);
	vector<Node*> stmtList  = parse(lex);

	Runtime rt;

	rt.execute(stmtList);


}
