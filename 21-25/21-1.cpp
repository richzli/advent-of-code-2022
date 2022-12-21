#include "../template.hpp"

enum op {
    val,
    add,
    sub,
    mul,
    dv
};

struct node {
    string name;
    op operation;
    ll value;
    string fst, snd;
    node(string _name, ll _value) {
        name = _name;
        operation = op::val;
        value = _value;
        fst = "";
        snd = "";
    }
    node(string _name, string _operation, string _fst, string _snd) {
        name = _name;
        if (_operation == "+")
            operation = op::add;
        else if (_operation == "-") {
            operation = op::sub;
        } else if (_operation == "*") {
            operation = op::mul;
        } else {
            operation = op::dv;
        }
        fst = _fst;
        snd = _snd;
    }
};

int main() {
    string s;

    map<string, int> nodes;
    vector<node> ns;
    int i = 0;
    while (getline(cin, s)) {
        if (s.empty()) continue;

        string name = s.substr(0, 4);
        if (s[6] >= '0' && s[6] <= '9') {
            ns.pb(node(name, stoi(s.substr(6))));
            nodes[name] = i;
        } else {
            stringstream ss(s.substr(6));
            string fst, o, snd;
            ss >> fst >> o >> snd;
            ns.pb(node(name, o, fst, snd));
            nodes[name] = i;
        }
        ++i;
    }

    function<ll(string)> eval = [&](string name) {
        ll v;
        switch (ns[nodes[name]].operation) {
            case op::val:
                v = ns[nodes[name]].value;
                break;
            case op::add:
                v = eval(ns[nodes[name]].fst) + eval(ns[nodes[name]].snd);
                break;
            case op::sub:
                v = eval(ns[nodes[name]].fst) - eval(ns[nodes[name]].snd);
                break;
            case op::mul:
                v = eval(ns[nodes[name]].fst) * eval(ns[nodes[name]].snd);
                break;
            case op::dv:
                v = eval(ns[nodes[name]].fst) / eval(ns[nodes[name]].snd);
                break;
            default:
                v = 0;
        }
        ns[nodes[name]].value = v;
        ns[nodes[name]].operation = op::val;
        return v;
    };

    cout << eval("root");
}
