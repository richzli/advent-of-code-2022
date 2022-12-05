#include "../template.hpp"

int main() {
    string s;
    int ans;
    while (getline(cin, s)) {
        string l, r;
        int pos = s.find(',');
        l = s.substr(0, pos);
        r = s.substr(pos+1);
        
        int l1, l2;
        l1 = stoi(l.substr(0, l.find('-')));
        l2 = stoi(l.substr(l.find('-')+1));
        int r1, r2;
        r1 = stoi(r.substr(0, r.find('-')));
        r2 = stoi(r.substr(r.find('-')+1));

        if (!((l1 > r2) || (r1 > l2))) {
            ++ans;
        }
    }

    cout << ans;
}
