#include<iostream>
using namespace std;

int s_check[10], sub_check[10], check[10];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	string s, sub;
	cin >> s >> sub;
	int i, j, index, start, tf, sl = s.size(), subl = sub.size();
	for (i = 0; i < sl; i++) s_check[s[i] - '0']++;
	for (i = 0; i < subl; i++) sub_check[sub[i] - '0']++;
	for (i = 0; i < 10; i++) {
		if (s_check[i] == 0) continue;
		if (s_check[i] == sub_check[i]) {
			for (j = 0; j < sl; j++) {
				if (s[j] == i + '0') {
					s.erase(j, 1);
					j--;
					sl--;
				}
			}
			subl -= s_check[i];
			s_check[i] = 0;
			sub_check[i] = 0;
		}
	}
	int k = sl - subl;
	start = 0;
	while(subl){
		tf = 0;
		index = 0;
		for (i = 9; i >= 0; i--) {
			if (s_check[i] == 0) continue;
			for (j = 0; j < 10; j++) check[j] = 0;
			for (j = start; j <= start + subl; j++) {
				if (s[j] - '0' == i) {
					if (s_check[i] == sub_check[i]) {
						s.erase(j, 1);
						subl--;
						s_check[i]--;
						sub_check[i]--;
						continue;
					}
					tf = 1;
					index = j;
					break;
				}
				if (sub_check[s[j] - '0'] >= check[s[j] - '0'] + 1) {
					check[s[j] - '0']++;
				}
				else break;
			}
			if (tf) break;
		}
		if (tf) {
			for (i = 0; i < 10; i++) {
				s_check[i] -= check[i];
				sub_check[i] -= check[i];
				subl -= check[i];
				sl -= check[i];
				check[i] = 0;
			}
			s.erase(start, index - start);
		}
		s_check[s[start] - '0']--;
		start++;
		if (start >= k) {
			s.erase(k, s.size() - start + 1);
			subl = 0;
		}
	}
	cout << s;
}
