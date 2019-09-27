#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct expression;

enum exptype { literal, add, subtract, mult, var };

ostream& operator<<(ostream& out, const exptype& t) {
    switch (t) {
        case exptype::literal:
            out << "literal";
            break;
        case exptype::add:
            out << "add";
            break;
        case exptype::subtract:
            out << "subtract";
            break;
        case exptype::mult:
            out << "multiply";
            break;
        case exptype::var:
            out << "var";
            break;
    }

    return out;
}

unordered_map<string, expression*> vars;

struct expression {
    expression(int value)
        : name(""),
          value(value),
          type(exptype::literal),
          _1(nullptr),
          _2(nullptr) {}
    expression(string name)
        : name(name), value(0), type(exptype::var), _1(nullptr), _2(nullptr) {}
    expression(expression* _1, expression* _2, exptype type)
        : name(""), value(0), type(type), _1(_1), _2(_2) {}
    string name;
    int value;

    expression* _1;
    expression* _2;

    exptype type;

    static forward_list<expression> exps;

    int _calc(int v1, int v2) const {
        switch (type) {
            case exptype::var:
            case exptype::literal:
                return 0;
            case exptype::add:
                return v1 + v2;
            case exptype::subtract:
                return v1 - v2;
            case exptype::mult:
                return v1 * v2;
        }
    }

    bool eval_recursive(unordered_set<string>& alreadyEvaled,
                        int& value) const {
        switch (type) {
            case exptype::literal:
                value = this->value;
                return true;
            case exptype::var: {
                if (!alreadyEvaled.insert(name).second) return false;
                auto entry = vars.find(name);
                if (entry == vars.end()) return false;

                if (!entry->second->eval_recursive(alreadyEvaled, value))
                    return false;
                alreadyEvaled.erase(name);
                return true;
            }
            case exptype::mult:
            case exptype::subtract:
            case exptype::add: {
                int value1, value2;
                if (name != "") {
                    if (!alreadyEvaled.insert(name).second) return false;
                }
                if (_1->eval_recursive(alreadyEvaled, value1) &&
                    _2->eval_recursive(alreadyEvaled, value2)) {
                    value = _calc(value1, value2);
                    if (name != "") alreadyEvaled.erase(name);
                    return true;
                }
                if (name != "") alreadyEvaled.erase(name);

                return false;
            }
        }
    }
};

ostream& operator<<(ostream& out, const expression& exp) {
    out << "name: " << exp.name << ", value: " << exp.value
        << ", type: " << exp.type << ", _1: " << exp._1 << ", _2: " << exp._2;

    return out;
}

forward_list<expression> expression::exps;

bool eval_expresion(const expression& exp, int& value) {
    unordered_set<string> alreadyEvaled;
    // cout << "eval: " << exp << "\n";
    return exp.eval_recursive(alreadyEvaled, value);
}

void eval_print(string var) {
    // cout << "print: " << var << endl;
    auto element = vars.find(var);
    if (element != vars.end()) {
        int value;
        // cout << "p: " << element->second << "\n";
        if (eval_expresion(*element->second, value))
            cout << value << "\n";
        else
            cout << "UNDEF\n";
    } else {
        cout << "UNDEF\n";
    }
}

void eval_reset() {
    expression::exps.clear();
    vars.clear();
}

struct node {
    node(string data, node* prev) : data(data), exp(nullptr), next(nullptr) {
        this->prev = prev;
        prev->next = this;
    }

    node(string data)
        : data(data), exp(nullptr), next(nullptr), prev(nullptr) {}

    string data;
    expression* exp;

    node* next;
    node* prev;
};

ostream& operator<<(ostream& out, const node& n) {
    out << "data: " << /*n.data <<*/ ", exp: ";
    if (n.exp)
        out << *n.exp;
    else
        out << "none";

    return out;
}

node* _eval_simple_assignment(node* start, node* end) {
    // multiplication first
    for (node* it = start; it != end->next; it = it->next) {
        if (it->data == "*") {
            expression::exps.emplace_front(it->prev->exp, it->next->exp,
                                           exptype::mult);
            it->prev->exp = &expression::exps.front();
            it->prev->next = it->next->next;
            if (it->next->next) it->next->next->prev = it->prev;
            if (it->next == end) end = it->prev;
            it = it->prev;
        }
    }

    // addition second
    for (node* it = start; it != end->next; it = it->next) {
        //         cout << ", " << it->data << endl;
        if (it->data == "+" || it->data == "-") {
            expression::exps.emplace_front(
                it->prev->exp, it->next->exp,
                it->data == "+" ? exptype::add : exptype::subtract);
            // cout << "new exp: " << expression::exps.front() << endl;
            it->prev->exp = &expression::exps.front();
            it->prev->next = it->next->next;
            if (it->next->next) it->next->next->prev = it->prev;
            if (it->next == end) end = it->prev;
            it = it->prev;
        }
    }

    // cout << "eval_simple: " << *end->exp << endl;

    return end;
}

