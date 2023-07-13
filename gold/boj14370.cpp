#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

string s, check_string[10] = { "SIX","EIGHT","TWO","ZERO","FOUR","ONE","THREE","FIVE","SEVEN","NINE" };
char check_alp[10] = { 'X','G','W','Z','U','O','H','F','S','I' };
int check_num[10] = { 6,8,2,0,4,1,3,5,7,9 };

void ans() {
	int alp[26] = { 0, }, i, j, l, temp;
	vector<int> v;
	for (auto iter = s.begin(); iter != s.end(); iter++) alp[*iter-'A']++;
	for (i = 0; i < 10; i++) {
		l = check_string[i].size();
		temp = alp[check_alp[i] - 'A'];
		for (j = 0; j < l; j++) alp[check_string[i][j] - 'A'] -= temp;
		for (j = 0; j < temp; j++) v.push_back(check_num[i]);
	}
	l = v.size();
	sort(v.begin(), v.end());
	for (i = 0; i < l; i++) cout << v[i];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int t, i;
	cin >> t;
	for (i = 1; i <= t; i++) {
		cin >> s;
		cout << "Case #" << i << ": ";
		ans();
		cout << '\n';
	}
}
