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
	int i, j, cnt = 2, y = 0;
	v = vector<co>(n);
	for (i = 0; i < n; i++) {
		cin >> v[i].x >> v[i].y;
		y = max(y, v[i].y);
	}
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
	double res = 40001, temp, p1, p2;
	for (i = 0; i < cnt; i++) {
		temp = p1 = 0;
		p2 = 20001;
		co a = { 0,0 }, b = { ans[i].y - ans[(i + 1) % cnt].y,ans[(i + 1) % cnt].x - ans[i].x };
		if (b.x * b.y > 0) {
			a.y += y;
			b.y += y;
		}
		double dist = sqrt(dis(ans[i], ans[(i + 1) % cnt])), dist_ = sqrt(dis(a, b));
		for (j = i; j < i + 2; j++) {
			p1 = max(p1, (double)abs(ccw(a, b, ans[j % cnt])) / dist_);
			p2 = min(p2, (double)abs(ccw(a, b, ans[j % cnt])) / dist_);
		}
		for (j = i + 2; j < i + cnt; j++) {
			temp = max(temp, (double)abs(ccw(ans[i], ans[(i + 1) % cnt], ans[j % cnt])) / dist);
			p1 = max(p1, (double)abs(ccw(a, b, ans[j % cnt])) / dist_);
			p2 = min(p2, (double)abs(ccw(a, b, ans[j % cnt])) / dist_);
		}
		res = min(res, (p1 - p2) * 2 + temp * 2);
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	while (cin >> n) {
		printf("%0.8f\n", solve());
		v.clear();
		ans.clear();
	}
}
