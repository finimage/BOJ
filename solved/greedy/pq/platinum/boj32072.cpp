#include<bits/stdc++.h>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n;
vector<int> arr;
vector<vector<int>> g;
priority_queue<pii> pq;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int i, a, b; cin >> n;
    arr.resize(n + 1);
    g.resize(n + 1);
    for (i = 2; i <= n; i++) {
        cin >> a;
        g[a].emplace_back(i);
    }
    for (i = 1; i <= n; i++) cin >> arr[i];
    pq.push({-arr[1],1});
    for (i = 1; i <= n; i++) {
        a = -pq.top().x;
        b = pq.top().y;
        pq.pop();
        cout << a << '\n';
        for (auto& iter : g[b]) pq.push({-arr[iter],iter});
    }
}
