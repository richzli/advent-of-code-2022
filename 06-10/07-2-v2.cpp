#include "../template.hpp"

typedef struct path_t {
    map<string, path_t*> contents;
    string name;
    ll size;
    bool directory;
    path_t* parent;
    path_t(string _name, ll _size, path_t* _parent) {
        this->name = _name;
        this->size = _size;
        if (_size == -1) {
            this->directory = true;
        } else {
            this->directory = false;
        }
        this->parent = _parent;
    }
} path_t;

int main() {
    string s;
    ll ans = 0;
    getline(cin, s);
    path_t* root = new path_t("", -1, nullptr);
    path_t* cur = root;
    while (true) {
        stringstream ss(s);
        string prompt, cmd, arg;
        ss >> prompt >> cmd;
        if (cmd == "cd") {
            ss >> arg;
            if (arg == "/") {
                cur = root;
            } else if (arg == "..") {
                cur = cur->parent;
            } else {
                if (cur->contents.count(arg) == 0) {
                    cur->contents[arg] = new path_t(arg, -1, cur);
                }
                cur = cur->contents[arg];
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
                if (typ == "dir") {
                    if (cur->contents.count(name) == 0) {
                        cur->contents[name] = new path_t(name, -1, cur);
                    }
                } else {
                    cur->contents[name] = new path_t(name, stoi(typ), cur);
                }
            }
            if (!ok) {
                break;
            }
        }
    }

    vector<ll> wt;
    function<ll(path_t*)> dfs = [&](path_t* path) {
        ll xd = 0;
        for (auto [name, next] : path->contents) {
            if (next->directory) { // is dir;
                xd += dfs(next);
            } else {
                xd += next->size;
            }
        }
        path->size = xd;
        wt.pb(xd);
        return xd;
    };
    dfs(root);

    ans = root->size;
    ll limit = 30000000 - (70000000 - ans);
    for (ll w : wt) {
        if (w >= limit) {
            ans = min(ans, w);
        }
    }

    cout << ans;
}
