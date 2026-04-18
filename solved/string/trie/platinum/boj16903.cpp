#include<bits/stdc++.h>
#define INF 10000001
using namespace std;

struct info {
    int check;
    int child[2];
};

int nodesz = 1;
vector<info> node(200000);

int plus_node() {
    if (nodesz + 1 == node.size()) node.resize(nodesz * 2);
    return ++nodesz;
}

void plus_val(int val) {
    int i;
    vector<int> v;
    for (i = 0; i < 32; i++) {
        if (val & 1) v.push_back(1);
        else v.push_back(0);
        val >>= 1;
    }
    reverse(v.begin(), v.end());
    int st = 1;
    for (i = 0; i < 32; i++) {
        if (!node[st].child[v[i]]) {
            node[st].child[v[i]] = plus_node();
            st = node[st].child[v[i]];
        }
        else st = node[st].child[v[i]];
        node[st].check++;
    }
}

void remove_val(int val) {
    int i;
    vector<int> v;
    for (i = 0; i < 32; i++) {
        if (val & 1) v.push_back(1);
        else v.push_back(0);
        val >>= 1;
    }
    reverse(v.begin(), v.end());
    int st = 1;
    for (i = 0; i < 32; i++) {
        st = node[st].child[v[i]];
        node[st].check--;
    }
}

int res(int val) {
    int i;
    vector<int> v;
    for (i = 0; i < 32; i++) {
        if (val & 1) v.push_back(1);
        else v.push_back(0);
        val >>= 1;
    }
    reverse(v.begin(), v.end());
    int st = 1, ret = 0;
    for (i = 0; i < 32; i++) {
        if (v[i] == 0) {
            if (node[st].child[1] && node[node[st].child[1]].check) {
                st = node[st].child[1];
                ret <<= 1;
                ret |= 1;
            }
            else {
                st = node[st].child[0];
                ret <<= 1;
            }
        }
        else {
            if (node[st].child[0] && node[node[st].child[0]].check) {
                st = node[st].child[0];
                ret <<= 1;
            }
            else {
                st = node[st].child[1];
                ret <<= 1;
                ret |= 1;
            }
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    node[1].check = 20000000;
    plus_val(0);
    int i, q, a, b; cin >> q;
    while (q--) {
        cin >> a >> b;
        if (a == 1) plus_val(b);
        else if (a == 2) remove_val(b);
        else cout << (b ^ res(b)) << '\n';
    }
}
