#include<iostream>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;

struct cir {
	int x, y, r;
};

struct info {
	int a, b;
	double val;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.val > b.val;
	}
};

const double pi = 3.14159265358979;
int parent[1001];
priority_queue<info, vector<info>, cmp> pq;
vector<cir> v;

int dis(const cir& a, const cir& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double checking(const cir& a, const cir& b) {
	if ((a.r + b.r) * (a.r + b.r) >= dis(a, b)) return 0;
	if (a.r == b.r) return sqrt(dis(a, b)) * 2 + pi * 2 * a.r;
	else if (a.r > b.r) {
		int t = (a.r - b.r) * (a.r - b.r);
		double k = sqrt(dis(a, b) - t);
		double theta = atan(k / sqrt(t));
		return 2 * k + (pi - theta) * 2 * a.r + theta * 2 * b.r;
	}
	else {
		int t = (b.r - a.r) * (b.r - a.r);
		double k = sqrt(dis(a, b) - t);
		double theta = atan(k / sqrt(t));
		return 2 * k + (pi - theta) * 2 * b.r + theta * 2 * a.r;
	}
}

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
	int n, i, j, a, b; cin >> n;
	double val, ans = 0;
	v = vector<cir>(n + 1);
	for (i = 1; i <= n; i++) {
		parent[i] = i;
		cin >> v[i].x >> v[i].y >> v[i].r;
	}
	for (i = 1; i < n; i++) {
		for (j = i + 1; j <= n; j++) pq.push({ i,j,checking(v[i],v[j]) });
	}
	while (!pq.empty()) {
		a = pq.top().a;
		b = pq.top().b;
		val = pq.top().val;
		pq.pop();
		if (union_(a, b)) continue;
		ans += val;
	}
	printf("%0.15f", ans);
}
