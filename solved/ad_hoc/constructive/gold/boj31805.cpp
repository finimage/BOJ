#include<bits/stdc++.h>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n;
string s, s_;
vector<int> alp[26];
vector<pii> ans;
priority_queue<pii> pq;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, Max = 0; cin >> n >> s;
    s_ = s;
    for (i = 0; i < n; i++) alp[s[i] - 'a'].emplace_back(i + 1);
    for (i = 0; i < 26; i++) {
        Max = max(Max, (int)alp[i].size());
        if (alp[i].size() > 0) pq.push({alp[i].size(),i});
    }
    if (Max > n - Max) {
        cout << -1;
        return 0;
    }
    while (pq.size() > 1) {
        pii fi = pq.top();
        pq.pop();
        pii se = pq.top();
        pq.pop();
        if (alp[fi.y][fi.x - 1] < alp[se.y][se.x - 1]) ans.push_back({alp[fi.y][fi.x - 1],alp[se.y][se.x - 1]});
        else ans.push_back({alp[se.y][se.x - 1],alp[fi.y][fi.x - 1]});
        swap(s[alp[fi.y][--fi.x] - 1], s[alp[se.y][--se.x] - 1]);
        if (fi.x > 0) pq.push(fi);
        if (se.x > 0) pq.push(se);
    }
    if (!pq.empty()) {
        pii k = pq.top();
        for (i = 0; i < n; i++) {
            if (s[i] != (char)('a' + k.y) && s_[i] != (char)('a' + k.y)) {
                if (alp[k.y][0] < i + 1) ans.push_back({alp[k.y][0],i+1});
                else ans.push_back({i+1,alp[k.y][0]});
                break;
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto& iter : ans) cout << iter.x << ' ' << iter.y << '\n';
}
