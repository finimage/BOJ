#include<iostream>
#include<queue>
using namespace std;

struct info {
	int ind, v;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.ind < b.ind;
	}
};

priority_queue<info, vector<info>, cmp> pq;
int arr[500001], index_[500001], next_[500001];
bool check[500001];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, k, i, ans = 0, cnt = 0; cin >> n >> k;
	for (i = 1; i <= k; i++) {
		cin >> arr[i];
		next_[i] = 500002;
		if (check[arr[i]]) next_[index_[arr[i]]] = i;
		check[arr[i]] = 1;
		index_[arr[i]] = i;
	}
	for (i = 1; i <= k; i++) check[arr[i]] = 0;
	for (i = 1; i <= k; i++) {
		if (check[arr[i]]) pq.push({ next_[i],arr[i] });
		else if (cnt < n) {
			cnt++;
			check[arr[i]] = 1;
			pq.push({ next_[i],arr[i] });
		}
		else {
			while (!check[pq.top().v]) pq.pop();
			check[pq.top().v] = 0;
			pq.pop();
			pq.push({ next_[i],arr[i] });
			check[arr[i]] = 1;
			ans++;
		}
	}
	cout << ans;
}
