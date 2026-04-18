#include<bits/stdc++.h>
#define ld long double
using namespace std;

int arr[1000001];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, t, i; cin >> n >> m >> t;
	ld s = 0, as = 0, Max = 0;
	for (i = 0; i < n; i++) {
		cin >> arr[i];
		s += (ld)arr[i];
		Max = max(Max, (ld)arr[i]);
	}
	if (m == 1) {
		printf("%.8Lf", s - Max * Max * t / s);
		return 0;
	}
	ld p = (ld)m / (m - 1);
	for (i = 0; i < n; i++) as += pow((ld)arr[i] * arr[i], p);
	printf("%.8Lf", s - pow(as, 1 / p) * pow(t, (ld)1 / m) / s);
}
