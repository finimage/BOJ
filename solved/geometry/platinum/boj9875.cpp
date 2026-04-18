#include<iostream>
#include<algorithm>
#include<vector>
#define ll long long
using namespace std;

struct co {
	ll x, y;
};

int n, cnt1 = 0, cnt2 = 0;
vector<co> v1, v2, ans1, ans2;

bool cmp(co a, co b) {
	if (a.y < b.y) return 1;
	else if (a.y == b.y && a.x < b.x) return 1;
	return 0;
}

ll ccw(co a, co b, co c) {
	return a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
}

ll dis(co a, co b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool comp1(co a, co b) {
	ll k = ccw(v1[0], a, b);
	if (k == 0) return dis(v1[0], a) < dis(v1[0], b);
	return k > 0;
}

bool comp2(co a, co b) {
	ll k = ccw(v2[0], a, b);
	if (k == 0) return dis(v2[0], a) < dis(v2[0], b);
	return k > 0;
}

int check(co a, co b, co c) {
	if (ccw(a, b, c)) return 0;
	if (min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y)) return 1;
	return 0;
}

int check_1(co a) {
	int le = 1, ri = cnt1 - 1;
	if (ccw(ans1[0], ans1[le], a) < 0) return 0;
	if (ccw(ans1[ri], ans1[0], a) < 0) return 0;
	while (le + 1 < ri) {
		int mid = (le + ri) / 2;
		if (ccw(ans1[mid], ans1[0], a) >= 0) ri = mid;
		else le = mid;
	}
	if (ccw(ans1[le], ans1[ri], a) >= 0) return 1;
	return 0;
}

int check_2(co a) {
	int le = 1, ri = cnt2 - 1;
	if (ccw(ans2[0], ans2[le], a) < 0) return 0;
	if (ccw(ans2[ri], ans2[0], a) < 0) return 0;
	while (le + 1 < ri) {
		int mid = (le + ri) / 2;
		if (ccw(ans2[mid], ans2[0], a) >= 0) ri = mid;
		else le = mid;
	}
	if (ccw(ans2[le], ans2[ri], a) >= 0) return 1;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, ans_1 = 0, ans_2 = 0; cin >> n;
	v1 = vector<co>(n);
	v2 = vector<co>(n);
	for (i = 0; i < n; i++) cin >> v1[i].x >> v1[i].y;
	for (i = 0; i < n; i++) cin >> v2[i].x >> v2[i].y;
	sort(v1.begin(), v1.end(), cmp);
	sort(v1.begin() + 1, v1.end(), comp1);
	sort(v2.begin(), v2.end(), cmp);
	sort(v2.begin() + 1, v2.end(), comp2);
	for (i = 0; i < n; i++) {
		while (cnt1 >= 2 && ccw(ans1[cnt1 - 2], ans1[cnt1 - 1], v1[i]) <= 0) {
			cnt1--;
			ans1.pop_back();
		}
		cnt1++;
		ans1.push_back(v1[i]);
	}
	for (i = 0; i < n; i++) {
		while (cnt2 >= 2 && ccw(ans2[cnt2 - 2], ans2[cnt2 - 1], v2[i]) <= 0) {
			cnt2--;
			ans2.pop_back();
		}
		cnt2++;
		ans2.push_back(v2[i]);
	}
	if (cnt1 > 2) {
		for (i = 0; i < n; i++) ans_1 += check_1(v2[i]);
	}
	else {
		for (i = 0; i < n; i++) ans_1 += check(ans1[0], ans1[1], v2[i]);
	}
	if (cnt2 > 2) {
		for (i = 0; i < n; i++) ans_2 += check_2(v1[i]);
	}
	else {
		for (i = 0; i < n; i++) ans_2 += check(ans2[0], ans2[1], v1[i]);
	}
	cout << ans_1 << ' ' << ans_2;
}
