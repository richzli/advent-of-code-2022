#include "../template.hpp"

vector<int> parse(string s) {
    int x, y, xx, yy;
    sscanf(s.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n", &x, &y, &xx, &yy);
    return {x-y, x+y, (max(abs((x-y)-(xx-yy)), abs((x+y)-(xx+yy))))};
}

int main() {
    string s;
    vector<vi> cnt;
    set<int> coords;
    while (getline(cin, s)) {
        if (s.empty()) break;

        vi d = parse(s);
        cnt.pb(d);
        coords.insert(d[0]-d[2]);
        coords.insert(d[0]+d[2]);
        coords.insert(d[0]+d[2]+1);
        coords.insert(d[1]-d[2]);
        coords.insert(d[1]+d[2]);
        coords.insert(d[1]+d[2]+1);
    }

    vi cc(all(coords));
    sort(all(cc));
    map<int, int> ccmp;
    rep(i,0,sz(cc)) {
        ccmp[cc[i]] = i;
    }

    int n = 4000001, m = 4000001;
    vvi x(sz(cc), vi(sz(cc), 0));
    for (vi d : cnt) {
        x[ccmp[d[0]-d[2]]][ccmp[d[1]-d[2]]] = 1;
        x[ccmp[d[0]-d[2]]][ccmp[d[1]+d[2]+1]] = -1;
        x[ccmp[d[0]+d[2]+1]][ccmp[d[1]-d[2]]] = -1;
        x[ccmp[d[0]+d[2]+1]][ccmp[d[1]+d[2]+1]] = 1;
    }
    vvi y(sz(cc), vi(sz(cc), 0));
    rep(i,0,sz(cc)) {
        if (i > 0) y[i] = y[i-1];
        int d = 0;
        rep(j,0,sz(cc)) {
            d += x[i][j];
            y[i][j] += d;
            
            int xx = (cc[i] + cc[j])/2, yy = (cc[j] - cc[i]) / 2;
            if (y[i][j] == 0 && bound(xx, yy)) {
                cout << ((ll)xx) * 4000000 + yy;
                return 0;
            }
        }
    }
}
