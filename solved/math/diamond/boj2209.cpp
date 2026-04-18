#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct co {
	int x, y, ind;
};

vector<co> origin, v;
co k;

int dis(co a, co b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

bool cmp(const co& a, const co& b) {
	return dis(a, k) > dis(b, k);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, j, t, ans = 30001; cin >> n;
	v = vector<co>(n);
	origin = vector<co>(n);
	for (i = 0; i < n; i++) {
		cin >> v[i].x >> v[i].y;
		v[i].ind = i;
		origin[i] = v[i];
	}
	for (i = 0; i < n - 1; i++) {
		k = origin[i];
		sort(v.begin(), v.end(), cmp);
		for (j = i + 1; j < n; j++) {
			int temp = 0;
			for (t = 0; t < n; t++) {
				if (dis(origin[j], v[temp]) < dis(origin[j], v[t])) {
					ans = min(ans, dis(origin[i], origin[j]) + dis(origin[i], v[t]) + dis(origin[j], v[temp]));
					temp = t;
				}
			}
		}
	}
	cout << ans;
}
