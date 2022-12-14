#include "../template.hpp"

int sgn(int x) {
    return (x == 0) ? 0 : (x/abs(x));
}

int main() {
    vector<vector<int>> map(1000, vi(500));
    string s;
    int besty = 0;
    while (getline(cin, s)) {
        vector<string> coords = split(s, " -> ");
        int cx = -1, cy = -1;
        for (string coord : coords) {
            vector<string> xy = split(coord, ",");
            int nx = stoi(xy[0]), ny = stoi(xy[1]);
            besty = max(besty, ny);
            if (cx == -1 && cy == -1) {
                cx = nx; cy = ny;
                map[cx][cy] = 1;
            } else {
                int dx = sgn(nx-cx), dy = sgn(ny-cy);
                while (cx != nx || cy != ny) {
                    cx += dx;
                    cy += dy;
                    map[cx][cy] = 1;
                }
            }
        }
    }
    rep(i,0,1000) {
        map[i][besty+2] = 1;
    }

    int ans = 0;
    while (true) {
        int x = 500, y = 0;
        while (true) {
            if (map[x][y+1] != 0) {
                if (map[x-1][y+1] == 0) {
                    x--;
                    y++;
                } else if (map[x+1][y+1] == 0) {
                    x++;
                    y++;
                } else {
                    map[x][y] = 2;
                    break;
                }
            } else {
                ++y;
            }
        }
        ++ans;
        if (x == 500 && y == 0) {
            break;
        }
    }

    cout << ans;
}
