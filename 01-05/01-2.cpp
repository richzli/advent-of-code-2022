#include "../template.hpp"

int main() {
    string s;
    vi ans;
    int cur = 0;
    while (getline(cin, s)) {
        if (s == "") {
            ans.pb(cur);
            cur = 0;
        } else {
            cur += stoi(s);
        }
    }
    sort(all(ans));
    reverse(all(ans));

    cout << (ans[0] + ans[1] + ans[2]);
}
