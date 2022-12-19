#include "../template.hpp"

struct state {
    vector<int> resources;
    vector<int> robots;
    state() {
        resources = {0, 0, 0, 0};
        robots = {1, 0, 0};
    }
    bool operator<(const state& s) const {
        if (resources != s.resources) return resources < s.resources;
        return robots < s.robots;
    }
    bool operator==(const state& s) const {
        return resources == s.resources && robots == s.robots;
    }
};

int main() {
    string s;
    int sm = 0;
    while (getline(cin, s)) {
        if (s.empty()) continue;

        int d, o_o, c_o, b_o, b_c, g_o, g_b;
        sscanf(s.c_str(), "Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.", &d, &o_o, &c_o, &b_o, &b_c, &g_o, &g_b);

        int mo = max({o_o, c_o, b_o, g_o});

        set<state> a, b;
        state st = state();
        a.insert(st);
        int lmg = 0;
        int mt = 24;
        rep(t,0,mt-1) {
            int mg = 0;
            for (state x : a) {
                if (lmg > x.resources[3] + (mt-t)*(mt-1-t)/2) continue;
                rep(i,0,3) {
                    x.resources[i] += x.robots[i];
                }
                b.insert(x);
                mg = max(mg, x.resources[3]);
                if (x.resources[0] - x.robots[0] >= o_o &&
                    x.robots[0] < mo &&
                    t < mt - 3 - o_o &&
                    x.resources[0] < mo * (mt-1-t)) {
                    state y = x;
                    y.resources[0] -= o_o;
                    y.robots[0] += 1;
                    b.insert(y);
                }
                if (x.resources[0] - x.robots[0] >= c_o &&
                    x.robots[1] < b_c &&
                    t < mt - 5 &&
                    x.resources[1] < b_c * (mt-1-t)) {
                    if (x.robots[0] == mo &&
                        x.resources[0] - x.robots[0] >= mo) {
                        b.erase(x);
                    }
                    state y = x;
                    y.resources[0] -= c_o;
                    y.robots[1] += 1;
                    b.insert(y);
                }
                if (x.resources[0] - x.robots[0] >= b_o && 
                    x.resources[1] - x.robots[1] >= b_c &&
                    x.robots[2] < g_b &&
                    t < mt - 3 &&
                    x.resources[2] < g_b * (mt-1-t)) {
                    state y = x;
                    y.resources[0] -= b_o;
                    y.resources[1] -= b_c;
                    y.robots[2] += 1;
                    b.insert(y);
                }
                if (x.resources[0] - x.robots[0] >= g_o &&
                    x.resources[2] - x.robots[2] >= g_b &&
                    t < mt - 1) {
                    state y = x;
                    y.resources[0] -= g_o;
                    y.resources[2] -= g_b;
                    y.resources[3] += mt - 1 - t;
                    b.insert(y);
                    mg = max(mg, y.resources[3]);
                }
            }
            swap(a, b);
            b.clear();
            lmg = mg;
        }

        int ans = 0;
        for (state x : a) {
            ans = max(ans, x.resources[3]);
        }
        sm += ans * d;
    }

    cout << sm;
}
