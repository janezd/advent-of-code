#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <iterator>
using namespace std;

bool is_number(string const &s) {
    for(string::const_iterator si(s.begin()); si != s.end(); si++) {
        if ((*si < '0') || (*si > '9')) {
            return false;
        }
    }
    return true;
}

class Expression {
public:
    string operation;
    string arg1, arg2;

    Expression()
    {}

    Expression(string const &anop, string const &anarg1)
    : operation(anop), arg1(anarg1)
    {}

    Expression(string const &anop, string const &anarg1, string const &anarg2)
    : operation(anop), arg1(anarg1), arg2(anarg2)
    {}

    Expression(Expression const &o)
    : operation(o.operation), arg1(o.arg1), arg2(o.arg2)
    {}
};

typedef map<string, Expression> Definitions;
typedef map<string, int> Knowns;

void read_expressions(istream &s, Definitions &definitions)
{
    char line[128];
    while(s.getline(line, 128)) {
        vector<string> tokens;
        string sline(line);
        istringstream ssline(sline);
        copy(istream_iterator<string>(ssline), istream_iterator<string>(),
             back_inserter(tokens));
        string const var = tokens.back();
        if (tokens.size() == 3) {
            definitions[var] = Expression("SET", tokens.at(0));
        }
        else if (tokens.size() == 4) {
            definitions[var] = Expression("NOT", tokens.at(1));
        }
        else {
            definitions[var] = Expression(tokens.at(1), tokens.at(0), tokens.at(2));
        }
    }
}


int solve_for(string const &var, Definitions const &definitions, Knowns &knowns)
{
    #define SOLVE(a) (solve_for(expr.arg##a, definitions, knowns))

    int res;
    if (is_number(var)) {
        stringstream(var) >> res;
        return res;
    }
    Knowns::const_iterator vi = knowns.find(var);
    if (vi != knowns.end()) {
        return vi->second;
    }

    Expression const &expr = definitions.at(var);
    if (expr.operation == "SET") {
        res = knowns[var] = SOLVE(1);
    }
    else if (expr.operation == "NOT") {
        res = knowns[var] = ~SOLVE(1);
    }
    else if (expr.operation == "AND") {
        res = knowns[var] = SOLVE(1) & SOLVE(2);
    }
    else if (expr.operation == "OR") {
        res = knowns[var] = SOLVE(1) | SOLVE(2);
    }
    else if (expr.operation == "LSHIFT") {
        res = knowns[var] = SOLVE(1) << SOLVE(2);
    }
    else /* if (expr.operation == "RSHIFT") */ {
        res = knowns[var] = SOLVE(1) >> SOLVE(2);
    }
    return res;
}

int main(int argc, char *argv[]) {
    Definitions definitions;
    Knowns knowns;
    read_expressions(cin, definitions);

    int a = solve_for("a", definitions, knowns);
    cout << a << endl;
    knowns.clear();

    knowns["b"] = a;
    a = solve_for("a", definitions, knowns);
    cout << a << endl;
}
