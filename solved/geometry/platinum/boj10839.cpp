#include<iostream>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;

struct co {
	ll x, y;
	int ind;
};

int n, start_, end_, cnt;
vector<co> v, ch;

ll ccw(co a, co b, co c) {
	return a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
}

void solve() {
	for (int i = start_; i <= end_; i++) {
		while (cnt >= 2 && ccw(ch[cnt - 2], ch[cnt - 1], v[i]) >= 0) {
			ch.pop_back();
			cnt--;
		}
		ch.push_back(v[i]);
		cnt++;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i; cin >> n;
	v = vector<co>(n + 1);
	for (i = 0; i < n; i++) {
		cin >> v[i].x >> v[i].y;
		v[i].ind = i;
	}
	v[n] = v[0];
	v[n].ind = n;
	cin >> start_ >> end_;
	if (start_ == 0 && end_ == 1) cout << 2 << '\n' << "0 1";
	else if (start_ == 1 && end_ == 0) cout << 2 << '\n' << "1 0";
	else if (start_ == 0) {
		start_ = end_;
		end_ = n;
		solve();
		ch[cnt - 1].ind = 0;
		cout << cnt << '\n';
		for (i = cnt - 1; i >= 0; i--) cout << ch[i].ind << ' ';
	}
	else if (end_ == 0) {
		end_ = n;
		solve();
		ch[cnt - 1].ind = 0;
		cout << cnt << '\n';
		for (i = 0; i < cnt; i++) cout << ch[i].ind << ' ';
	}
	else if (start_ < end_) {
		solve();
		cout << cnt << '\n';
		for (i = 0; i < cnt; i++) cout << ch[i].ind << ' ';
	}
	else {
		swap(start_, end_);
		solve();
		cout << cnt << '\n';
		for (i = cnt - 1; i >= 0; i--) cout << ch[i].ind << ' ';
	}
}
