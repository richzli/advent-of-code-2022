#include "../template.hpp"

vector<int> parse(string s) {
    int x, y, xx, yy;
    sscanf(s.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n", &x, &y, &xx, &yy);
    return {x, y, (abs(x-xx) + abs(y-yy))};
}

int main() {
    string s;
    int b = 2000000;
    vector<pii> cnt;
    while (getline(cin, s)) {
        if (s.empty()) break;

        vi d = parse(s);
        int x = 0;
        if (abs(d[1]-b) > d[2]) {
            continue;
        } else {
            cnt.pb({d[0]-(d[2]-abs(d[1]-b)), 1});
            cnt.pb({d[0]+(d[2]-abs(d[1]-b))+1, -1});
        }
    }
    sort(all(cnt));
    int ans = 0;
    int cur = -1, v = 0;
    for (auto [x, d] : cnt) {
        if (v == 0) {
            cur = x;
        }
        v += d;
        if (v == 0) {
            ans += x - cur - 1;
            cur = -1;
        }
    }
    cout << ans;
}
