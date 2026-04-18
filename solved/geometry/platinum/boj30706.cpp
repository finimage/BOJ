#include<iostream>
#define ll long long
#define MOD 1000000007
using namespace std;

ll n, m, k, sxa, sxa2, sxb, sxb2, sxc, sxc2, sya, sya2, syb, syb2, syc, syc2;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll i, x, y; cin >> n >> m >> k;
	for (i = 0; i < n; i++) {
		cin >> x >> y;
		sxa = (sxa + x) % MOD;
		sxa2 = (sxa2 + x * x) % MOD;
		sya = (sya + y) % MOD;
		sya2 = (sya2 + y * y) % MOD;
	}
	for (i = 0; i < m; i++) {
		cin >> x >> y;
		sxb = (sxb + x) % MOD;
		sxb2 = (sxb2 + x * x) % MOD;
		syb = (syb + y) % MOD;
		syb2 = (syb2 + y * y) % MOD;
	}
	for (i = 0; i < k; i++) {
		cin >> x >> y;
		sxc = (sxc + x) % MOD;
		sxc2 = (sxc2 + x * x) % MOD;
		syc = (syc + y) % MOD;
		syc2 = (syc2 + y * y) % MOD;
	}
	ll A2 = 2 * m % MOD * k % MOD * ((sxa2 + sya2) % MOD) % MOD;
	ll B2 = 2 * n % MOD * k % MOD * ((sxb2 + syb2) % MOD) % MOD;
	ll C2 = 2 * m % MOD * n % MOD * ((sxc2 + syc2) % MOD) % MOD;
	ll S1 = (A2 + B2 + C2) % MOD;
	ll A = k * ((2 * sxa % MOD * sxb % MOD + 2 * sya % MOD * syb % MOD - sxa * syb % MOD + sxb * sya % MOD + MOD) % MOD) % MOD;
	ll B = m * ((2 * sxa % MOD * sxc % MOD + 2 * sya % MOD * syc % MOD - sxc * sya % MOD + sxa * syc % MOD + MOD) % MOD) % MOD;
	ll C = n * ((2 * sxc % MOD * sxb % MOD + 2 * syc % MOD * syb % MOD - sxb * syc % MOD + sxc * syb % MOD + MOD) % MOD) % MOD;
	ll S2 = (A + B + C) % MOD;
	cout << (S1 - S2 + MOD) % MOD;
}
