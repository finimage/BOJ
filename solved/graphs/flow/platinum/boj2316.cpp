#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n, p, cap[801][801], flow[801][801], cnt;
vector<int> g[801];
queue<int> q;

int max_flow() {
    q = queue<int>();
    vector<int> pre(2 * n + 1);
    q.push(2);
    int a, tf = 1;
    pre[2] = -1;
    while (!q.empty()) {
        a = q.front();
        q.pop();
        if (a == 3) {
            tf = 0;
            break;
        }
        for (auto& iter : g[a]) {
            if (!pre[iter] && cap[a][iter] > flow[a][iter]) {
                pre[iter] = a;
                q.push(iter);
            }
        }
    }
    if (tf) return 0;
    a = 3;
    while (pre[a] != -1) {
        flow[pre[a]][a]++;
        flow[a][pre[a]]--;
        a = pre[a];
    }
    cnt++;
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b; cin >> n >> p;
    for (i = 1; i <= n; i++) {
        g[i * 2 - 1].push_back(i * 2);
        g[i * 2].push_back(i * 2 - 1);
        cap[i * 2 - 1][i * 2] = 1;
    }
    for (i = 0; i < p; i++) {
        cin >> a >> b;
        g[a * 2].push_back(b * 2 - 1);
        g[b * 2 - 1].push_back(a * 2);
        g[b * 2].push_back(a * 2 - 1);
        g[a * 2 - 1].push_back(b * 2);
        cap[a * 2][b * 2 - 1] = 1;
        cap[b * 2][a * 2 - 1] = 1;
    }
    while (1) {
        if (!max_flow()) break;
    }
    cout << cnt;
}
