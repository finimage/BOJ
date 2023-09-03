#include<iostream>
#include<queue>
#define ll long long
using namespace std;

struct info {
	ll x;
	int ind;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.x > b.x;
	}
};

pair<ll, ll> arr[50001];
priority_queue<info, vector<info>, cmp> pq, c_pq;
priority_queue<ll> p_pq;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, k, i, ind, cnt = 0;
	ll m, p, c, used = 0; cin >> n >> k >> m;
	for (i = 1; i <= n; i++) {
		cin >> p >> c;
		arr[i] = { p,c };
		pq.push({ c,i });
	}
	while (!pq.empty()) {
		c = pq.top().x;
		ind = pq.top().ind;
		pq.pop();
		if (k) {
			if (used + c > m) break;
			used += c;
			cnt++;
			k--;
			c_pq.push({ arr[ind].first - c,i });
		}
		else {
			ll a = m - used - c_pq.top().x - c;
			ll b = m - used - arr[ind].first;
			if (a >= 0 && b >= 0) {
				cnt++;
				if (a > b) {
					used += c_pq.top().x + c;
					c_pq.pop();
					c_pq.push({ arr[ind].first - c,ind });
				}
				else {
					used += arr[ind].first;
					p_pq.push(arr[ind].first);
				}
			}
			else if (a >= 0) {
				cnt++;
				used += c_pq.top().x + c;
				c_pq.pop();
				c_pq.push({ arr[ind].first - c,ind });
			}
			else if (b >= 0) {
				cnt++;
				used += arr[ind].first;
				p_pq.push(arr[ind].first);
			}
			else {
				if (p_pq.empty()) continue;
				if (p_pq.top() > arr[ind].first) {
					used -= p_pq.top();
					used += arr[ind].first;
					p_pq.pop();
					p_pq.push(arr[ind].first);
				}
			}
		}
	}
	cout << cnt;
}