node* _eval_parens(node* start) {
    // cout << "_eval_parens: " << *start << endl;
    for (node* it = start->next; it != nullptr; it = it->next) {
        // cout << *it << endl;
        if (it->data == ")") {
            node* result = _eval_simple_assignment(start->next, it->prev);
            if (start->prev) start->prev->next = result;
            result->prev = start->prev;

            if (it->next) it->next->prev = result;
            result->next = it->next;
            // cout << "_eval_parens result: " << result << endl;
            return result;
        } else if (it->data == "(") {
            it = _eval_parens(it);
        }
    }

    return nullptr;
}

void eval_assignment(string name, vector<string>& tokens) {
    // cout << "var: " << name << endl << "tokens: ";
    // for (string& s : tokens) {
    //     cout << s << ", ";
    // }
    // cout << endl;
    node* start;
    forward_list<node> nodes;
    nodes.emplace_front(tokens.front());
    start = &nodes.front();
    for (uint i = 1; i < tokens.size(); ++i) {
        nodes.emplace_front(tokens[i], &nodes.front());
    }

    // parse vars and literals to expresions
    for (node* it = start; it != nullptr; it = it->next) {
        //        cout << it->data << endl;
        if (isdigit(it->data.front()) ||
            (it->data.size() > 1 && it->data.front() == '-')) {
            expression::exps.emplace_front(stoi(it->data));
            it->exp = &expression::exps.front();
            it->data.clear();
        } else if (it->data.front() != '+' && it->data.front() != '-' &&
                   it->data.front() != '*' && it->data.front() != '(' &&
                   it->data.front() != ')') {
            expression::exps.emplace_front(it->data);
            it->exp = &expression::exps.front();
            it->data.clear();
        }
    }

    while (start->data == "(") start = _eval_parens(start);

    node* end = nullptr;

    for (node* it = start; it; it = it->next) {
        // cout << *it << endl;

        if (it->data == "(") {
            it = _eval_parens(it);
        }
        if (it->next == nullptr) {
            end = it;
        }
    }

    // for (node* it = start; it; it = it->next) cout << *it << endl;

    vars[name] = _eval_simple_assignment(start, end)->exp;
}

string trim(string string) {
    while (string.size() > 0 && string.front() <= ' ') {
        string = string.substr(1);
    }

    while (string.size() > 0 && string.back() <= ' ') {
        string.pop_back();
    }

    return string;
}

int main() {
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        line = trim(line);

        if (line == "RESET") {
            eval_reset();
        } else if (line.size() > 5 && line.substr(0, 5) == "PRINT" &&
                   line[5] <= ' ') {
            string name = line.substr(5, line.size());
            int firstNonW = name.find_first_not_of(' ');
            int lastNonW = name.find_last_not_of(' ');
            name = name.substr(firstNonW, lastNonW - firstNonW + 1);
            eval_print(name);
        } else if (line.find_first_not_of(' ') != -1) {
            int pos = line.find(":");
            string name = line.substr(0, pos);
            int firstNonW = name.find_first_not_of(' ');
            int lastNonW = name.find_last_not_of(' ');
            name = name.substr(firstNonW, lastNonW - firstNonW + 1);

            pos = line.find("=");
            string raw = line.substr(pos + 1, line.size());
            raw += ' ';
            //            cout << raw << endl;
            vector<string> tokens;
            tokens.reserve(10);

            for (uint i = 0; i < raw.size(); ++i) {
                // cout << raw[i] << endl;

                switch (raw[i]) {
                    case '*':
                    case '+':
                    case ')':
                    case '(':
                        tokens.push_back({raw[i]});
                        break;
                    case '-':
                        if (tokens.size() > 0) {
                            if (tokens.back() == "*" || tokens.back() == "+" ||
                                tokens.back() == "-" || tokens.back() == "(") {
                                int numberEnd =
                                    raw.find_first_not_of("0123456789", i + 1);
                                tokens.push_back(raw.substr(i, numberEnd - i));
                                i = numberEnd - 1;
                            } else {
                                tokens.push_back("-");
                            }
                        } else if (tokens.size() == 0) {
                            int numberEnd =
                                raw.find_first_not_of("0123456789", i + 1);
                            tokens.push_back(raw.substr(i, numberEnd - i));
                            i = numberEnd - 1;
                        } else {
                            tokens.push_back("-");
                        }
                        break;
                    default:
                        if (raw[i] > ' ') {
                            if (isdigit(raw[i])) {
                                int numberEnd =
                                    raw.find_first_not_of("0123456789", i);
                                tokens.push_back(raw.substr(i, numberEnd - i));
                                i = numberEnd - 1;
                            } else {
                                int varEnd = raw.find_first_not_of(
                                    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL"
                                    "MNOP"
                                    "QRSTUVWXYZ1234567890",
                                    i);
                                tokens.push_back(raw.substr(i, varEnd - i));
                                i = varEnd - 1;
                            }
                        }
                }
            }

            eval_assignment(name, tokens);
        }
    }

    return 0;
}
