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
    Node(string value, Node *left=nullptr, Node *right=nullptr) {
	value = value; left = left; right = right;
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
    if (n.left != NULL) os << ", left=" << n.left;
    if (n.right != NULL) os << ", right=" << n.right;
    os << ")" << endl;
    return os;
}
 

// Parser ----------------------------------------------------------------------

string parse_token(istream &s) {
    string token = ""; 
    char c = s.peek();
    while (c == ' ') c = s.get(); //should skip whitespaces
    //c = s.get();
    if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/') 
	token += c;
    else if ((c > '0' && c < '9') || c == '.') {
	while ((c > '0' && c < '9') || c == '.') {
	    token =+ c;
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
	right = parse_expression(s);
	//if (right) parse_token(s)
	//no if left if right used... 
    }
    //else left = NULL; right = NULL;
    return new Node(token, left, right);
}

// Interpreter -----------------------------------------------------------------

void evaluate_r(const Node *n, stack<int> &s) {
}

int evaluate(const Node *n) {
    return 0;
}

// Main execution --------------------------------------------------------------

int main(int argc, char *argv[]) {
    string line;
    int c;

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

    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
