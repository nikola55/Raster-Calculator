#include <Lexer.h>
#include <Parser.h>
#include <Runtime.h>
#include <iostream>

using namespace cproc;
using namespace runtime;
using namespace std;

int main(void) {

	std::string expr = 
	"Img = load('C:/Users/nikola.petkanski/mingw/pixes-master/f8iaAQQ.jpg'); "
	"Edge = edge(Img, 'SOBEL');                                              "
	"print(Edge);                                                            "
	"save(Edge, 'saved.jpg', 'jpeg');                                        ";
	// VOID
	
	Lexer lex = Lexer(expr);
	vector<Node*> stmtList  = parse(lex);
	//printStatement(stmtList[0], "");
	Runtime rt;

	rt.execute(stmtList);
}
