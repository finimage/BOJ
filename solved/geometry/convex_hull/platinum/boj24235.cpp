#include<iostream>
#include<vector>
#include<algorithm>
#define ld long double
#define pdd pair<ld, ld>
#define x first
#define y second
using namespace std;

int n, cnt;
ld s, le = 1e9 + 1, ri = - 1e9 - 1, mid, part;
vector<pdd> v, ch, ch_;

bool cmp1(pdd a, pdd b) {
	if (a.y < b.y) return 1;
	else if (a.y == b.y && a.x < b.x) return 1;
	return 0;
}

ld ccw(pdd a, pdd b, pdd c) {
	return a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
}

ld dis(pdd a, pdd b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool cmp2(pdd a, pdd b) {
	ld k = ccw(v[0], a, b);
	if (k == 0) return dis(v[0], a) < dis(v[0], b);
	return k > 0;
}

ld find_(pdd a, pdd b, ld c) {
	return (a.y - b.y) * (c - a.x) / (a.x - b.x) + a.y;
}

void cut() {
	ch_.clear();
	part = 0;
	int i, l;
	for (i = 0; i < cnt; i++) {
		if (ch[i].x < mid) ch_.push_back(ch[i]);
		if ((ch[i].x - mid) * (ch[(i + 1) % cnt].x - mid) < 0) ch_.push_back({ mid,find_(ch[i], ch[(i + 1) % cnt], mid) });
		else if (ch[i].x == mid) ch_.push_back(ch[i]);
	}
	l = ch_.size();
	for (i = 2; i < l; i++) part += abs(ccw(ch_[0], ch_[i - 1], ch_[i]));
	part /= 2;
}

void b_search() {
	ld ans = 0;
	while (le <= ri) {
		mid = (le + ri) / 2;
		cut();
		if (abs(s - part) < 0.0009) {
			ans = mid;
			break;
		}
		else if (s > part) le = mid + 0.00001;
		else ri = mid - 0.00001;
	}
	ans = mid;
	printf("%Lf", ans);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i; cin >> n;
	v = vector<pdd>(n);
	for (i = 0; i < n; i++) {
		cin >> v[i].x >> v[i].y;
		le = min(le, v[i].x);
		ri = max(ri, v[i].x);
	}
	sort(v.begin(), v.end(), cmp1);
	sort(v.begin() + 1, v.end(), cmp2);
	for (i = 0; i < n; i++) {
		while (cnt >= 2 && ccw(ch[cnt - 2], ch[cnt - 1], v[i]) <= 0) {
			ch.pop_back();
			cnt--;
		}
		ch.push_back(v[i]);
		cnt++;
	}
	for (i = 2; i < cnt; i++) s += abs(ccw(ch[0], ch[i - 1], ch[i]));
	s /= 4;
	b_search();
}
