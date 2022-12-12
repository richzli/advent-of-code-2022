#include "../template.hpp"

int main() {
    vector<vector<char>> grid;
    string s;
    while (cin >> s) {
        grid.pb(vector<char>(all(s)));
    }

    int sx = 0, sy = 0;
    int n = sz(grid), m = sz(grid[0]);
    rep(i,0,sz(grid)) {
        rep(j,0,sz(grid[i])) {
            if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
            }
        }
    }

    function<int(int, int)> height = [&](int x, int y) {
        char c = grid[x][y];
        if (c == 'S') {
            return 0;
        } else if (c == 'E') {
            return 25;
        } else {
            return c - 'a';
        }
    };

    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    deque<pii> q;
    q.pb({sx, sy});
    dist[sx][sy] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop_front();
        if (vis[x][y]) {
            continue;
        }
        vis[x][y] = true;
        int d = dist[x][y], h = height(x, y);
        rep(k,0,4) {
            int nx = x + dx4[k], ny = y + dy4[k];
            if (bound(nx, ny)) {
                int h2 = height(nx, ny);
                if (h2 <= h + 1) {
                    dist[nx][ny] = min(dist[nx][ny], d + 1);
                    q.pb({nx, ny});
                }
            }
        }
    }

    rep(i,0,n) {
        rep(j,0,m) {
            if (grid[i][j] == 'E') {
                cout << dist[i][j];
            }
        }
    }
}
