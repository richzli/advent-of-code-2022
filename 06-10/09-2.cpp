#include "../template.hpp"

int sgn(int x) {
    return x == 0 ? 0 : (x/abs(x));
}

pii mov(int dx, int dy) {
    if (abs(dx) <= 1 && abs(dy) <= 1) {
        return {0, 0};
    }
    return {sgn(dx), sgn(dy)};
}

map<char, int> dir = {
    {'U', 0},
    {'D', 2},
    {'L', 1},
    {'R', 3}
};

int main() {
    string s;
    set<pii> pos;
    vector<pii> rope(10, {0, 0});
    pos.insert({0, 0});
    while (getline(cin, s)) {
        stringstream ss(s);
        char d;
        int t;
        ss >> d >> t;
        
        rep(i,0,t) {
            rope[0].first += dx4[dir[d]];
            rope[0].second += dy4[dir[d]];

            rep(k,1,10) {
                pii m = mov(rope[k-1].first-rope[k].first, rope[k-1].second-rope[k].second);
                rope[k].first += m.first;
                rope[k].second += m.second;
            }

            pos.insert(rope[9]);
        }
    }
    cout << sz(pos);
}
