#include "../template.hpp"

map<char, int> score = {
    {'X', 1},
    {'Y', 2},
    {'Z', 3}
};
map<char, char> win = {
    {'C', 'X'},
    {'A', 'Y'},
    {'B', 'Z'}
},
draw = {
    {'A', 'X'},
    {'B', 'Y'},
    {'C', 'Z'}
},
lose = {
    {'A', 'Z'},
    {'B', 'X'},
    {'C', 'Y'}
};

int main() {
    int pts = 0;
    
    while (cin.peek() != EOF) {
        char e, y;
        cin >> e >> y;

        if (y == 'Z') {
            pts += 6;
            pts += score[win[e]];
        } else if (y == 'Y') {
            pts += 3;
            pts += score[draw[e]];
        } else {
            pts += score[lose[e]];
        }
    }

    cout << pts;
}
