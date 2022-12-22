#include "../template.hpp"

int main() {
    string s;

    vector<vector<char>> grid;

    while (getline(cin, s)) {
        if (s.empty()) break;

        grid.pb(vector<char>(all(s)));
        while (sz(grid.back()) < 150) {
            grid.back().pb(' ');
        }
    }

    int n = sz(grid);
    int m = sz(grid[0]);

    map<pair<pii, int>, pair<pii, int>> wrap;

    int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
    map<pii, int> dir = {
        {{0, 1}, 0},
        {{1, 0}, 1},
        {{0, -1}, 2},
        {{-1, 0}, 3}
    };

    function<void(pii, pii, pii, pii)> glue = [&](pii ssp, pii sep, pii esp, pii eep) {
        int dirs = dir[{sgn(sep.first - ssp.first), sgn(sep.second - ssp.second)}];
        int pdirs = (dirs + 3) % 4;
        int dire = dir[{sgn(eep.first - esp.first), sgn(eep.second - esp.second)}];
        int pdire = (dire + 3) % 4;
        for (pii ps = ssp, pe = esp; ps != sep; ps.first += dx[dirs], ps.second += dy[dirs], pe.first += dx[dire], pe.second += dy[dire]) {
            wrap[{ps, pdirs}] = {pe, pdire};
        }
        wrap[{sep, pdirs}] = {eep, pdire};
    };

    glue({49, 49}, {0, 49}, {100, 0}, {149, 0});
    glue({0, 150}, {49, 150}, {149, 99}, {100, 99});
    glue({99, 49}, {50, 49}, {100, 49}, {100, 0});
    glue({50, 100}, {99, 100}, {49, 100}, {49, 149});
    glue({149, -1}, {100, -1}, {0, 50}, {49, 50});
    glue({100, 100}, {149, 100}, {49, 149}, {0, 149});
    glue({199, -1}, {150, -1}, {0, 99}, {0, 50});
    glue({150, 50}, {199, 50}, {149, 50}, {149, 99});

    glue({99, 0}, {99, 49}, {50, 50}, {99, 50});
    glue({200, 49}, {200, 0}, {0, 149}, {0, 100});
    glue({-1, 50}, {-1, 99}, {150, 0}, {199, 0});
    glue({150, 99}, {150, 50}, {199, 49}, {150, 49});
    glue({-1, 100}, {-1, 149}, {199, 0}, {199, 49});
    glue({50, 149}, {50, 100}, {99, 99}, {50, 99});

    getline(cin, s);
    int spos = 0;

    pii pos = {0, 50};
    int dr = 0;
    while (spos < sz(s)) {
        int cnt = 0;
        while (s[spos] >= '0' && s[spos] <= '9') {
            cnt *= 10;
            cnt += s[spos] - '0';
            ++spos;
        }

        rep(i,0,cnt) {
            int nx = pos.first + dx[dr], ny = pos.second + dy[dr], nd = dr;
            if (!bound(nx, ny) || grid[nx][ny] == ' ') {
                auto X = wrap[{{nx, ny}, nd}];
                nx = X.first.first, ny = X.first.second, nd = X.second;
                // cout << "WRAP FROM " << pos.first + dx[dr] << ' ' << pos.second + dy[dr] << ' ' << dr << " TO " << nx << ' ' << ny << ' ' << nd << endl;
            }
            if (grid[nx][ny] == '#') {
                break;
            } else {
                pos = {nx, ny};
                dr = nd;
            }
        }

        if (spos >= sz(s)) break;

        if (s[spos] == 'R') {
            dr += 1;
        } else {
            dr += 3;
        }
        dr %= 4;
        ++spos;
        // cout << pos.first << ' ' << pos.second << ' ' << dr << endl;
    }

    // cout << pos.first << ' ' << pos.second << ' ' << dr << endl;
    cout << 1000 * (pos.first + 1) + 4 * (pos.second + 1) + dr;
}
