#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct co {
	int x, y;
};

bool cmp(const co& a, const co& b) {
	if (a.y < b.y) return 1;
	else if (a.y == b.y && a.x < b.x) return 1;
	return 0;
}

int n, m;
vector<co> v1, v2, ans1, ans2;

int ccw(const co& a, const co& b, const co& c) {
	int k = a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
	if (k > 0) return 1;
	else if (k < 0) return -1;
	return 0;
}

int dis(const co& a, const co& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool comp1(const co& a, const co& b) {
	int k = ccw(v1[0], a, b);
	if (k == 0) return dis(v1[0], a) < dis(v1[0], b);
	return k > 0;
}

bool comp2(const co& a, const co& b) {
	int k = ccw(v2[0], a, b);
	if (k == 0) return dis(v2[0], a) < dis(v2[0], b);
	return k > 0;
}

void solve1() {
	int i, tf = 1;
	v1 = vector<co>(n);
	for (i = 0; i < n; i++) cin >> v1[i].x >> v1[i].y;
	v2 = vector<co>(m);
	for (i = 0; i < m; i++) cin >> v2[i].x >> v2[i].y;
	if (ccw(v1[0], v1[1], v2[0]) == 0) {
		if ((v2[0].x - v1[0].x) * (v2[0].x - v1[1].x) > 0) tf = 1;
		else if ((v2[0].y - v1[0].y) * (v2[0].y - v1[1].y) > 0) tf = 1;
		else tf = 0;
	}
	if (tf) cout << "YES\n";
	else cout << "NO\n";
}

void solve2() {
	int i, tf = 1;
	v1 = vector<co>(n);
	for (i = 0; i < n; i++) cin >> v1[i].x >> v1[i].y;
	v2 = vector<co>(m);
	for (i = 0; i < m; i++) cin >> v2[i].x >> v2[i].y;
	if (ccw(v2[0], v2[1], v1[0]) == 0) {
		if ((v1[0].x - v2[0].x) * (v1[0].x - v2[1].x) > 0) tf = 1;
		else if ((v1[0].y - v2[0].y) * (v1[0].y - v2[1].y) > 0) tf = 1;
		else tf = 0;
	}
	if (tf) cout << "YES\n";
	else cout << "NO\n";
}

void solve3() {
	int i;
	v1 = vector<co>(n);
	for (i = 0; i < n; i++) cin >> v1[i].x >> v1[i].y;
	v2 = vector<co>(m);
	for (i = 0; i < m; i++) cin >> v2[i].x >> v2[i].y;
	cout << "YES\n";
}

bool checking(int a, int b, int c, int d) {
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return b < c || d < a;
}

bool check(co a, co b, co c, co d) {
	int A = ccw(a, b, c), B = ccw(a, b, d);
	int C = ccw(c, d, a), D = ccw(c, d, b);
	if (A * B == 0 && C * D == 0) {
		return !checking(a.x, b.x, c.x, d.x) && !checking(a.y, b.y, c.y, d.y);
	}
	return A * B <= 0 && C * D <= 0;
}

void solve4() {
	int i, j, cnt1 = 0, cnt2 = 0, tf = 0;
	v1 = vector<co>(n);
	for (i = 0; i < n; i++) cin >> v1[i].x >> v1[i].y;
	sort(v1.begin(), v1.end(), cmp);
	sort(v1.begin() + 1, v1.end(), comp1);
	for (i = 0; i < n; i++) {
		while (cnt1 >= 2 && ccw(ans1[cnt1 - 2], ans1[cnt1 - 1], v1[i]) <= 0) {
			ans1.pop_back();
			cnt1--;
		}
		ans1.push_back(v1[i]);
		cnt1++;
	}
	v2 = vector<co>(m);
	for (i = 0; i < m; i++) cin >> v2[i].x >> v2[i].y;
	sort(v2.begin(), v2.end(), cmp);
	sort(v2.begin() + 1, v2.end(), comp2);
	for (i = 0; i < m; i++) {
		while (cnt2 >= 2 && ccw(ans2[cnt2 - 2], ans2[cnt2 - 1], v2[i]) <= 0) {
			ans2.pop_back();
			cnt2--;
		}
		ans2.push_back(v2[i]);
		cnt2++;
	}
	if (cnt1 > 2) {
		for (i = 0; i < cnt2; i++) {
			if (tf) continue;
			int temp = 1;
			for (j = 0; j < cnt1; j++) {
				int k = ccw(ans1[j], ans1[(j + 1) % cnt1], ans2[i]);
				if (k < 0) {
					temp = 0;
					break;
				}
			}
			tf = temp;
		}
	}
	if (tf) {
		cout << "NO\n";
		return;
	}
	if (cnt2 > 2) {
		for (i = 0; i < cnt1; i++) {
			if (tf) continue;
			int temp = 1;
			for (j = 0; j < cnt2; j++) {
				int k = ccw(ans2[j], ans2[(j + 1) % cnt2], ans1[i]);
				if (k < 0) {
					temp = 0;
					break;
				}
			}
			tf = temp;
		}
	}
	if (tf) {
		cout << "NO\n";
		return;
	}
	for (i = 0; i < cnt1; i++) {
		for (j = 0; j < cnt2; j++) {
			if (check(ans1[i], ans1[(i + 1) % cnt1], ans2[j], ans2[(j + 1) % cnt2])) {
				tf = 1;
				break;
			}
		}
		if (tf) break;
	}
	if (tf) cout << "NO\n";
	else cout << "YES\n";
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) {
		cin >> n >> m;
		if (n == 2 && m == 1) solve1();
		else if (n == 1 && m == 2) solve2();
		else if (n == 1 && m == 1) solve3();
		else solve4();
		v1.clear();
		v2.clear();
		ans1.clear();
		ans2.clear();
	}
}
