#include "../template.hpp"

int main() {
    vector<vector<char>> trees;
    string s;
    while (getline(cin, s)) {
        trees.pb(vector<char>(all(s)));
    }

    int n = sz(trees), m = sz(trees[0]);
    int ans = 0;
    rep(i,0,sz(trees)) {
        rep(j,0,sz(trees[i])) {
            int score = 1;
            rep(k,0,4) {
                int cur = 0;
                int nx = i, ny = j;
                while ((trees[nx][ny] < trees[i][j]) || (nx == i && ny == j)) {
                    ++cur;
                    nx += dx4[k];
                    ny += dy4[k];
                    if (!bound(nx, ny)) {
                        --cur;
                        break;
                    }
                }
                score *= cur;
            }
            ans = max(ans, score);
        }
    }

    cout << ans;
}
