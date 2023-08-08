#include<iostream>
using namespace std;

int A[100001], L[100001];
int cnt[100001];

void make_() {
	int i, j;
	for (i = 1; i <= 100001; i++) {
		if (A[i]) cnt[i]++;
		if (cnt[i] == 0) continue;
		for (j = i * 2; j <= 100001; j += i) {
			cnt[j] += cnt[i];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, q, a, i; cin >> n;
	for (i = 0; i < n; i++) {
		cin >> a;
		A[a] = 1;
	}
	make_();
	cin >> q;
	for (i = 0; i < q; i++) cin >> A[i];
	for (i = 0; i < q; i++) cout << cnt[A[i]] << ' ';
}
