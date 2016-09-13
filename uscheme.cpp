// uscheme.cpp

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>

using namespace std;

// Globals ---------------------------------------------------------------------

bool BATCH = false;
bool DEBUG = false;

// Structures ------------------------------------------------------------------

struct Node {
    Node(string Nvalue, Node *Nleft=nullptr, Node *Nright=nullptr) {
		value = Nvalue;
		left = Nleft;
		right = Nright;
    };
    ~Node() {
		if (left) delete left;
		if (right) delete right;
    };

    string value;
    Node * left;
    Node * right;

    friend ostream &operator<<(ostream &os, const Node &n);
};

ostream &operator<<(ostream &os, const Node &n) {
    os << "(Node: value=" << n.value;
    if (n.left != NULL) { 
		os << ", left=" << *n.left;
		//if (n.right != NULL) assuming right will be defined if left is defined
		os << ", right=" << *n.right;
    }
    cout << ")";
    return os;
}
 

// Parser ----------------------------------------------------------------------

string parse_token(istream &s) {
    string token = ""; 
    char c = s.get();
    while (c == ' ') c = s.get(); //should skip whitespaces
    
    //operand or parentheses
    if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/')  
	token += c; 

    //digit
    else if ((c >= '0' && c <= '9') || c == '.') {
		while (1) { //(c > '0' && c < '9') || c == '.') {  //use while loop to read entire digit
		    token += c;
		    c = s.peek();
		    if (!((c >= '0' && c <= '9') || c == '.')) break;
		    c = s.get();
		}
    }
    return token;
}

Node *parse_expression(istream &s) {
    string token = parse_token(s);
    Node *left = NULL;
    Node *right = NULL;

    if (token == "" || token == ")") return NULL;
    else if (token == "(") {
		token = parse_token(s);
		left = parse_expression(s);
		if(left) right = parse_expression(s);
		if(right) parse_token(s);
		//no if left if right used... 
    }
    //else left = NULL; right = NULL;
    return new Node(token, left, right);
}

// Interpreter -----------------------------------------------------------------

void evaluate_r(const Node *n, stack<int> &s) {
    char tmp = n->value[0];
    if((tmp>='0' && tmp<='9') || tmp=='.')
		s.push(stoi(n->value));
    else {
		evaluate_r(n->right, s);
		evaluate_r(n->left, s);
		
		int a = s.top();
		s.pop();
		int b = s.top();
		s.pop();
		if(tmp == '+') s.push(a+b); 
		else if (tmp == '-') s.push(a-b);
		else if (tmp == '*') s.push(a*b);
		else if (tmp == '/') s.push(a/b);
    }
}

int evaluate(const Node *n) {
    stack<int> s;
    evaluate_r(n, s);
    return s.top();
}

// Main execution --------------------------------------------------------------

int main(int argc, char *argv[]) {
    string line;
    int c;

	// Command line argument parsing
    while ((c = getopt(argc, argv, "bdh")) != -1) {
        switch (c) {
            case 'b': BATCH = true; break;
            case 'd': DEBUG = true; break;
            default:
                cerr << "usage: " << argv[0] << endl;
                cerr << "    -b Batch mode (disable prompt)"   << endl;
                cerr << "    -d Debug mode (display messages)" << endl;
                return 1;
        }
    }

    while (!cin.eof()) {
        if (!BATCH) {
            cout << ">>> ";
            cout.flush();
        }

        if (!getline(cin, line)) {
            break;
        }

        if (DEBUG) { cout << "LINE: " << line << endl; }

        stringstream s(line);
        Node *n = parse_expression(s);
        if (DEBUG) { cout << "TREE: " << *n << endl; }

        cout << evaluate(n) << endl;

        delete n;
    }
    
    return EXIT_SUCCESS;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
