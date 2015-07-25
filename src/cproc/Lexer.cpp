#include <Lexer.h>
#include <cctype>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
using namespace std;
cproc::Lexer::Lexer(const std::string &input) :
			input(input), currPos(0) {
	currTok.type = BEGINPRG;
	currTok.value = "";
	tokenize();
	currTok = tokBuff.front();
}
bool cproc::Lexer::hasMore() {
	return tokBuff.size() != 0;
}
cproc::Token cproc::Lexer::next() {
	if(tokBuff.size() == 0) {
		throw std::range_error("Lexer::next() end of tokens.");
	}
	Token curr = tokBuff.front();
	tokBuff.pop_front();
	return curr;
}
cproc::Token cproc::Lexer::top() {
	if(tokBuff.size() == 0) {
		throw std::range_error("Lexer::top() end of tokens.");
	}
	return tokBuff.front();
}
void cproc::Lexer::pushBack(cproc::Token tok) {
	if(hasMore()) {
		tokBuff.push_front(tok);
	} else throw std::range_error("Lexer::pushBack(cproc::Token tok) lexer not hasMore.");
}
bool cproc::Lexer::tokenize() {
	while(currTok.type != ENDPRG) {
		trimFront();
		bool res = string();
		if(res) continue;
		res = name();
		if(res) continue;
		res = oper();
		if(res) continue;
		res = number();
		if(res) continue;
		res = assign();
		if(res) continue;
		res = paren();
		if(res) continue;
		res = seq();
		if(res) continue;
		res = endprog();
		if(res) continue;
		res = end();
		continue;
		throw runtime_error("Not valid token." +
		std::string(
		input.begin() + currPos - 5,
		input.begin() + currPos + 5));
	}
}
bool cproc::Lexer::endprog() {
	if(input.size() == currPos) {
		currTok.type = ENDPRG;
		currTok.value = "";
		tokBuff.push_back(currTok);
		return true;
	}
	return false;
}
static std::string KeyWords[4] = {
	"OR", "NOT", "XOR", "AND"
};
inline
char getEscapeEnt(char ch) {
	switch(ch) {
		case 't' : return '\t';
		case 'r' : return '\r';
		case 'n' : return '\n';
		case '\'': return '\'';
		case '"' : return '"';
		case '\\': return '\\';
		default :
			throw std::runtime_error("getEscapeEnt(char ch) invalid ch");
	}
}
bool cproc::Lexer::string() {
	if(currPos == input.size())
		return false;
	int tmpPos = currPos;
	if(!(input[tmpPos] == '"' ||
		input[tmpPos] == '\'')) {
		return false;
	}
	char quot = input[tmpPos++];
	std::vector<char> s;
	for(;;) {
		if(tmpPos == input.size()) {
			throw runtime_error("Not terminated string");
		}
		char currChar = input[tmpPos++];
		if(currChar == '\\' && tmpPos != input.size()) { // check if escape sequence
			char nextChar = input[tmpPos];
			if(!(nextChar == 't' ||
				 nextChar == 'r' ||
				 nextChar == 'n' ||
				 nextChar == '\'' ||
				 nextChar == '"'  ||
				 nextChar == '\\')) {
				throw std::runtime_error("Invalid escape sequence");
			}
			s.push_back(getEscapeEnt(nextChar));
			tmpPos++;
			continue;
		}
		if(currChar == quot) { // end of the string
			break;
		}
		if( ! (currChar >= 32 || currChar == 9 ||
			 currChar == 12 || currChar == 13)) {
			throw std::runtime_error("Invalid characters in string.");
		}
		s.push_back(currChar);
	}
	currTok.type = STRING;
	currTok.value = std::string(s.begin(), s.end());
	currPos = tmpPos;
	tokBuff.push_back(currTok);
	return true;
}
bool cproc::Lexer::name() {
	if(currPos == input.size())
		return false;
	int tmpPos = currPos;
	char ch = input[tmpPos];
	if(!(
		isalpha(ch) ||
		ch == '_' || ch == '$' ||
		ch == '#' || ch == '@'
		)) return false;
	std::vector<char> name;
	name.push_back(ch);
	tmpPos++;
	if(tmpPos == input.size()) {
		goto success;
	}
	ch = input[tmpPos];
	while(isalnum(ch) || ch == '_') {
		name.push_back(ch);
		tmpPos++;
		if(tmpPos == input.size()) {
			goto success;
		}
		ch = input[tmpPos];
	}
	success : {
		std::string nm = std::string(name.begin(), name.end());
		if(std::find(KeyWords, KeyWords+4, nm) != KeyWords+4) {
			return false;
		}
		currPos = tmpPos;
		currTok.type = NAME;
		currTok.value = nm;
		tokBuff.push_back(currTok);
		return true;
	}
}
inline
std::vector<char> digitSequence(const std::string &input,
								int currPos) {
	std::vector<char> ds;
	if(currPos >= input.size())
		return ds;
	char ch = input[currPos];
	while(isdigit(ch)) {
		ds.push_back(ch);
		currPos++;
		if(currPos >= input.size())
			break;
		ch = input[currPos];
	}
	return ds;
}
bool cproc::Lexer::number() {
	if(currPos >= input.size())
		return false;
	int tmpPos = currPos;
	std::vector<char> num;
	std::vector<char> whole = digitSequence(input, tmpPos);
	std::vector<char> fraction;
	char ch;
	if(whole.size() == 0)
		return false;
	tmpPos+=whole.size();
	num.insert(num.end(), whole.begin(), whole.end());
	if(tmpPos >= input.size()) {
		goto success;
	}
	ch = input[tmpPos];
	if(ch != '.') goto success;
	num.push_back(ch);
	tmpPos++;
	fraction = digitSequence(input, tmpPos);
	if(fraction.size() == 0) {
		return false;
	}
	tmpPos += fraction.size();
	num.insert(num.end(), fraction.begin(), fraction.end());
	success : {
		currPos=tmpPos;
		currTok.type = NUMBER;
		currTok.value = std::string(num.begin(), num.end());
		tokBuff.push_back(currTok);
		return true;
	}
}
bool cproc::Lexer::end() {
	if(currPos >= input.size())
		return false;
	if(input[currPos] == ';') {
		currPos++;
		currTok.type = END_STMT;
		currTok.value = "";
		tokBuff.push_back(currTok);
		return true;
	}
	return false;
}
bool cproc::Lexer::seq() {
	if(currPos >= input.size())
		return false;
	if(input[currPos] == ',') {
		currPos++;
		currTok.type = SEQ;
		currTok.value = "";
		tokBuff.push_back(currTok);
		return true;
	}
	return false;
}
bool cproc::Lexer::paren() {
	if(currPos >= input.size())
		return false;
	if(input[currPos] == '(' ||
	   input[currPos] == ')' ) {
		currPos++;
		currTok.type = TokenType(input[currPos-1]);
		currTok.value = "";
		tokBuff.push_back(currTok);
		return true;
	}
	return false;
}
bool cproc::Lexer::assign() {
	if(currPos >= input.size())
		return false;
	if(input[currPos] == '=') {
		currPos++;
		currTok.type = ASSIGN;
		currTok.value = "";
		tokBuff.push_back(currTok);
		return true;
	}
	return false;
}
bool cproc::Lexer::oper() {
	if(currPos >= input.size())
		return false;
	int startPosition = currPos;
	char ch = input[currPos];
	if(ch == '+' || ch == '-' ||
	   ch == '*' || ch == '/' ) {
		currTok.value = "";
		currTok.type = TokenType(ch);
		currPos+=1;
		tokBuff.push_back(currTok);
		return true;
	}
	int tempCurrPos = currPos;
	if((input.size() - tempCurrPos) >= 3) {
		char next1 = input[tempCurrPos++];
		char next2 = input[tempCurrPos++];
		if(next1 == 'O' && next2 == 'R') {
			currTok.type = OR;
			currTok.value = "";
			currPos = tempCurrPos;
			tokBuff.push_back(currTok);
			return true;
		}
		tempCurrPos = currPos;
	}
	if((input.size() - currPos) >= 4) {
		char next1 = input[tempCurrPos++];
		char next2 = input[tempCurrPos++];
		char next3 = input[tempCurrPos++];
		currTok.value = "";
		currPos = tempCurrPos;
		if(next1 == 'A' && next2 == 'N' && next3 == 'D') {
			currTok.type = AND;
			tokBuff.push_back(currTok);
			return true;
		} else if (next1 == 'X' && next2 == 'O' && next3 == 'R') {
			currTok.type = XOR;
			tokBuff.push_back(currTok);
			return true;
		} else if(next1 == 'N' && next2 == 'O' && next3 == 'T') {
			currTok.type = NOT;
			tokBuff.push_back(currTok);
			return true;
		} else {
			currPos = startPosition;
			return false;
		}
	}
	return false;
}
inline bool iswhitespace(char ch) {
	return ch == ' ' ||
		   ch == '\r' ||
		   ch == '\n' ||
		   ch == '\t';
}
void cproc::Lexer::trimFront() {
	if(currPos >= input.size())
		return;
	while(iswhitespace(input[currPos])) {
		currPos++;
		if(currPos >= input.size())
			return;
	}
}
