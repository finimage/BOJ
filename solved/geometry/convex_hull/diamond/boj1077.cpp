#include<iostream>
#include<algorithm>
#include<vector>
#define ld long double
using namespace std;

struct co {
	ld x, y;
};

int n, m;
vector<co> v1, v2, ans, ans_;

bool cmp(co a, co b) {
	if (a.y < b.y) return 1;
	else if (a.y == b.y && a.x < b.x) return 1;
	return 0;
}

ld ccw(co a, co b, co c) {
	return a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
}

ld dis(co a, co b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool comp(co a, co b) {
	ld k = ccw(ans[0], a, b);
	if (k == 0) return dis(ans[0], a) < dis(ans[0], b);
	return k > 0;
}

//내부 점 판정
int inside(co a, vector<co>& v, int k) {
	int le = 1, ri = k - 1;
	if (ccw(v[0], v[le], a) < 0) return 0;
	if (ccw(v[ri], v[0], a) < 0) return 0;
	while (le + 1 < ri) {
		int mid = (le + ri) / 2;
		if (ccw(v[mid], v[0], a) >= 0) ri = mid;
		else le = mid;
	}
	if (ccw(v[le], v[ri], a) >= 0) return 1;
	return 0;
}

//선분 교차 판정
bool checking(int a, int b, int c, int d) {
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return b < c || d < a;
}

ld change__(ld a) {
    if (a > 0) return 1;
    else if (a == 0) return 0;
    return -1;
}

bool line_cross(co a, co b, co c, co d) {
	ld A = change__(ccw(a, b, c)), B = change__(ccw(a, b, d));
	ld C = change__(ccw(c, d, a)), D = change__(ccw(c, d, b));
	if (A * B == 0 && C * D == 0) {
		return !checking(a.x, b.x, c.x, d.x) && !checking(a.y, b.y, c.y, d.y);
	}
	return A * B <= 0 && C * D <= 0;
}

co lcc(co a, co b, co c, co d) {
	co k = { 0, };
	if (a.x != b.x && c.x != d.x) {
		k.x = ((a.y - b.y) * a.x * (c.x - d.x) - a.y * (a.x - b.x) * (c.x - d.x) - (c.y - d.y) * c.x * (a.x - b.x) + c.y * (a.x - b.x) * (c.x - d.x)) / ((a.y - b.y) * (c.x - d.x) - (c.y - d.y) * (a.x - b.x));
		k.y = (a.y - b.y) * (k.x - a.x) / (a.x - b.x) + a.y;
	}
	else if (a.x == b.x && c.x != d.x) {
		k.x = a.x;
		k.y = (c.y - d.y) * (k.x - c.x) / (c.x - d.x) + c.y;
	}
	else if (a.x != b.x && c.x == d.x) {
		k.x = c.x;
		k.y = (a.y - b.y) * (k.x - a.x) / (a.x - b.x) + a.y;
	}
	return k;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j; cin >> n >> m;
	v1 = vector<co>(n);
	v2 = vector<co>(m);
	for (i = 0; i < n; i++) cin >> v1[i].x >> v1[i].y;
	for (i = 0; i < m; i++) cin >> v2[i].x >> v2[i].y;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (line_cross(v1[i], v1[(i + 1) % n], v2[j], v2[(j + 1) % m])) {
				//둘의 교점 추가
				ans.push_back(lcc(v1[i], v1[(i + 1) % n], v2[j], v2[(j + 1) % m]));
			}
		}
	}
	for (i = 0; i < n; i++) {
		if (inside(v1[i], v2, m)) ans.push_back(v1[i]);
	}
	for (i = 0; i < m; i++) {
		if (inside(v2[i], v1, n)) ans.push_back(v2[i]);
	}
	int l = ans.size();
	if (l < 3) {
		cout << "0.0";
		return 0;
	}
	sort(ans.begin(), ans.end(), cmp);
	sort(ans.begin() + 1, ans.end(), comp);
	int cnt = 0;
	for (i = 0; i < l; i++) {
		while (cnt >= 2 && ccw(ans_[cnt - 2], ans_[cnt - 1], ans[i]) <= 0) {
			ans_.pop_back();
			cnt--;
		}
		ans_.push_back(ans[i]);
		cnt++;
	}
	l = ans_.size();	
	ld answer = 0;
	for (i = 1; i < l - 1; i++) answer += abs(ccw(ans_[0], ans_[i], ans_[i + 1]));
	printf("%0.15Lf", answer / 2);
}
