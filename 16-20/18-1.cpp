#include "../template.hpp"

int main() {
    string s;

    set<tuple<int, int, int>> pts;
    while (getline(cin, s)) {
        if (s.empty()) break;
        vector<string> cs = split(s, ",");
        pts.insert({stoi(cs[0]), stoi(cs[1]), stoi(cs[2])});
    }

    int dx[6] = {1, -1, 0, 0, 0, 0},
        dy[6] = {0, 0, 1, -1, 0, 0},
        dz[6] = {0, 0, 0, 0, 1, -1};

    int ans = 0;
    for (auto [x, y, z] : pts) {
        rep(i,0,6) {
            if (pts.find({x + dx[i], y + dy[i], z + dz[i]}) == pts.end()) {
                ++ans;
            }
        }
    }

    cout << ans;
}
