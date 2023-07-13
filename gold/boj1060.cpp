#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#define ll long long
using namespace std;

struct info {
    ll size;
    int le, ri;
};

struct cmp {
    bool operator()(const info& a, const info& b) {
        if (a.size > b.size) return true;
        else if (a.size == b.size) {
            if (a.le > b.le) return true;
        }
        return false;
    }
};

bool cmp2(const pair<ll, int>& a, const pair<ll, int>& b) {
    if (a.first < b.first) return true;
    else if (a.first == b.first) {
        return a.second < b.second;
    }
    return false;
}

vector<int> v;
vector<pair<ll, int>> ans;
priority_queue<info, vector<info>, cmp> pq;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, k, i, temp, le, ri; cin >> n;
    ll size;
    for (i = 0; i < n; i++) {
        cin >> temp;
        v.push_back(temp);
        pq.push({ 0,temp,temp });
    }
    sort(v.begin(), v.end());
    if (v[0] >= 2) {
        v.push_back(0);
        n++;
        sort(v.begin(), v.end());
    }
    for (i = 1; i < n; i++) {
        if (v[i - 1] + 1 == v[i]) continue;
        pq.push({ (ll)(v[i] - v[i - 1] - 2),v[i - 1] + 1,v[i] - 1 });
    }
    cin >> k;
    while (!pq.empty()) {
        size = pq.top().size;
        le = pq.top().le;
        ri = pq.top().ri;
        pq.pop();
        ans.push_back({ size,le });
        if (le + 1 == ri) ans.push_back({ size,ri });
        if (le + 2 <= ri) {
            ans.push_back({ size,ri });
            pq.push({ size + (ll)(ri - le) - 1,le + 1,ri - 1 });
        }
        if (ans.size() >= k) break;
    }
    sort(ans.begin(), ans.end(), cmp2);
    temp = ans.size();
    if (temp >= k) {
        for (i = 0; i < k; i++) cout << ans[i].second << ' ';
    }
    else {
        for (i = 0; i < temp; i++) cout << ans[i].second << ' ';
        k -= temp;
        temp = v[n - 1] + 1;
        for (i = 0; i < k; i++) cout << temp++ << ' ';
    }
}
