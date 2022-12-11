#include "../template.hpp"

enum op {
    plus,
    mult,
    sqre
};

typedef struct monkey {
    deque<ll> items;
    op operation;
    ll upd;
    ll test_num;
    int test_true;
    int test_false;
    ll used;
} monkey;

pair<int, monkey*> parse() {
    monkey* m = new monkey();
    int num;
    scanf("Monkey %d:\n", &num);
    string s;
    getline(cin, s);
    stringstream ss(s);
    string s2;
    ss >> s2 >> s2; // starting items:
    while (ss >> s2) {
        if (s2.back() != ',') {
            m->items.pb(stoi(s2));
            break;
        } else {
            m->items.pb(stoi(s2.substr(0, s2.length() - 1)));
        }
    }
    char c;
    scanf("  Operation: new = old %c ", &c);
    cin >> s;
    scanf("\n");
    if (c == '*') {
        if (s == "old") {
            m->operation = op::sqre;
        } else {
            m->operation = op::mult;
            m->upd = stoi(s);
        }
    } else {
        m->operation = op::plus;
        m->upd = stoi(s);
    }
    scanf("  Test: divisible by %lld\n", &(m->test_num));
    scanf("    If true: throw to monkey %d\n", &(m->test_true));
    scanf("    If false: throw to monkey %d\n", &(m->test_false));
    scanf("\n");
    return {num, m};
}

int main() {
    vector<monkey*> monkies;
    int n = 8;
    ll mod = 1;
    rep(i,0,n) {
        monkies.pb(parse().second);
        mod *= monkies.back()->test_num;
    }

    rep(i,0,10000) {
        rep(m,0,n) {
            monkey* mm = monkies[m];
            while (!(monkies[m]->items.empty())) {
                monkies[m]->used++;
                ll item = monkies[m]->items.front(); monkies[m]->items.pop_front();
                if (mm->operation == op::mult) {
                    item *= mm->upd;
                } else if (mm->operation == op::plus) {
                    item += mm->upd;
                } else {
                    item *= item;
                }
                item %= mod;
                if (item % mm->test_num == 0) {
                    monkies[mm->test_true]->items.push_back(item);
                } else {
                    monkies[mm->test_false]->items.push_back(item);
                }
            }
        }
    }

    sort(all(monkies), [](monkey* a, monkey* b){ return a->used > b->used; });
    cout << monkies[0]->used * monkies[1]->used;
}
