#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;

struct info {
	int x, y, cost;
};

struct Info {
	string s;
	int cost;
};

struct comp {
	bool operator()(const Info& a, const Info& b) {
		return a.cost > b.cost;
	}
};

unordered_map<string, int> um;
int n, m, arr[8];
vector<info> v;
string start, cmp;
priority_queue<Info, vector<Info>, comp> pq;

void switching(char* a, char* b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

void dijkstra() {
	pq.push({ start,0 });
	string s;
	int cost;
	um[s] = 0;
	while (!pq.empty()) {
		s = pq.top().s;
		cost = pq.top().cost;
		pq.pop();
		if (cost > um[s]) continue;
		for (auto& iter : v) {
			string new_s = s;
			switching(&new_s[iter.x], &new_s[iter.y]);
			if (!um.count(new_s)) {
				um[new_s] = cost + iter.cost;
				pq.push({ new_s,um[new_s] });
			}
			else if (um[new_s] > cost + iter.cost) {
				um[new_s] = cost + iter.cost;
				pq.push({ new_s,um[new_s] });
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, c; cin >> n;
	for (i = 0; i < n; i++) {
		cin >> arr[i];
		start += arr[i] - 1 + '0';
	}
	sort(arr, arr + n);
	for (i = 0; i < n; i++) cmp += arr[i] - 1 + '0';
	cin >> m;
	for (i = 0; i < m; i++) {
		cin >> a >> b >> c;
		v.push_back({ a - 1,b - 1,c });
	}
	dijkstra();
	if (um.count(cmp)) cout << um[cmp];
	else cout << -1;
}
