#include "../template.hpp"

int main() {
    string s;
    cin >> s;
    string nx = s.substr(0, 13);
    for (int i = 13; i < sz(s); ++i) {
        nx += s[i];

        bool ok = true;
        for (char c : nx) {
            if (nx.find(c, nx.find(c)+1) != string::npos) {
                ok = false;
            }
        }
        if (ok) {
            cout << i+1;
            break;
        }

        nx = nx.substr(1);
    }
}
