#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct co {
	int x, y;
};

struct line {
	int ind;
	co p1, p2;
};

int ccw(const co& a, const co& b, const co& c) {
	int k = a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
	if (k > 0) return 1;
	else if (k < 0) return -1;
	return 0;
}

bool checking(int a, int b, int c, int d) {
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return b < c || d < a;
}

bool check_(co a, co b, co c, co d) {
	int A = ccw(a, b, c), B = ccw(a, b, d);
	int C = ccw(c, d, a), D = ccw(c, d, b);
	if (A * B == 0 && C * D == 0) {
		return !checking(a.x, b.x, c.x, d.x) && !checking(a.y, b.y, c.y, d.y);
	}
	return A * B <= 0 && C * D <= 0;
}

stack<int> st;
int n, num[6001], low[6001], cnt, cnt_, check[6001];
bool visited[6001];
vector<line> arr;
vector<vector<int>> graph;

void scc(int ind) {
	cnt++;
	num[ind] = low[ind] = cnt;
	visited[ind] = 1;
	st.push(ind);
	for (auto& iter : graph[ind]) {
		if (!num[iter]) {
			scc(iter);
			low[ind] = min(low[ind], low[iter]);
		}
		else if(visited[iter]) low[ind] = min(low[ind], low[iter]);
	}
	if (num[ind] == low[ind]) {
		cnt_++;
		while (!st.empty()) {
			int k = st.top();
			st.pop();
			visited[k] = 0;
			check[k] = cnt_;
			if (ind == k) break;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j; cin >> n;
	arr = vector<line>(3 * n + 1);
	for (i = 1; i <= 3 * n; i++) {
		arr[i].ind = i;
		cin >> arr[i].p1.x >> arr[i].p1.y >> arr[i].p2.x >> arr[i].p2.y;
	}
	graph = vector<vector<int>>(6 * n + 1);
	for (i = 1; i < 3 * n; i++) {
		for (j = i + 1; j <= 3 * n; j++) {
			if (check_(arr[i].p1, arr[i].p2, arr[j].p1, arr[j].p2)) {
				graph[i * 2 - 1].push_back(j * 2);
				graph[j * 2 - 1].push_back(i * 2);
			}
		}
	}
	for (i = 1; i <= n; i++) {
		graph[(3 * i - 2) * 2].push_back((3 * i - 1) * 2 - 1);
		graph[(3 * i - 2) * 2].push_back(6 * i - 1);
		graph[(3 * i - 1) * 2].push_back((3 * i - 2) * 2 - 1);
		graph[(3 * i - 1) * 2].push_back(6 * i - 1);
		graph[6 * i].push_back((3 * i - 2) * 2 - 1);
		graph[6 * i].push_back((3 * i - 1) * 2 - 1);
	}
	for (i = 1; i <= 6 * n; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 1; i <= 3 * n; i++) {
		if (check[i * 2 - 1] == check[i * 2]) {
			cout << -1;
			return 0;
		}
	}
	cout << n << '\n';
	for (i = 1; i <= n; i++) {
		if (check[(3 * i - 2) * 2] < check[(3 * i - 2) * 2 - 1]) cout << 3 * i - 2 << ' ';
		else if (check[(3 * i - 1) * 2] < check[(3 * i - 1) * 2 - 1]) cout << 3 * i - 1 << ' ';
		else cout << 3 * i << ' ';
	}
}
