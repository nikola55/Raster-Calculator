#include <Lexer.h>
#include <Parser.h>
#include <Runtime.h>
#include <iostream>

using namespace cproc;
using namespace runtime;
using namespace std;

int main(void) {

	std::string expr="Img = load('C:/Users/Nikola/CodeBlocksProjects/pixes_shared/a3LdE97_460s.jpg', 'jpeg');"
                     "Edge = edge(Img);"
                     "save(Edge, 'saved.jpg', 'jpeg');";

	Lexer lex = Lexer(expr);
	vector<Node*> stmtList  = parse(lex);

	Runtime rt;

	rt.execute(stmtList);


}
