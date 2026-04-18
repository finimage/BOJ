#include<bits/stdc++.h>
using namespace std;

string a[2], t;
vector<int> p[2];
stack<char> st[2];
stack<int> stp[2];
list<char> dq;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int l, k, i; cin >> a[0] >> t;
	l = a[0].size();
	p[0].resize(l + 1);
	k = 0;
	for (i = 1; i < l; i++) {
		while (k > 0 && a[0][k] != a[0][i]) k = p[0][k - 1];
		if (a[0][k] == a[0][i]) k++;
		p[0][i] = k;
	}
	for (i = l - 1; i >= 0; i--) a[1].push_back(a[0][i]);
	p[1].resize(l + 1);
	k = 0;
	for (i = 1; i < l; i++) {
		while (k > 0 && a[1][k] != a[1][i]) k = p[1][k - 1];
		if (a[1][k] == a[1][i]) k++;
		p[1][i] = k;
	}
	for (auto& iter : t) dq.push_back(iter);
	int tf = 0;
	while (!dq.empty()) {
		char tmp;
		if (tf) {
			tmp = dq.back();
			dq.pop_back();
		}
		else {
			tmp = dq.front();
			dq.pop_front();
		}
		if (!st[tf].empty()) {
			k = stp[tf].top();
			while (k > 0 && a[tf][k] != tmp) k = p[tf][k - 1];
			if (a[tf][k] == tmp) k++;
			st[tf].push(tmp);
			stp[tf].push(k);
		}
		else {
			if (a[tf][0] == tmp) stp[tf].push(1);
			else stp[tf].push(0);
			st[tf].push(tmp);
		}
		if (stp[tf].top() == l) {
			for (i = 0; i < l; i++) {
				st[tf].pop();
				stp[tf].pop();
			}
			if (!st[tf].empty()) {
				k = stp[tf].top();
				for (i = 0; i < k; i++) {
					if (tf) {
						dq.push_back(st[tf].top());
						st[tf].pop();
						stp[tf].pop();
					}
					else {
						dq.push_front(st[tf].top());
						st[tf].pop();
						stp[tf].pop();
					}
				}
			}
			tf = !tf;
		}
	}
	while (!st[0].empty()) {
		dq.push_front(st[0].top());
		st[0].pop();
	}
	while (!st[1].empty()) {
		dq.push_back(st[1].top());
		st[1].pop();
	}
	for (auto& iter : dq) cout << iter;
}
