#include<iostream>
#include<algorithm>
#include<vector>
#define ll long long
using namespace std;

struct co {
	ll x, y;
};

bool cmp(const co& a, const co& b) {
	if (a.y < b.y) return 1;
	else if (a.y == b.y && a.x < b.x) return 1;
	return 0;
}

vector<co> v, ans;
int n;

ll ccw(const co& a, const co& b, const co& c) {
	return a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
}

ll dis(const co& a, const co& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool comp(const co& a, const co& b) {
	ll k = ccw(v[0], a, b);
	if (k == 0) return dis(v[0], a) < dis(v[0], b);
	return k > 0;
}

ll ccw_4(co a, co b, co c, co d) {
	d.x -= c.x - b.x;
	d.y -= c.y - b.y;
	return ccw(a, b, d);
}

void solve() {
	cin >> n;
	int i, cnt = 2;
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
	int ind = 1;
	ll res = 0;
	co a, b;
	for (i = 0; i < cnt; i++) {
		while ((ind + 1) != i && ccw_4(ans[i], ans[(i + 1) % cnt], ans[ind % cnt], ans[(ind + 1) % cnt]) > 0) {
			if (res < dis(ans[i], ans[ind % cnt])) {
				res = dis(ans[i], ans[ind % cnt]);
				a = ans[i];
				b = ans[ind % cnt];
			}
			ind++;
		}
		if (res < dis(ans[i], ans[ind % cnt])) {
			res = dis(ans[i], ans[ind % cnt]);
			a = ans[i];
			b = ans[ind % cnt];
		}
	}
	cout << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << '\n';
	v.clear();
	ans.clear();
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
