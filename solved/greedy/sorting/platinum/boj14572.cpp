#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct info {
	int M, d;
	vector<int> v;
};

bool cmp(const info& a, const info& b) {
	return a.d < b.d;
}

info stu[100001];
int check[31];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int N, K, D, i, j, temp, le = 0, ri = 0, ans = 0; cin >> N >> K >> D;
	for (i = 0; i < N; i++) {
		cin >> stu[i].M >> stu[i].d;
		for (j = 0; j < stu[i].M; j++) {
			cin >> temp;
			stu[i].v.push_back(temp);
		}
	}
	sort(stu, stu + N, cmp);
	while (le <= ri && ri < N) {
		temp = 0;
		while (stu[ri].d - stu[le].d > D) {
			for (auto& iter : stu[le].v) check[iter]--;
			le++;
		}
		for (auto& iter : stu[ri].v) check[iter]++;
		ri++;
		for (i = 1; i <= K; i++) {
			if (check[i] == ri - le) temp--;
			if (check[i]) temp++;
		}
		ans = max(ans, temp * (ri - le));
	}
	cout << ans;
}
