#include<iostream>
#include<queue>
using namespace std;

struct info {
	int a, b, dis;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.dis > b.dis;
	}
};

int n, p, arr[10001], parent[10001];
priority_queue<info, vector<info>, cmp> pq;

int find_(int a) {
	if (a == parent[a]) return a;
	return parent[a] = find_(parent[a]);
}

bool union_(int a, int b) {
	a = find_(a);
	b = find_(b);
	if (a == b) return 1;
	parent[a] = b;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, dis, cost = 0, Min = 1001; cin >> n >> p;
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
		Min = min(Min, arr[i]);
		parent[i] = i;
	}
	while (p--) {
		cin >> a >> b >> dis;
		pq.push({ a,b,dis * 2 + arr[a] + arr[b] });
	}
	while (!pq.empty()) {
		a = pq.top().a;
		b = pq.top().b;
		dis = pq.top().dis;
		pq.pop();
		if (union_(a, b)) continue;
		cost += dis;
	}
	cout << cost + Min;
}
