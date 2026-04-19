#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n, arr[3001], indegree[3001], GCD[3001][3001];
vector<int> g[3001];

struct cmp {
	bool operator()(const int a, const int b) {
		return arr[a] > arr[b];
	}
};

priority_queue<int, vector<int>, cmp> pq;

int gcd(int a, int b) {
	while (b) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

void input() {
	int i, j; cin >> n;
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
		for (j = i - 1; j > 0; j--) GCD[i][j] = GCD[j][i] = gcd(arr[i], arr[j]);
	}
}

void make_g() {
	int i, j, tf;
	for (i = 1; i <= n; i++) {
		tf = 1;
		for (j = i - 1; j > 0; j--) {
			if (GCD[i][j] != 1) {
				tf = 0;
				g[j].push_back(i);
				indegree[i]++;
			}
		}
		if (tf) {
			pq.push(i);
			indegree[i]++;
		}
		for (j = i + 1; j <= n; j++) {
			if (GCD[i][j] != 1) {
				g[i].push_back(j);
				indegree[j]++;
			}
		}
	}
}

void solve() {
	int a;
	while (!pq.empty()) {
		a = pq.top();
		pq.pop();
		cout << arr[a] << ' ';
		for (auto& iter : g[a]) {
			indegree[iter]--;
			if (indegree[iter] == 0) pq.push(iter);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	make_g();
	solve();
}
