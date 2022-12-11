#include "../template.hpp"

int main() {
    string s;
    int cycle = 0;
    string ans;
    int x = 1;
    while (cin >> s) {
        if (s == "noop") {
            if (abs(x - (cycle % 40)) <= 1) {
                ans += '#';
            } else {
                ans += '.';
            }
            ++cycle;
        } else {
            cin >> s;
            if (abs(x - (cycle % 40)) <= 1) {
                ans += '#';
            } else {
                ans += '.';
            }
            ++cycle;
            if (abs(x - (cycle % 40)) <= 1) {
                ans += '#';
            } else {
                ans += '.';
            }
            ++cycle;
            x += stoi(s);
        }
    }
    for (int i = 0; i < sz(ans); i += 40) {
        cout << ans.substr(i, 40) << endl;
    }
}
