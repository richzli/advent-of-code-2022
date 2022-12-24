#include "../template.hpp"

int main() {
    map<char, int> bd = {
        {'v', 0},
        {'>', 1},
        {'^', 2},
        {'<', 3}
    };
    int dx[5] = {1, 0, -1, 0, 0}, dy[5] = {0, 1, 0, -1, 0};
    map<pii, int> dirs = {
        {{1, 0}, 0},
        {{0, 1}, 1},
        {{-1, 0}, 2},
        {{0, -1}, 3}
    };

    set<pair<pii, int>> blizzards;
    string s;
    getline(cin, s);
    int r = 0, m;
    while (getline(cin, s)) {
        if (s[1] == '#') break;
        m = sz(s)-2;
        rep(c,1,sz(s)-1) {
            if (s[c] != '.') {
                blizzards.insert({{r, c-1}, bd[s[c]]});
            }
        }
        ++r;
    }
    int n = r;

    set<pii> pos;
    pos.insert({-1, 0});
    int t = 0;
    while (true) {
        ++t;
        set<pii> pos2;

        set<pair<pii, int>> b2;
        for (auto [bp, d] : blizzards) {
            auto [bx, by] = bp;
            bx = (bx + dx[d] + n) % n;
            by = (by + dy[d] + m) % m;
            b2.insert({{bx, by}, d});
        }
        blizzards.swap(b2);

        bool found = false;
        for (auto [px, py] : pos) {
            rep(k,0,5) {
                int nx = px + dx[k], ny = py + dy[k];
                if (bound(nx, ny) || (nx == -1 && ny == 0)) {
                    int cnt = 0;
                    rep(l,0,4) {
                        cnt += blizzards.count({{nx, ny}, l});
                    }
                    if (cnt == 0) {
                        pos2.insert({nx, ny});
                    }
                } else if (nx == n && ny == m-1) {
                    found = true;
                }
            }
        }
        if (found) break;

        pos.swap(pos2);
    }

    cout << t;
}
