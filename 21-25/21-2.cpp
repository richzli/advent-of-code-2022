#include "../template.hpp"

enum op {
    val,
    add,
    sub,
    mul,
    dv,
    eq
};

typedef long double ld;

struct poly {
    vector<ld> coeffs;
    poly() {
        coeffs = {0};
    }
    poly(vector<ld> _coeffs) {
        coeffs = _coeffs;
    }
    poly operator+(const poly& p) const {
        poly ret(vector<ld>(max(sz(coeffs), sz(p.coeffs)), 0));

        rep(i,0,sz(ret.coeffs)) {
            if (i < sz(coeffs)) ret.coeffs[i] += coeffs[i];
            if (i < sz(p.coeffs)) ret.coeffs[i] += p.coeffs[i];
        }

        return ret;
    }
    poly operator-(const poly& p) const {
        poly ret(vector<ld>(max(sz(coeffs), sz(p.coeffs)), 0));

        rep(i,0,sz(ret.coeffs)) {
            if (i < sz(coeffs)) ret.coeffs[i] += coeffs[i];
            if (i < sz(p.coeffs)) ret.coeffs[i] -= p.coeffs[i];
        }

        return ret;
    }
    poly operator*(const poly& p) const {
        poly ret(vector<ld>(sz(coeffs) + sz(p.coeffs) - 1, 0));

        rep(i,0,sz(ret.coeffs)) {
            rep(j,0,sz(coeffs)) {
                if (i-j < 0) break;
                if (i-j >= sz(p.coeffs)) continue;
                ret.coeffs[i] += coeffs[j] * p.coeffs[i-j];
            }
        }

        return ret;
    }
    poly operator/(const poly& p) const {
        if (sz(p.coeffs) > 1) {
            cout << "please no :(";
            return poly();
        }

        poly ret(vector<ld>(sz(coeffs), 0));

        rep(i,0,sz(coeffs)) {
            ret.coeffs[i] = coeffs[i] / p.coeffs[0];
        }

        return ret;
    }
};

struct node {
    string name;
    op operation;
    poly value;
    string fst, snd;
    node(string _name, ll _value) {
        name = _name;
        operation = op::val;
        if (_value == -1)
            value = poly({0, 1});
        else
            value = poly({(ld) _value});
        fst = "";
        snd = "";
    }
    node(string _name, string _operation, string _fst, string _snd) {
        name = _name;
        if (name == "root") {
            operation = op::eq;
        } else if (_operation == "+") {
            operation = op::add;
        } else if (_operation == "-") {
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
        if (name == "humn") {
            ns.pb(node(name, -1));
            nodes[name] = i;
        } else if (s[6] >= '0' && s[6] <= '9') {
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

    function<poly(string)> eval = [&](string name) {
        poly v;
        switch (ns[nodes[name]].operation) {
            case op::val:
                v = ns[nodes[name]].value;
                break;
            case op::add:
                v = eval(ns[nodes[name]].fst) + eval(ns[nodes[name]].snd);
                break;
            case op::sub:
            case op::eq:
                v = eval(ns[nodes[name]].fst) - eval(ns[nodes[name]].snd);
                break;
            case op::mul:
                v = eval(ns[nodes[name]].fst) * eval(ns[nodes[name]].snd);
                break;
            case op::dv:
                v = eval(ns[nodes[name]].fst) / eval(ns[nodes[name]].snd);
                break;
            default:
                v = poly();
        }
        ns[nodes[name]].value = v;
        ns[nodes[name]].operation = op::val;
        return v;
    };

    poly p = eval("root");
    cout << setprecision(0) << fixed;
    cout << - p.coeffs[0] / p.coeffs[1]; // in the form mx+b
}
