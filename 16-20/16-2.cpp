#include "../template.hpp"

struct state {
    int node;
    int elephant;
    int on;
    state(int _node, int _elephant) {
        node = _node;
        elephant = _elephant;
        on = 0;
    }
    int value() {
        return node + 100 * elephant + 100'00 * on;
    }
    bool operator<(const state& s2) const {
        if (node != s2.node) return node < s2.node;
        if (elephant != s2.elephant) return elephant < s2.elephant;
        if (on != s2.on) return on < s2.on;
        return false;
    }
};

int main() {
    map<string, int> f;
    map<string, vector<string>> g;
    vector<string> ns, nz;
    map<string, int> ns2, nz2;
    int tot = 0;

    vector<int> szt;

    string ss;
    while (getline(cin, ss)) {
        if (ss.empty()) break;
        vector<string> sx = split(ss, "; tunnels lead to valves ");
        char a, b;
        int flow;
        string v = sx[0];
        sscanf(v.c_str(), "Valve %c%c has flow rate=%d", &a, &b, &flow);
        vector<string> nb = split(sx[1], ", ");
        
        string x;
        x += a;
        x += b;
        ns2[x] = sz(ns);
        ns.pb(x);
        if (flow > 0) {
            nz2[x] = sz(nz);
            szt.pb(sz(nz));
            nz.pb(x);
        } else {
            szt.pb(0);
        }
        f[x] = flow;
        g[x] = nb;
        tot += flow;
    }

    vi ff(sz(ns));
    vvi gg(sz(ns));
    rep(i,0,sz(ns)) {
        ff[i] = f[ns[i]];
        for (string x : g[ns[i]])
            gg[i].pb(ns2[x]);
    }

    function<int(int)> fl = [&](int bm) {
        int ans = 0;
        rep(i,0,sz(nz)) {
            if ((bm & (1 << i)) != 0) {
                ans += f[nz[i]];
            }
        }
        return ans;
    };
    function<int(int, int, int)> st = [&](int nd, int el, int on) {
        return nd + el * 64 + on * 4096;
    };
    
    int ans = 0;
    int NN = 64 * 64 * (1 << 15);
    vi cur(NN, 0), cur2(NN, 0);
    cur[st(ns2["AA"], ns2["AA"], 0)] = 1;
    rep(i,0,26) {
        //cout << i << " | ";
        rep(s,0,NN) {
            if (cur[s] == 0) continue;
            int v = cur[s];
            int nd = s % 64, el = (s / 64) % 64, on = (s / 4096);
            v += fl(on);
            if (on == (1 << sz(nz)) - 1) {
                ans = max(ans, v + fl(on) * (25-i));
                continue;
            }
            if (ff[nd] > 0 && ((on & (1 << szt[nd])) == 0)) {
                int t = st(nd, el, on | (1 << szt[nd]));
                cur2[t] = max(cur2[t], v);
            }
            for (int x : gg[nd]) {
                int t = st(x, el, on);
                cur2[t] = max(cur2[t], v);
            }
        }
        swap(cur, cur2);
        fill(all(cur2), 0);
        rep(s,0,NN) {
            if (cur[s] == 0) continue;
            int v = cur[s];
            int nd = s % 64, el = (s / 64) % 64, on = (s / 4096);
            if (on == (1 << sz(nz)) - 1) {
                ans = max(ans, v + fl(on) * (25-i));
                continue;
            }
            if (ff[el] > 0 && ((on & (1 << szt[el])) == 0)) {
                int u = st(nd, el, on | (1 << szt[el]));
                cur2[u] = max(cur2[u], v);
            }
            for (int y : gg[el]) {
                int u = st(nd, y, on);
                cur2[u] = max(cur2[u], v);
            }
        }
        swap(cur, cur2);
        fill(all(cur2), 0);
    }

    rep(s,0,NN) {
        ans = max(ans, cur[s]);
    }
    cout << (ans-1);
}
