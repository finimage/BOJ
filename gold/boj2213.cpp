#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> tree[10001], ans;
int N, dp[2][10001], value[10001];
bool visited[10001];

void dfs(int index) {
    visited[index] = 1;
    dp[0][index] = value[index];
    for (auto iter = tree[index].begin(); iter != tree[index].end(); iter++) {
        if (visited[*iter]) continue;
        dfs(*iter);
        dp[1][index] += max(dp[0][*iter], dp[1][*iter]);
        dp[0][index] += dp[1][*iter];
    }
}

void solve(int index, bool check) {
    bool mark = 0;
    visited[index] = 0;
    if (!check && dp[0][index] > dp[1][index]) {
        ans.push_back(index);
        mark = 1;
    }
    for (auto iter = tree[index].begin(); iter != tree[index].end(); iter++) {
        if (!visited[*iter]) continue;
        solve(*iter, mark);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b; cin >> N;
    for (i = 1; i <= N; i++) cin >> value[i];
    for (i = 1; i < N; i++) {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    dfs(1);
    cout << max(dp[0][1], dp[1][1]) << '\n';
    solve(1, 0);
    sort(ans.begin(), ans.end());
    for (auto iter = ans.begin(); iter != ans.end(); iter++) cout << *iter << ' ';
}
