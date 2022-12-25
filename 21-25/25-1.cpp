#include "../template.hpp"

map<char, int> val = {
    {'=', -2},
    {'-', -1},
    {'0', 0},
    {'1', 1},
    {'2', 2}
};
string val2 = "=-012";

ll stox(string s) {
    ll place = 1;
    ll ans = 0;
    rep(i,0,sz(s)) {
        ans += place * val[s[sz(s)-i-1]];
        place *= 5;
    }
    return ans;
}

string dtos(ll x) {
    ll place = 1;
    ll y = 0;
    int digits = 0;
    while (x >= y) {
        y += 2 * place;
        place *= 5;
        ++digits;
    }

    x += y;
    string ret = "";
    while (x > 0) {
        ret += val2[x % 5];
        x /= 5;
    }
    reverse(all(ret));
    while (ret[0] == '0') {
        ret = ret.substr(1);
    }
    return ret;
}

int main() {
    string s;
    ll sm = 0;
    while (getline(cin, s)) {
        if (s.empty()) break;
        sm += stox(s);
    }
    cout << dtos(sm);
}
