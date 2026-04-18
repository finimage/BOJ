#include<iostream>
using namespace std;

int N, M, parent[100001];
long long dif[100001];

int find_(int a) {
	if (a == parent[a]) return a;
	int A = find_(parent[a]);
	dif[a] += dif[parent[a]];
	return parent[a] = A;
}

void union_(int a, int b, int c) {
	int A = find_(a), B = find_(b);
	if (A != B) {
		parent[A] = B;
		dif[A] = dif[b] - dif[a] - c;
	}
}

void init() {
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		dif[i] = 0;
	}
}

void solve() {
	int a, b, c;
	char order;
	while (M--) {
		cin >> order;
		if (order == '!') {
			cin >> a >> b >> c;
			union_(a, b, c);
		}
		else {
			cin >> a >> b;
			if (find_(a) == find_(b)) cout << dif[b] - dif[a] << '\n';
			else cout << "UNKNOWN\n";
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	while (1) {
		cin >> N >> M;
		if (N == 0 && M == 0) break;
		init();
		solve();
	}
}
