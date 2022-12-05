#include "../template.hpp"

int priority(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

int main() {
    string s;
    int ans = 0;
    while (getline(cin, s)) {
        string first, second;
        first = s.substr(0, sz(s)/2);
        second = s.substr(sz(s)/2, sz(s)/2);
        for (char c : first) {
            if (second.find(c) != string::npos) {
                ans += priority(c);
                break;
            }
        }
    }
    cout << ans;
}
