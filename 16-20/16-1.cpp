#include "../template.hpp"

vi perm(int n, int k) {
    // 0 <= k < n!
    vi x, ans;
    rep(i,0,n) {
        x.pb(i);
    }
    for (int i = n; i > 0; --i) {
        int y = k % i;
        k /= i;
        ans.pb(x[y]);
        x.erase(x.begin() + y);
    }
    return ans;
}

struct state {
    string node;
    set<string> on;
    int flow;
    state(string _node, set<string> _on, int _flow) {
        node = _node;
        on = _on;
        flow = _flow;
    }
    bool operator<(const state& s2) const {
        if (node != s2.node) return node < s2.node;
        if (on != s2.on) return on < s2.on;
        if (flow != s2.flow) return flow < s2.flow;
        return false;
    }
};

int main() {
    map<string, int> f;
    map<string, string> p;
    map<string, set<string>> g;
    vector<string> ns, nz;
    map<string, int> nz2;

    string s;
    while (getline(cin, s)) {
        if (s.empty()) break;
        vector<string> sx = split(s, "; tunnels lead to valves ");
        char a, b;
        int flow;
        string v = sx[0];
        sscanf(v.c_str(), "Valve %c%c has flow rate=%d", &a, &b, &flow);
        vector<string> nb = split(sx[1], ", ");
        
        string x;
        x += a;
        x += b;
        ns.pb(x);
        if (flow > 0) {
            nz2[x] = sz(nz);
            nz.pb(x);
        }
        f[x] = flow;
        g[x] = set<string>(all(nb));
    }

    map<state, int> cur;
    cur[state("AA", set<string>(), 0)] = 0;
    rep(i,0,30) {
        cout << i << ' ';
        auto cur2 = cur;
        for (auto [s, v] : cur) {
            cur2[s] += s.flow;
        }
        for (auto [s, v] : cur) {
            v += s.flow;
            if (f[s.node] > 0 && s.on.find(s.node) == s.on.end()) {
                state t = s;
                t.on.insert(s.node);
                t.flow += f[s.node];
                cur2[t] = max(cur2[t], v);
            }
            for (string x : g[s.node]) {
                state t = s;
                t.node = x;
                cur2[t] = max(cur2[t], v);
            }
        }
        cur = cur2;
    }

    int ans = 0;
    for (auto [s, v] : cur) {
        ans = max(ans, v);
    }
    cout << ans;
}
