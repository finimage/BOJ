#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> C, nimber, vnum;
vector<set<int>> v;
vector<vector<int>> g;

void dfs(int ind, int pre) {
    int val = C[ind];
    int Max = 0, Cnt = 0, ck = 0, nim = 0;
    set<int> s;
    vector<int> check(g[ind].size() + 1, 0);
    for (auto& iter : g[ind]) {
        ck++;
        if (iter == pre) continue;
        dfs(iter, ind);
        nim ^= nimber[iter];
        if (v[vnum[iter]].count(val ^ C[iter])) check[ck] = 1;
        if (v[vnum[iter]].size() > Cnt) {
            Max = iter;
            Cnt = v[vnum[iter]].size();
        }
    }
    ck = 0;
    for (auto& iter : g[ind]) {
        ck++;
        if (iter == pre) continue;
        if (check[ck]) s.insert((nim ^ nimber[iter]));
        if (iter == Max) continue;
        for (auto& itr : v[vnum[iter]]) v[vnum[Max]].insert(C[Max] ^ itr ^ C[iter]);
        v[vnum[iter]].clear();
    }
    if (C[ind] == 0) s.insert(nim);
    if (Max != 0) vnum[ind] = vnum[Max];
    C[ind] ^= C[Max];
    v[vnum[ind]].insert(C[Max]);
    if (s.empty()) nimber[ind] = 0;
    else {
        int tf = 1;
        ck = 0;
        for (auto& iter : s) {
            if (iter != ck) {
                nimber[ind] = ck;
                tf = 0;
                break;
            }
            ck++;
        }
        if (tf) nimber[ind] = ck;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b; cin >> n;
    C.resize(n + 1);
    g.resize(n + 1);
    v.resize(n + 1);
    vnum.resize(n + 1);
    nimber.resize(n + 1);
    for (i = 1; i <= n; i++) {
        vnum[i] = i;
        cin >> C[i];
    }
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(1, 0);
    cout << (nimber[1] > 0 ? "kidw0124" : "eoaud0108"); 
}
