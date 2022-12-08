#include "../template.hpp"

int main() {
    vector<vector<char>> trees;
    string s;
    while (getline(cin, s)) {
        trees.pb(vector<char>(all(s)));
    }
    vector<vector<bool>> see(sz(trees), vector<bool>(sz(trees[0]), false));

    rep(i,0,sz(trees)) {
        int mx = -1;
        rep(j,0,sz(trees[i])) {
            if (trees[i][j] > mx) {
                see[i][j] = true;
                mx = trees[i][j];
            }
        }
        mx = -1;
        for (int j = sz(trees[i])-1; j >= 0; --j) {
            if (trees[i][j] > mx) {
                see[i][j] = true;
                mx = trees[i][j];
            }
        }
    }

    rep(j,0,sz(trees[0])) {
        int mx = -1;
        rep(i,0,sz(trees)) {
            if (trees[i][j] > mx) {
                see[i][j] = true;
                mx = trees[i][j];
            }
        }
        mx = -1;
        for (int i = sz(trees)-1; i >= 0; --i) {
            if (trees[i][j] > mx) {
                see[i][j] = true;
                mx = trees[i][j];
            }
        }
    }

    int ans = 0;
    rep(i,0,sz(trees)) {
        rep(j,0,sz(trees)) {
            ans += (see[i][j] ? 1 : 0);
        }
    }

    cout << ans;
}
