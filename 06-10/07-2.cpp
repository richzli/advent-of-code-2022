#include "../template.hpp"

int main() {
    string s;
    ll ans = 0;
    getline(cin, s);
    map<vector<string>, vector<string>> tree;
    map<vector<string>, int> size;
    map<vector<string>, bool> directory;
    vector<string> cur;
    while (true) {
        stringstream ss(s);
        string prompt, cmd, arg;
        ss >> prompt >> cmd;
        if (cmd == "cd") {
            ss >> arg;
            if (arg == "/") {
                cur.clear();
            } else if (arg == "..") {
                cur.pop_back();
            } else {
                cur.pb(arg);
            }
            if (!getline(cin, s)) {
                break;
            }
        } else { // cmd == "ls"
            bool ok = false;
            while (getline(cin, s)) {
                if (s[0] == '$') {
                    ok = true;
                    break;
                }

                ss = stringstream(s);
                string typ, name;
                ss >> typ >> name;
                tree[cur].pb(name);
                cur.pb(name);
                if (typ == "dir") {
                    size[cur] = -1;
                    directory[cur] = true;
                } else {
                    size[cur] = stoi(typ);
                    directory[cur] = false;
                }
                cur.pop_back();
            }
            if (!ok) {
                break;
            }
        }
    }

    function<int(vector<string>)> dfs = [&](vector<string> path) {
        ll xd = 0;
        for (string next : tree[path]) {
            path.pb(next);
            if (directory[path] == true) { // is dir;
                xd += dfs(path);
            } else {
                xd += size[path];
            }
            path.pop_back();
        }
        size[path] = xd;
        return xd;
    };
    dfs(vector<string>());

    ans = size[vector<string>()];
    int limit = 30000000 - (70000000 - ans);
    for (auto [path, xd] : size) {
        if (xd >= limit && directory[path]) {
            ans = min(ans, (ll) xd);
        }
    }

    cout << ans;
}
