#include "../template.hpp"

int main() {
    string s;
    int cycle = 0;
    int ans = 0;
    int x = 1;
    set<int> check = {20, 60, 100, 140, 180, 220};
    while (cin >> s) {
        if (s == "noop") {
            ++cycle;
            if (check.find(cycle) != check.end()) {
                ans += cycle * x;
                cout << cycle * x << endl;
            }
        } else {
            cin >> s;
            ++cycle;
            if (check.find(cycle) != check.end()) {
                ans += cycle * x;
                cout << cycle * x << endl;
            }
            ++cycle;
            if (check.find(cycle) != check.end()) {
                ans += cycle * x;
                cout << cycle * x << endl;
            }
            x += stoi(s);
        }
    }
    cout << ans;
}
