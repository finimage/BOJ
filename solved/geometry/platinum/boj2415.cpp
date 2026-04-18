#include<iostream>
#include<vector>
#include<algorithm>
#define ll long long
#define co pair<ll, ll>
#define x first
#define y second
using namespace std;

struct info {
	co mid;
	ll dis;
	int A, B;
};

int n;
co arr[1501];
info v[1500 * 1500 / 2];

ll sq(co a, co b, co c) {
	return a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
}

ll dis(co a, co b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool cmp(info a, info b) {
	if (a.mid.x < b.mid.x) return 1;
	else if (a.mid.x == b.mid.x) {
		if (a.mid.y < b.mid.y) return 1;
		else if (a.mid.y == b.mid.y && a.dis < b.dis) return 1;
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, l = 0; cin >> n;
	ll ans = 0;
	for (i = 1; i <= n; i++) {
		cin >> arr[i].x >> arr[i].y;
		for (j = 1; j < i; j++) {
			v[l++] = { {arr[i].x + arr[j].x, arr[i].y + arr[j].y}, dis(arr[i], arr[j]), i, j };
		}
	}
	sort(v, v + l, cmp);
	for (i = 0; i < l; i++) {
		for (j = i - 1; j >= 0; j--) {
			if (v[i].mid == v[j].mid && v[i].dis == v[j].dis) {
				ans = max(ans, abs(sq(arr[v[i].A], arr[v[i].B], arr[v[j].A])));
			}
            else break;
		}
	}
	cout << ans;
}
