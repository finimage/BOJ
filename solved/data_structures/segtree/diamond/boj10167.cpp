#include<iostream>
#include<algorithm>
#define ll long long
#define INF 4000000000000
using namespace std;

struct info {
	ll le, ri, sum, Max;
};

struct Co {
	int ind, x, y, v;
};

info tree[12004];
Co arr[3001], co[3001];

bool cmp1(Co a, Co b) {
	if (arr[a.ind].x < arr[b.ind].x) return 1;
	else if (arr[a.ind].x == arr[b.ind].x && arr[a.ind].y < arr[b.ind].y) return 1;
	return 0;
}

bool cmp2(Co a, Co b) {
	if (arr[a.ind].y < arr[b.ind].y) return 1;
	else if (arr[a.ind].y == arr[b.ind].y && arr[a.ind].x < arr[b.ind].x) return 1;
	return 0;
}

void init(int start, int end, int ind) {
	tree[ind] = { 0,0,0,0 };
	if (start == end) return;
	int mid = (start + end) / 2;
	init(start, mid, ind * 2);
	init(mid + 1, end, ind * 2 + 1);
}

info update(int start, int end, int ind, int i, int v) {
	if (i < start || end < i) return tree[ind];
	if (start == end) {
		tree[ind].le += v;
		tree[ind].ri += v;
		tree[ind].sum += v;
		tree[ind].Max += v;
		return tree[ind];
	}
	int mid = (start + end) / 2;
	info a = update(start, mid, ind * 2, i, v), b = update(mid + 1, end, ind * 2 + 1, i, v);
	tree[ind].le = max(a.le, a.sum + b.le);
	tree[ind].ri = max(b.ri, b.sum + a.ri);
	tree[ind].sum = a.sum + b.sum;
	tree[ind].Max = max(max(a.Max, b.Max), a.ri + b.le);
	return tree[ind];
}

info find_max(int start, int end, int ind, int le, int ri) {
	if (ri < start || end < le) return { -INF,-INF,-INF,-INF };
	if (le <= start && end <= ri) return tree[ind];
	int mid = (start + end) / 2;
	info a = find_max(start, mid, ind * 2, le, ri), b = find_max(mid + 1, end, ind * 2 + 1, le, ri);
	if (a.Max != -INF && b.Max != -INF) {
		info ret = { 0, };
		ret.le = max(a.le, a.sum + b.le);
		ret.ri = max(b.ri, a.ri + b.sum);
		ret.sum = a.sum + b.sum;
		ret.Max = max(max(a.Max, b.Max), a.ri + b.le);
		return ret;
	}
	if (b.Max == -INF) return a;
	if (a.Max == -INF) return b;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, j; cin >> n;
	for (i = 1; i <= n; i++) {
		cin >> arr[i].x >> arr[i].y >> co[i].v;
		co[i].ind = i;
	}
	sort(co + 1, co + n + 1, cmp2);
	co[1].y = 1;
	for (i = 2; i <= n; i++) {
		if (arr[co[i - 1].ind].y == arr[co[i].ind].y) co[i].y = co[i - 1].y;
		else co[i].y = co[i - 1].y + 1;
	}
	sort(co + 1, co + n + 1, cmp1);
	co[1].x = 1;
	for (i = 2; i <= n; i++) {
		if (arr[co[i - 1].ind].x == arr[co[i].ind].x) co[i].x = co[i - 1].x;
		else co[i].x = co[i - 1].x + 1;
	}
	ll Max = 0;
	for (i = 1; i <= n; i++) {
		if (co[i].x == co[i - 1].x) continue;
		init(1, n, 1);
		int Max_y = 0, Min_y = 3001, x = co[i].x;
		for (j = i; j <= n; j++) {
			if (x != co[j].x) {
				Max = max(Max, find_max(1, n, 1, Min_y, Max_y).Max);
				x = co[j].x;
			}
			Min_y = min(Min_y, co[j].y);
			Max_y = max(Max_y, co[j].y);
			update(1, n, 1, co[j].y, co[j].v);
		}
		Max = max(Max, find_max(1, n, 1, Min_y, Max_y).Max);
	}
	cout << Max;
}
