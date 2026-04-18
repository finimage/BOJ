#include<bits/stdc++.h>
using namespace std;

struct info {
    int i, l, r;
};

vector<info> v;
int n, arr[5001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, tmp; cin >> n;
    for (i = 1; i <= n; i++) cin >> arr[i];
    for (i = 1; i <= n; i++) {
        if (arr[i] == i) continue;
        tmp = arr[i];
        v.push_back({i,i,i});
        while (tmp != i) {
            v.push_back({tmp,1,n});
            swap(tmp, arr[tmp]);
        }
        v.push_back({i,1,n});
        arr[i] = i;
    }
    cout << v.size() << '\n';
    for (auto& iter : v) cout << iter.i << ' ' << iter.l << ' ' << iter.r << '\n';
}
