#include<bits/stdc++.h>
using namespace std;

int n, m, hand, beh, ans;
vector<int> v1, v2, point, prefix_sum, prefix_v2;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int i, j, a, b, l, l1, l2; cin >> n >> m;
	string s;
	hand = beh = 1;
	for (i = 0; i < n; i++) {
		cin >> s;
		if (s == "Act") {
			cin >> a >> b;
			if (a > 0 && b > 0) {
				beh += a - 1;
				hand += b - 1;
			}
			if (a > 1 && b == 0) v1.emplace_back(a);
			if (a == 0 && b > 1) v2.emplace_back(b);
		}
		else {
			cin >> a;
			point.emplace_back(a);
		}
	}
	l = point.size();
	if (l == 0) {
		for (i = 0; i < m; i++) {
			cin >> s;
			if (s == "Point") {
				cin >> a;
				ans = max(ans, a);
			}
			else cin >> a >> b;
		}
		cout << ans;
		return 0;
	}
	sort(point.begin(), point.end(), greater<int>());
	prefix_sum.resize(l + 1);
	for (i = 1; i <= l; i++) prefix_sum[i] = prefix_sum[i - 1] + point[i - 1];
	sort(v1.begin(), v1.end(), greater<int>());
	sort(v2.begin(), v2.end(), greater<int>());
	l1 = v1.size();
	l2 = v2.size();
	prefix_v2.resize(l2 + 1);
	for (i = 1; i <= l2; i++) prefix_v2[i] = prefix_v2[i - 1] + v2[i - 1] - 1;
	int h = hand;
	if (hand == 1 && beh == 1) {
		i = j = 0;
		if (l2 > 0) ans = prefix_sum[min(l, v2[0])];
		ans = max(ans, point[0]);
		if (i < l1 && j < l2) {
			hand++;
			while (beh) {
				if (beh == 1) {
					if (i == l1) {
						if (j == l2) break;
						else hand += v2[j++] - 1;
						beh--;
					}
					else {
						if (j == l2) break;
						else {
							beh += v1[i++] - 1;
							hand--;
						}
					}
				}
				else {
					if (j == l2) break;
					else hand += v2[j++] - 1;
					beh--;
				}
			}
			if (j < l2) {
				for (i = 0; i < m; i++) {
					cin >> s;
					if (s == "Act") {
						cin >> a >> b;
						if (a > 0 && b > 1) ans = max(ans, prefix_sum[min(l, hand + b - 2 + prefix_v2[min(l2, j + a)] - prefix_v2[j])]);
						if (a == 0 && b > 1) ans = max(ans, prefix_sum[min(l, b)]);
					}
					else {
						cin >> a;
						ans = max(ans, prefix_sum[min(l, v2[0] - 1)] + a);
					}
				}
			}
			else {
				for (i = 0; i < m; i++) {
					cin >> s;
					if (s == "Act") {
						cin >> a >> b;
						if (a > 0 && b > 1) ans = max(ans, prefix_sum[min(l, hand + b - 2)]);
						if (a == 0 && b > 1) ans = max(ans, prefix_sum[min(l, b)]);
					}
					else {
						cin >> a;
						ans = max(ans, prefix_sum[min(l, v2[0] - 1)] + a);
					}
				}
			}
		}
		else if (j < l2) {
			for (i = 0; i < m; i++) {
				cin >> s;
				if (s == "Act") {
					cin >> a >> b;
					if (a > 0 && b > 0) ans = max(ans, prefix_sum[min(l, b + prefix_v2[min(l2, j + a)])]);
					if (a == 0 && b > 1) ans = max(ans, prefix_sum[min(l, b)]);
				}
				else {
					cin >> a;
					ans = max(ans, prefix_sum[min(l, v2[0] - 1)] + a);
				}
			}
		}
		else {
			for (i = 0; i < m; i++) {
				cin >> s;
				if (s == "Act") { 
					cin >> a >> b;
					if (a > 0 && b > 0) ans = max(ans, prefix_sum[min(l, b)]);
					if (a == 0 && b > 1) ans = max(ans, prefix_sum[min(l, b)]);
				}
				else {
					cin >> a;
					ans = max(ans, a);
				}
			}
		}
	}
	else {
		i = j = 0;
		while (beh) {
			if (beh == 1) {
				if (i == l1) {
					if (j == l2) break;
					else hand += v2[j++] - 1;
					beh--;
				}
				else {
					if (j == l2) break;
					else {
						beh += v1[i++] - 1;
						hand--;
					}
				}
			}
			else {
				if (j == l2) break;
				else hand += v2[j++] - 1;
				beh--;
			}
		}
		ans = prefix_sum[min(l, hand)];
		int res = ans;
		if (j < l2) {
			for (i = 0; i < m; i++) {
				cin >> s;
				if (s == "Act") {
					cin >> a >> b;
					if (a > 0 && b > 0) ans = max(ans, prefix_sum[min(l, hand + b - 1 + prefix_v2[min(l2, j + a - 1)] - prefix_v2[j])]);
					if (a > 1 && b == 0) ans = max(ans, prefix_sum[min(l, hand - 1 + prefix_v2[min(l2, j + a - 1)] - prefix_v2[j])]);
					if (a == 0 && b > 1) ans = max(ans, prefix_sum[min(l, hand - v2[j - 1] + max(v2[j - 1], b))]);
				}
				else {
					cin >> a;
					if (l >= hand) ans = max(ans, res - point[hand - 1] + a);
					else ans = max(ans, res + a);
				}
			}
		}
		else {
			for (i = 0; i < m; i++) {
				cin >> s;
				if (s == "Act") {
					cin >> a >> b;
					if (a > 0 && b > 0) ans = max(ans, prefix_sum[min(l, hand + b - 1)]);
					if (a == 0 && b > 1) {
						if (beh == 0) ans = max(ans, prefix_sum[min(l, max(hand, hand - v2[j - 1] + b))]);
						else ans = max(ans, prefix_sum[min(l, hand + b - 1)]);
					}
				}
				else {
					cin >> a;
					if (l >= hand) ans = max(ans, res - point[hand - 1] + a);
					else ans = max(ans, res + a);
				}
			}
		}
	}
	cout << ans;
}
