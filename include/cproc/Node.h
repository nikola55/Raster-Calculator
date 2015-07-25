#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include <string>
#include <iostream>

namespace cproc {

enum NodeType {
	NODE, NAME_NODE, NUMBER_NODE, STRING_NODE,
	FUNCTION_NODE, OPER_NODE, ASSIGNMENT
};
#ifdef RUNTIME_DEBUG
inline std::string printNodeType(NodeType nt) {
	using std::cout;
	using std::endl;

	switch(nt) {
		case NODE : {
			 return "NODE";
			break;
		}
		case NAME_NODE : {
			return "NAME_NODE";
			break;
		}
		case NUMBER_NODE : {
			return "NUMBER_NODE";
			break;
		}
		case FUNCTION_NODE : {
			return "FUNCTION_NODE";
			break;
		}
		case OPER_NODE : {
			return "OPER_NODE";
			break;
		}
		case ASSIGNMENT : {
			return "ASSIGNMENT";
			break;
		}
		case STRING_NODE : {
			return "STRING_NODE";
			break;
		}
		default :
			return "Invlide ";
	}
}
#endif // DEBUG
class Node {

	Node *l, *r;
	NodeType t;

	bool leaf;

protected :

	Node(NodeType t, bool leaf) :
		t(t), leaf(leaf) {
	}

public :

	virtual NodeType type() const {
		return t;
	}

	virtual void type(NodeType t) {
		this->t = t;
	}

	virtual Node * left() {
		return l;
	}
	virtual Node * right() {
		return r;
	}

	virtual void left(Node* l) {
		this->l = l;
	}
	virtual void right(Node* r) {
		this->r = r;
	}

	virtual bool isLeaf() const {
		return leaf;
	}

};

class Oper : public Node {
public:
	enum OperType {
		ADD, SUB, MUL, DIV, AND, OR, XOR
	};
private:
	OperType t;
public:
	Oper(OperType t) :
		Node(OPER_NODE, false), t(t) {
	}
	OperType operType() const {
		return t;
	}
};

class Function : public Node {
	std::string n;
	std::vector<Node*> argNodes;
public :
	Function(const std::string& name) :
		Node(FUNCTION_NODE, false), n(name) {

	}

	void addArg(Node *arg) {
		argNodes.push_back(arg);
	}

	Node * getArg(int i) {
		if(0 > i || i >= argNodes.size()) {
			return 0;
		}
		return argNodes[i];
	}

	const std::string & name() {
		return n;
	}

	int nArgs() const {
		return argNodes.size();
	}
};

class Assign : public Node {
	std::string n;
	Node * rh;
public:
	Assign(const std::string &n) :
		Node(ASSIGNMENT, false), n(n) {

	}
	const std::string& name() const {
		return n;
	}
	void rightHand(Node *rh) {
		this->rh = rh;
	}
	Node * rightHand() {
		return rh;
	}
};

class Name : public Node {
	std::string n;
public :
	Name(const std::string& n) :
		Node(NAME_NODE, true), n(n) {

	}

	const std::string & name() const {
		return n;
	}

	void name(const std::string &nm) {
		n = nm;
	}
};

class Number : public Node {
	double v;
public:
	Number(double v) :
		Node(NUMBER_NODE, true), v(v) {
	}

	double value() const {
		return v;
	}
};

class String_Node : public Node {
	std::string v;
public:
	String_Node(const std::string &value) :
		Node(STRING_NODE, true), v(value) {
	}

	const std::string & value() const {
		return v;
	}
};
}

#endif
