#include "../template.hpp"

int sgn(int x) {
    return x == 0 ? 0 : (x/abs(x));
}

pii mov(int dx, int dy) {
    if (dx == 0) {
        if (abs(dy) >= 2) {
            return {0, sgn(dy)};
        } else {
            return {0, 0};
        }
    } else if (abs(dx) >= 2) {
        if (dy == 0) {
            return {sgn(dx), 0};
        } else {
            return {sgn(dx), sgn(dy)};
        }
    } else { // dx = 1
        if (abs(dy) >= 2) {
            return {sgn(dx), sgn(dy)};
        } else {
            return {0, 0};
        }
    }
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
    int hx = 0, hy = 0;
    int tx = 0, ty = 0;
    pos.insert({0, 0});
    while (getline(cin, s)) {
        stringstream ss(s);
        char d;
        int t;
        ss >> d >> t;

        rep(i,0,t) {
            hx += dx4[dir[d]];
            hy += dy4[dir[d]];

            pii m = mov(hx-tx, hy-ty);
            tx += m.first;
            ty += m.second;
            pos.insert({tx, ty});
        }
    }
    cout << sz(pos);
}
