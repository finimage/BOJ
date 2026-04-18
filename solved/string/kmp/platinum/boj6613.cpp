#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;

string bug, s;
vector<int> p, p_, check;
stack<int> st;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, i, j, l, k, ss;
	while (cin >> n) {
		cin >> bug;
		cin.ignore();
		l = bug.size();
		bug = ' ' + bug;
		p.resize(l + 1, 0);
		k = 0;
		for (i = 2; i <= l; i++) {
			while (k > 0 && bug[k + 1] != bug[i]) k = p[k];
			if (bug[k + 1] == bug[i]) k++;
			p[i] = k;
		}
		while (n--) {
			getline(cin, s);
			ss = s.size();
			s = ' ' + s;
			check.clear();
			check.resize(ss + 1, 0);
			p_.resize(ss + 1, 0);
			k = 0;
			for (i = 1; i <= ss; i++) {
			    st.push(i);
				while (k > 0 && bug[k + 1] != s[i]) k = p[k];
				if (bug[k + 1] == s[i]) k++;
				if (k == l) {
				    for (j = 1; j < l; j++) st.pop();
				    check[st.top()] = i;
				    st.pop();
				    if (st.empty()) k = 0;
				    else k = p_[st.top()];
				}
				p_[i] = k;
			}
			for (i = 1; i <= ss; i++) {
				if (check[i]) i = check[i];
				else cout << s[i];
			}
			cout << '\n';
			st = stack<int>();
		}
	}
}
