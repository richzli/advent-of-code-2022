#include "../template.hpp"

int main() {
    string s;
    int ans = 0, cur = 0;
    while (getline(cin, s)) {
        if (s == "") {
            cur = 0;
        } else {
            cur += stoi(s);
        }

        ans = max(ans, cur);
    }

    cout << ans;
}
