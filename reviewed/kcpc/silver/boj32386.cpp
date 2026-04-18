#include<bits/stdc++.h>
using namespace std;

int n;
string s;
unordered_map<string, int> mmap;
vector<string> v;

bool cmp(string a, string b) {
    return mmap[a] > mmap[b];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int a, t, i, j; cin >> n;
    for (i = 0; i < n; i++) {
        cin >> a >> t;
        for (j = 0; j < t; j++) {
            cin >> s;
            if (mmap.count(s)) mmap[s]++;
            else {
                mmap[s] = 1;
                v.push_back(s);
            }
        }
    }
    if (v.size() == 1) {
        cout << v[0];
        return 0;
    }
    sort(v.begin(), v.end(), cmp);
    if (mmap[v[0]] == mmap[v[1]]) cout << -1;
    else cout << v[0];
}
