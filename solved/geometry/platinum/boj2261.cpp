#include<iostream>
#include<algorithm>
#include<vector>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n;
vector<pii> v;

int dis(pii a, pii b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool cmp_y(pii a, pii b) {
	return a.y < b.y;
}

int res(int start, int end) {
	if (start + 1 == end) return dis(v[start], v[end]);
	if (start + 2 == end) return min(dis(v[start], v[end]), min(dis(v[start], v[end - 1]), dis(v[end], v[end - 1])));
	int mid = (start + end) / 2, cmp = min(res(start, mid), res(mid + 1, end)), x = (v[mid].x + v[mid + 1].x) / 2, i;
	vector<pii> le, ri;
	for (i = start; i <= mid; i++) {
		if ((x - v[i].x) * (x - v[i].x) < cmp) le.push_back(v[i]);
	}
	for (i = mid + 1; i <= end; i++) {
		if ((x - v[i].x) * (x - v[i].x) < cmp) ri.push_back(v[i]);
	}
	sort(le.begin(), le.end(), cmp_y);
	sort(ri.begin(), ri.end(), cmp_y);
	i = 0;
	int l = le.size();
	if (l == 0) {
		ri.clear();
		return cmp;
	}
	for (auto& iter1 : ri) {
		int k = dis(iter1, le[i]);
		while (i < l && dis(iter1, le[i]) <= k) {
			k = min(k, dis(iter1, le[i]));
			i++;
		}
		cmp = min(cmp, k);
		i--;
	}
	le.clear();
	ri.clear();
	return cmp;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i; cin >> n;
	v = vector<pii>(n);
	for (i = 0; i < n; i++) cin >> v[i].x >> v[i].y;
	sort(v.begin(), v.end());
	cout << res(0, n - 1);
}
