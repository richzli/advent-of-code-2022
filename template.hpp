#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef map<int, int> mii;
typedef map<ll, ll> mll;

#define bound(x, y) ((0 <= (x)) && (0 <= (y)) && ((x) < n) && ((y) < m))

int dx4[4] = {1, 0, -1, 0}, dy4[4] = {0, 1, 0, -1};
int dx8[8] = {1, 1, 1, 0, -1, -1, -1, 0}, dy8[8] = {1, 0, -1, -1, -1, 0, 1, 1};

vector<string> split(string s, string delim) {
    size_t pos = 0;
    vector<string> ret;
    while ((pos = s.find(delim)) != string::npos) {
        ret.pb(s.substr(0, pos));
        s.erase(0, pos + delim.length());
    }
    return ret;
}