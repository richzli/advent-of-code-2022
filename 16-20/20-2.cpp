#include "../template.hpp"

struct node {
    ll value;
    node* left;
    node* right;
    node(ll _value) {
        value = _value;
        left = NULL;
        right = NULL;
    }
};

int main() {
    int n = 0;
    vector<node*> order;
    node* head = NULL;
    string s;
    while (getline(cin, s)) {
        if (s.empty()) continue;
        node* x = new node(((ll) stoi(s)) * 811589153);
        if (head == NULL) {
            head = x;
            x->left = x;
            x->right = x;
        } else {
            x->left = head;
            x->right = head->right;
            head->right->left = x;
            head->right = x;
        }
        order.pb(x);
        ++n;
    }


    rep(k,0,10) {
        rep(i,0,n) {
            ll v = ((order[i]->value % (n-1)) + (n-1)) % (n-1);

            rep(j,0,v) {
                node* le = order[i]->left;
                node* lele = order[i]->left->left;
                node* ri = order[i]->right;
                lele->right = order[i];
                le->right = ri;
                le->left = order[i];
                order[i]->left = lele;
                ri->left = le;
                order[i]->right = le;
            }
        }
    }

    ll ans = 0;
    while (head->value != 0) {
        head = head->left;
    }
    rep(i,0,3001) {
        if (i == 1000 || i == 2000 || i == 3000) {
            ans += head->value;
        }
        head = head->left;
    }

    cout << ans;
}
