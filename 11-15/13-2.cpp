#include "../template.hpp"

typedef struct lst {
    bool value;
    int x;
    vector<lst> elems;
    lst() {}
    lst(int _x) {
        if (_x < 0) {
            value = false;
        } else {
            value = true;
            x = _x;

        }
    }
    int cmp(lst l2) {
        if (value && l2.value) {
            if (x < l2.x) {
                return -1;
            } else if (x == l2.x) {
                return 0;
            } else {
                return 1;
            }
        } else {
            if (value) {
                elems = vector<lst>(1, lst(x));
            }
            if (l2.value) {
                l2.elems = vector<lst>(1, lst(l2.x));
            }
            int i = 0;
            while (i < min(sz(elems), sz(l2.elems))) {
                int c = elems[i].cmp(l2.elems[i]);
                if (c == -1) {
                    return -1;
                } else if (c == 1) {
                    return 1;
                }
                ++i;
            }
            if (sz(elems) < sz(l2.elems)) {
                return -1;
            } else if (sz(elems) > sz(l2.elems)) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    bool operator<(const lst& l2) {
        return this->cmp(l2) == -1;
    }
    bool operator==(const lst& l2) {
        return this->cmp(l2) == 0;
    }
    bool operator>(const lst& l2) {
        return this->cmp(l2) == 1;
    }
} lst;

int main() {
    string s;
    int pos;
    function<int()> getint = [&]() {
        int ret = 0;
        while (s[pos] >= '0' && s[pos] <= '9' && pos < sz(s)) {
            ret *= 10;
            ret += s[pos] - '0';
            ++pos;
        }
        return ret;
    };
    function<lst()> parse = [&]() {
        lst l = lst(-1);
        while (pos < sz(s)) {
            if (s[pos] == '[') {
                ++pos;
                if (s[pos] != ']')
                    l.elems.pb(parse());
                else {
                    ++pos;
                    break;
                }
            } else {
                l.elems.pb(lst(getint()));
            }

            if (s[pos++] == ']') {
                break;
            }
        }
        return l;
    };

    vector<lst> pkts;
    while (cin >> s) {
        pos = 0;
        pkts.pb(parse());
    }

    lst fst = lst(-1);
    fst.elems.pb(lst(-1));
    fst.elems[0].elems.pb(lst(2));
    lst snd = lst(-1);
    snd.elems.pb(lst(-1));
    snd.elems[0].elems.pb(lst(6));
    
    pkts.pb(fst);
    pkts.pb(snd);

    sort(all(pkts));

    cout << (lower_bound(all(pkts), fst) - pkts.begin() + 1) * (lower_bound(all(pkts), snd) - pkts.begin() + 1);
}
