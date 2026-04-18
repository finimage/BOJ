#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

struct query {
	int a, x, y, num;
};

int Q, tree[1200004][2];
vector<int> X, DIS;
vector<query> q;

ll dis(query a) {
	return (ll)a.x * a.x + (ll)a.y * a.y;
}

bool cmp1(query a, query b) {
	int A = abs(a.x), B = abs(b.x);
	if (A < B) return 1;
	else if (A == B) {
		if (b.y == 0) return 0;
		else if (a.y == 0) return 1;
		else if (a.x < b.x) return 1;
		else if (a.x > b.x) return 0;
		else return a.y < b.y;
	}
	return 0;
}

bool cmp2(query a, query b) {
	ll A = dis(a), B = dis(b);
	if (A < B) return 1;
	else if (A == B) {
		if (b.y == 0) return 1;
		else if (a.y == 0) return 0;
		else if (a.x < b.x) return 1;
		else if (a.x > b.x) return 0;
		else return a.y < b.y;
	}
	return 0;
}

bool cmp3(query a, query b) {
	return a.num < b.num;
}

int update1(int start, int end, int ind, int i) {
	if (i < start || end < i) return tree[ind][0];
	if (start == end) return tree[ind][0] = !tree[ind][0];
	int mid = (start + end) / 2;
	return tree[ind][0] = update1(start, mid, ind * 2, i) + update1(mid + 1, end, ind * 2 + 1, i);
}

int update2(int start, int end, int ind, int i) {
	if (i < start || end < i) return tree[ind][1];
	if (start == end) return tree[ind][1] = !tree[ind][1];
	int mid = (start + end) / 2;
	return tree[ind][1] = update2(start, mid, ind * 2, i) + update2(mid + 1, end, ind * 2 + 1, i);
}

int res1(int start, int end, int ind, int le, int ri) {
	if (ri < start || end < le) return 0;
	if (le <= start && end <= ri) return tree[ind][0];
	int mid = (start + end) / 2;
	return res1(start, mid, ind * 2, le, ri) + res1(mid + 1, end, ind * 2 + 1, le, ri);
}

int res2(int start, int end, int ind, int le, int ri) {
	if (ri < start || end < le) return 0;
	if (le <= start && end <= ri) return tree[ind][1];
	int mid = (start + end) / 2;
	return res2(start, mid, ind * 2, le, ri) + res2(mid + 1, end, ind * 2 + 1, le, ri);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, k = 1; cin >> Q;
	q.resize(Q);
	X.resize(Q);
	DIS.resize(Q);
	for (i = 0; i < Q; i++) {
		cin >> q[i].a >> q[i].x;
		if (q[i].a == 2) cin >> q[i].y;
		q[i].num = i;
	}
	sort(q.begin(), q.end(), cmp1);
	X[q[0].num] = k++;
	for (i = 1; i < Q; i++) {
		if (q[i].x == q[i - 1].x && q[i].y == q[i - 1].y) X[q[i].num] = X[q[i - 1].num];
		else X[q[i].num] = k++;
	}
	sort(q.begin(), q.end(), cmp2);
	k = 1;
	DIS[q[0].num] = k++;
	for (i = 1; i < Q; i++) {
		if (q[i].x == q[i - 1].x && q[i].y == q[i - 1].y) DIS[q[i].num] = DIS[q[i - 1].num];
		else DIS[q[i].num] = k++;
	}
	sort(q.begin(), q.end(), cmp3);
	for (i = 0; i < Q; i++) {
		if (q[i].a == 1) cout << res1(1, Q, 1, 1, X[q[i].num] - 1) - res2(1, Q, 1, 1, DIS[q[i].num] - 1) << '\n';
		else {
			update1(1, Q, 1, X[q[i].num]);
			update2(1, Q, 1, DIS[q[i].num]);
		}
	}
}
