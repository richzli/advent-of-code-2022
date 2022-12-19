#include "../template.hpp"

int main() {
    string s;

    set<tuple<int, int, int>> pts;
    int n = 0;
    while (getline(cin, s)) {
        if (s.empty()) break;
        vector<string> cs = split(s, ",");
        tuple<int, int, int> p = {stoi(cs[0])+5, stoi(cs[1])+5, stoi(cs[2])+5};
        pts.insert(p);
        n = max(n, max(get<0>(p), max(get<1>(p), get<2>(p))));
    }
    n += 5;

    int dx[6] = {1, -1, 0, 0, 0, 0},
        dy[6] = {0, 0, 1, -1, 0, 0},
        dz[6] = {0, 0, 0, 0, 1, -1};

    int ans = 0;
    set<tuple<int, int, int>> vis;
    queue<tuple<int, int, int>> q;
    q.push({0, 0, 0});
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        auto [x, y, z] = p;
        if (vis.count(p) != 0) continue;
        vis.insert(p);

        rep(k,0,6) {
            int nx = x + dx[k], ny = y + dy[k], nz = z + dz[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n || nz < 0 || nz > n) continue;
            if (pts.count({nx, ny, nz}) != 0) ++ans;
            else q.push({nx, ny, nz});
        }
    }
    
    cout << ans;
}
