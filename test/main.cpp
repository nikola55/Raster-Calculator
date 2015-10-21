#include <Lexer.h>
#include <Parser.h>
#include <Runtime.h>
#include <iostream>

using namespace cproc;
using namespace runtime;
using namespace std;

int main(void) {

	std::string expr = 
	"ExprRes = (1.111*333)-64.00001/22.11;					"
	"print(ExprRes);				";
	// VOID
	
	Lexer lex = Lexer(expr);
	vector<Node*> stmtList  = parse(lex);
	//printStatement(stmtList[0], "");
	Runtime rt;

	rt.execute(stmtList);
}
