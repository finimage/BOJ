#include<iostream>
#include<vector>
#include<stack>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

struct Frog {
	int topic[5], like[2];
};

Frog frog[3001];
stack<int> st;
vector<pii> gr[3001];
vector<int> lotus[3001], g[6001];
int n, m, num[6001], low[6001], cnt, cnt_, check[6001], ans[3001];
bool visited[6001];

void make_edge(int ind) {
	if (frog[ind].like[0] == frog[ind].like[1]) {
		g[ind * 2].push_back(ind * 2 - 1);
		for (auto& iter : gr[frog[ind].like[0]]) {
			for (auto& itr : lotus[iter.x]) {
				if (frog[itr].topic[iter.y] != frog[ind].topic[iter.y]) {
					if (frog[itr].like[0] == iter.x) g[ind * 2 - 1].push_back(itr * 2);
					else g[ind * 2 - 1].push_back(itr * 2 - 1);
				}
			}
		}
		for (auto& iter : lotus[frog[ind].like[0]]) {
			if (iter == ind) continue;
			if (frog[iter].like[0] == frog[ind].like[0]) g[ind * 2 - 1].push_back(iter * 2);
			else g[ind * 2 - 1].push_back(iter * 2 - 1);
		}
	}
	else {
		int i;
		for (i = 0; i < 2; i++) {
			for (auto& iter : gr[frog[ind].like[i]]) {
				for (auto& itr : lotus[iter.x]) {
					if (frog[itr].topic[iter.y] != frog[ind].topic[iter.y]) {
						if (frog[itr].like[0] == iter.x) g[ind * 2 - (i ? 0 : 1)].push_back(itr * 2);
						else g[ind * 2 - (i ? 0 : 1)].push_back(itr * 2 - 1);
					}
				}
			}
			for (auto& iter : lotus[frog[ind].like[i]]) {
				if (iter == ind) continue;
				if (frog[iter].like[0] == frog[ind].like[i]) g[ind * 2 - (i ? 0 : 1)].push_back(iter * 2);
				else g[ind * 2 - (i ? 0 : 1)].push_back(iter * 2 - 1);
			}
		}
	}
}

void scc(int ind) {
	cnt++;
	num[ind] = low[ind] = cnt;
	visited[ind] = 1;
	st.push(ind);
	for (auto& iter : g[ind]) {
		if (!num[iter]) {
			scc(iter);
			low[ind] = min(low[ind], low[iter]);
		}
		else if (visited[iter]) low[ind] = min(low[ind], low[iter]);
	}
	if (num[ind] == low[ind]) {
		cnt_++;
		while (!st.empty()) {
			int k = st.top();
			st.pop();
			visited[k] = 0;
			check[k] = cnt_;
			if (k == ind) break;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, a, b, c, tf = 0; cin >> n >> m;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= 4; j++) cin >> frog[i].topic[j];
	}
	for (i = 1; i <= n; i++) {
		for (j = 0; j < 2; j++) {
			cin >> frog[i].like[j];
			lotus[frog[i].like[j]].push_back(i);
		}
	}
	for (i = 0; i < m; i++) {
		cin >> a >> b >> c;
		gr[a].push_back({ b,c });
		gr[b].push_back({ a,c });
	}
	for (i = 1; i <= n; i++) make_edge(i);
	for (i = 1; i <= 2 * n; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 1; i <= n; i++) {
		if (check[i * 2 - 1] == check[i * 2]) {
			tf = 1;
			break;
		}
	}
	if (tf) {
		cout << "NO";
		return 0;
	}
	cout << "YES\n";
	for (i = 1; i <= n; i++) {
		if (check[i * 2 - 1] < check[i * 2]) ans[frog[i].like[0]] = i;
		else ans[frog[i].like[1]] = i;
	}
	for (i = 1; i <= n; i++) cout << ans[i] << ' ';
}
