#include<iostream>
#include<vector>
#define ll long long
#define Mod 1000000000
using namespace std;

struct fibo {
	ll arr[2][2];
};

vector<fibo> Fibo;
vector<int> bi;

void make_bi(ll num) {
	while (num) {
		if (num % 2) bi.push_back(1);
		else bi.push_back(0);
		num /= 2;
	}
}

fibo m_matrix(fibo a, fibo b) {
	int i, j, t;
	fibo temp = { 0, };
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			for (t = 0; t < 2; t++) {
				temp.arr[i][j] += a.arr[i][t] * b.arr[t][j] % Mod;
				temp.arr[i][j] %= Mod;
			}
		}
	}
	return temp;
}

ll find_fibo(ll num) {
	if (num == 0) return 0;
	if (num == 1 || num == 2) return 1;
	make_bi(num);
	int l = bi.size(), total = Fibo.size(), i;
	if (l > total) {
		for (i = total; i < l; i++) Fibo.push_back(m_matrix(Fibo.back(), Fibo.back()));
	}
	fibo temp = { 1,0,0,1 };
	for (i = 0; i < l; i++) {
		if (bi[i]) temp = m_matrix(temp, Fibo[i]);
	}
	bi.clear();
	return temp.arr[0][1];
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll a, b; cin >> a >> b;
	Fibo.push_back({ { {1,1},{1,0} } });
	cout << (find_fibo(b + 2) - find_fibo(a + 1) + Mod) % Mod;
}
