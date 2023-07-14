#include<iostream>
using namespace std;

char KY[500001] = { 0, };
int check[500001] = { 0, }, KY_value[500001] = { 0, }, group[500001][3] = { 0, }, tree[2000004][2] = { 0, };
long long int sum_[500001] = { 0, };

void init(int start, int end, int index) {
	if (start == end) {
		int temp = (KY[start] == 'K') ? 0 : 1;
		tree[index][temp] = KY_value[start];
		return;
	}
	int mid = (start + end) / 2;
	init(start, mid, index * 2);
	init(mid + 1, end, index * 2 + 1);
	tree[index][0] = max(tree[index * 2][0], tree[index * 2 + 1][0]);
	tree[index][1] = max(tree[index * 2][1], tree[index * 2 + 1][1]);
}

int find_(int start, int end, int index, int le, int ri, int a) {
	if (start > ri || end < le) return 0;
	if (start >= le && end <= ri) return tree[index][a];
	int mid = (start + end) / 2;
	return max(find_(start, mid, index * 2, le, ri, a), find_(mid + 1, end, index * 2 + 1, le, ri, a));
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, t, i, j = 0, start = 1, val = 0, le, ri, ky;
	long long int S, ansk, ansy, tem[2];
	char temp = '_';
	cin >> n;
	for (i = 1; i <= n; i++) {
		cin >> KY[i];
		if (temp != KY[i]) {
			temp = KY[i];
			j++;
		}
		check[i] = j;
	}
	temp = KY[1];
	j = 1;
	for (i = 1; i <= n; i++) {
		cin >> KY_value[i];
		if (temp != KY[i]) {
			group[j][0] = start;
			group[j][1] = i - 1;
			group[j][2] = val;
			sum_[j] = sum_[j - 1] + val;
			start = i;
			val = 0;
			temp = KY[i];
			j++;
		}
		val = max(val, KY_value[i]);
	}
	group[j][0] = start;
	group[j][1] = n;
	group[j][2] = val;
	init(1, n, 1);
	cin >> t;
	for (i = 0; i < t; i++) {
		cin >> le >> ri;
		if (check[ri] == check[le]) {
			cout << "YK 0\n";
			continue;
		}
		S = sum_[check[ri] - 1] - sum_[check[le]];
		ansk = 0;
		ansy = 0;
		ky = (KY[le] == 'K') ? 0 : 1;
		tem[0] = (long long int)find_(1, n, 1, le, group[check[le]][1], ky);
		ky = (KY[ri] == 'K') ? 0 : 1;
		tem[1] = (long long int)find_(1, n, 1, group[check[ri]][0], ri, ky);
		if (KY[le] == 'K' && KY[ri] == 'K') {
			ansk = S + tem[0];
			ansy = S + tem[1];
		}
		if (KY[le] == 'K' && KY[ri] == 'Y') {
			ansk = S + tem[0] + tem[1];
			ansy = S;
		}
		if (KY[le] == 'Y' && KY[ri] == 'K') {
			ansy = S + tem[0] + tem[1];
			ansk = S;
		}
		if (KY[le] == 'Y' && KY[ri] == 'Y') {
			ansy = S + tem[0];
			ansk = S + tem[1];
		}
		if (ansy == ansk) cout << "YK " << ansk << '\n';
		else if (ansy > ansk) cout << "Y " << ansy << '\n';
		else cout << "K " << ansk << '\n';
	}
}
