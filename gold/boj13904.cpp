#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

struct info {
	int day, grade;
};

bool cmp (const info& a, const info& b) {
	return a.day < b.day;
}

info arr[1001];
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, cnt = 0, ans = 0; cin >> n;
	for (i = 0; i < n; i++) cin >> arr[i].day >> arr[i].grade;
	sort(arr, arr + n, cmp);
	for (i = 0; i < n; i++) {
		pq.push(arr[i].grade);
		cnt++;
		while (arr[i].day < cnt) {
			pq.pop();
			cnt--;
		}
	}
	while (!pq.empty()) {
		ans += pq.top();
		pq.pop();
	}
	cout << ans;
}
