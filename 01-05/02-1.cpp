#include "../template.hpp"

map<char, int> score = {
    {'X', 1},
    {'Y', 2},
    {'Z', 3}
};
map<char, char> win = {
    {'X', 'C'},
    {'Y', 'A'},
    {'Z', 'B'}
},
draw = {
    {'X', 'A'},
    {'Y', 'B'},
    {'Z', 'C'}
};

int main() {
    int pts = 0;
    
    while (cin.peek() != EOF) {
        char e, y;
        cin >> e >> y;

        pts += score[y];
        if (e == win[y]) {
            pts += 6;
        } else if (e == draw[y]) {
            pts += 3;
        } else {
            // nothing
        }
    }

    cout << pts;
}
