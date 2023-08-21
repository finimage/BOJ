#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;

struct co {
	int x, y;
};

bool cmp(const co& a, const co& b) {
	if (a.y < b.y) return 1;
	else if (a.y == b.y && a.x < b.x) return 1;
	return 0;
}

vector<co> v, ans;
int n;

int ccw(const co& a, const co& b, const co& c) {
	return a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
}

int dis(const co& a, const co& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool comp(const co& a, const co& b) {
	int k = ccw(v[0], a, b);
	if (k == 0) return dis(v[0], a) < dis(v[0], b);
	return k > 0;
}

double solve() {
	int i, j, cnt = 2;
	v = vector<co>(n);
	for (i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
	sort(v.begin(), v.end(), cmp);
	sort(v.begin() + 1, v.end(), comp);
	ans.push_back(v[0]);
	ans.push_back(v[1]);
	for (i = 2; i < n; i++) {
		while (cnt >= 2 && ccw(ans[cnt - 2], ans[cnt - 1], v[i]) <= 0) {
			ans.pop_back();
			cnt--;
		}
		ans.push_back(v[i]);
		cnt++;
	}
	double res = 20001, temp;
	for (i = 0; i < cnt; i++) {
		temp = 0;
		double dist = sqrt(dis(ans[i], ans[(i + 1) % cnt]));
		for (j = i + 2; j < i + cnt; j++) {
			temp = max(temp, (double)abs(ccw(ans[i], ans[(i + 1) % cnt], ans[j % cnt])) / dist);
		}
		res = min(res, temp);
	}
	if (res * 100 > (int)(res * 100)) return (double)((int)(res * 100)) / 100 + 0.01;
	return (double)((int)(res * 100)) / 100;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i = 1;
	while (1) {
		cin >> n;
		if (n == 0) break;
		printf("Case %d: %0.2f\n", i, solve());
		v.clear();
		ans.clear();
		i++;
	}
}
