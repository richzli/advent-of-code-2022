#include "../template.hpp"

int main() {
    string s;
    vector<vector<char>> stacks;
    while (getline(cin, s), (s[1] != '1')) {
        for (int i = 0; (4 * i + 1) < sz(s); ++i) {
            if (i >= sz(stacks)) {
                stacks.pb(vector<char>());
            }
            if (s[4 * i + 1] != ' ') {
                stacks[i].pb(s[4 * i + 1]);
            }
        }
    }

    rep(i,0,sz(stacks)) {
        reverse(all(stacks[i]));
    }

    getline(cin, s);
    int cnt, from, to;
    while (getline(cin, s)) {
        sscanf(s.c_str(), "move %d from %d to %d", &cnt, &from, &to);
        --from;
        --to;
        cnt = min(cnt, sz(stacks[from]));
        copy(stacks[from].end()-cnt, stacks[from].end(), back_inserter(stacks[to]));
        stacks[from].erase(stacks[from].end()-cnt, stacks[from].end());
    }

    rep(i,0,sz(stacks)) {
        cout << stacks[i].back();
    }
    cout << endl;
}
