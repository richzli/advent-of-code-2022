#include "../template.hpp"

int priority(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

int main() {
    string s1, s2, s3;
    int ans = 0;
    while (getline(cin, s1), getline(cin, s2), getline(cin, s3)) {
        for (char c : s1) {
            if ((s2.find(c) != string::npos) && (s3.find(c) != string::npos)) {
                ans += priority(c);
                break;
            }
        }
    }
    cout << ans;
}
