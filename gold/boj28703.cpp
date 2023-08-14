#include<iostream>
#include<queue>
#define ll long long
using namespace std;

priority_queue<ll, vector<ll>, greater<ll>> pq;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	ll MAX = 0, temp, dif = 1000000001;
	while (n--) {
		cin >> temp;
		MAX = max(MAX, temp);
		pq.push(temp);
	}
	if (n == 1) {
		cout << 0;
		return 0;
	}
	ll origin = MAX;
	while (pq.top() != origin) {
		dif = min(dif, MAX - pq.top());
		ll k = pq.top();
		pq.pop();
		k *= 2;
		MAX = max(MAX, k);
		pq.push(k);
	}
	dif = min(dif, MAX - pq.top());
	cout << dif;
}
