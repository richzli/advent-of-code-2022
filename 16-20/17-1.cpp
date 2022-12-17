#include "../template.hpp"

vector<vector<string>> rocks = {
    {
        "####"
    },{
        ".#.",
        "###",
        ".#."
    },{
        "###",
        "..#",
        "..#"
    },{
        "#",
        "#",
        "#",
        "#"
    },{
        "##",
        "##"
    }
};

int main() {
    string s;
    cin >> s;

    int h = 0;

    vector<string> grid;
    function<bool(int, int, int)> check = [&](int piece, int x, int y){
        if (y < 0 || y + sz(rocks[piece][0]) > 7) return false;
        if (x - sz(rocks[piece]) + 1 < 0) return false;
        rep(i,0,sz(rocks[piece])) {
            rep(j,0,sz(rocks[piece][i])) {
                if (rocks[piece][sz(rocks[piece])-i-1][j] != '.' && grid[x-i][y+j] != '.') {
                    return false;
                }
            }
        }
        return true;
    };
    function<void(int, int, int)> place = [&](int piece, int x, int y) {
        rep(i,0,sz(rocks[piece])) {
            rep(j,0,sz(rocks[piece][i])) {
                if (grid[x-i][y+j] == '.') {
                    grid[x-i][y+j] = rocks[piece][sz(rocks[piece])-i-1][j];
                }
            }
        }
    };
    int wind = 0;
    rep(i,0,2022) {
        int piece = i % 5;
        while (sz(grid) < sz(rocks[piece]) + h + 3) {
            grid.pb(".......");
        }

        int posx = sz(rocks[piece]) + h + 3 - 1, posy = 2;

        while (true) {
            if (s[wind] == '<' && check(piece, posx, posy-1)) {
                posy--;
            } else if (s[wind] == '>' && check(piece, posx, posy+1)) {
                posy++;
            }

            ++wind;
            wind %= sz(s);

            if (check(piece, posx-1, posy)) {
                posx--;
            } else {
                place(piece, posx, posy);
                h = max(h, posx+1);
                break;
            }
        }
    }

    cout << h;
}
