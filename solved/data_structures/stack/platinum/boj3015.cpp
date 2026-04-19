#include<iostream>
#include<stack>
using namespace std;

stack<pair<int, int>> s;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, i, cnt = 0, temp;
	long long int ans = 0;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> temp;
		cnt = 0;
		while (!s.empty() && s.top().first <= temp) {
			if (s.top().first == temp) cnt += s.top().second;
			ans += s.top().second;
			s.pop();
		}
		if (!s.empty() && s.top().first > temp) ans++;
		s.push({ temp,cnt + 1 });
	}
	cout << ans;
}
