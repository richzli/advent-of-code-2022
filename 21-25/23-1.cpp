#include "../template.hpp"

int main() {
    string s;
    int r = 0;
    set<pii> elves;
    while (getline(cin, s)) {
        if (s.empty()) continue;
        rep(c,0,sz(s)) {
            if (s[c] == '#') {
                elves.insert({r, c});
            }
        }
        ++r;
    }

    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    int kx[4] = {0, 0, 1, 1}, ky[4] = {1, 1, 0, 0};

    rep(i,0,10) {
        map<pii, pii> move;
        set<pii> dir, dir2;
        for (auto [r, c] : elves) {
            int go = false;
            rep(j,0,8) {
                int nr = r + dx8[j], nc = c + dy8[j];
                if (elves.count({nr, nc}) > 0) {
                    go = true;
                }
            }
            if (go) rep(j,0,4) {
                int nr = r + dx[(i + j) % 4], nc = c + dy[(i + j) % 4];
                bool ok = true;
                rep(k,-1,2) {
                    if (elves.count({nr+kx[(i+j)%4]*k, nc+ky[(i+j)%4]*k}) == 1) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    move[{r, c}] = {nr, nc};
                    if (dir.count({nr, nc}) == 1) {
                        dir2.insert({nr, nc});
                    } else {
                        dir.insert({nr, nc});
                    }
                    break;
                }
            }
            if (move.count({r, c}) == 0) {
                move[{r, c}] = {r, c};
            }
        }

        set<pii> e6;
        for (auto e : elves) {
            if (move[e] == e) {
                e6.insert(e);
            } else if (dir2.count(move[e]) > 0) {
                e6.insert(e);
            } else {
                e6.insert(move[e]);
            }
        }
        elves.swap(e6);
    }

    int mnr = elves.begin()->first,
        mxr = elves.begin()->first,
        mnc = elves.begin()->second,
        mxc = elves.begin()->second;
    
    for (auto [r, c] : elves) {
        mnr = min(mnr, r);
        mxr = max(mxr, r);
        mnc = min(mnc, c);
        mxc = max(mxc, c);
    }

    cout << ((mxr - mnr + 1) * (mxc - mnc + 1) - sz(elves));
}
