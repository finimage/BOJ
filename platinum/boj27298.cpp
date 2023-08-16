#include<iostream>
using namespace std;

string s, s_3[3], s_4[4];
int sum_[10005], l;
int arr[10][4] = {
	{0,0,0,0},
	{2,3,5,8},
	{1,3,5,8},
	{1,2,5,8},
	{0,0,0,0},
	{1,2,3,8},
	{1,2,3,9},
	{0,0,0,0},
	{1,2,3,5},
	{1,2,3,6},
};
int arr_[10][3] = {
	{0,0,0},
	{1,1,1},
	{2,2,2},
	{3,3,3},
	{4,4,4},
	{5,5,5},
	{6,6,6},
	{7,7,7},
	{5,6,9},
	{5,6,8},
};
bool check[10];

string sum_1() {
	int i, j;
	string temp = "";
	for (i = 0; i < l; i++) {
		for (j = 0; j < 3; j++) s_3[j] += arr_[s[i] - '0'][j] + '0';
	}
	for (i = l - 1; i >= 0; i--) {
		for (j = 0; j < 3; j++) sum_[l - i - 1] += (int)s_3[j][i] - '0';
		sum_[l - i] += sum_[l - i - 1] / 10;
		sum_[l - i - 1] %= 10;
	}
	if (sum_[l]) temp += sum_[l] + '0';
	for (i = l - 1; i >= 0; i--) temp += sum_[i] + '0';
	return temp;
}

string sum_2() {
	int i, j;
	string temp = "";
	for (i = 0; i < l; i++) {
		sum_[i] = 0;
		for (j = 0; j < 4; j++) s_4[j] += arr[s[i] - '0'][j] + '0';
	}
	sum_[l] = 0;
	for (i = l - 1; i >= 0; i--) {
		for (j = 0; j < 4; j++) sum_[l - i - 1] += (int)s_4[j][i] - '0';
		sum_[l - i] += sum_[l - i - 1] / 10;
		sum_[l - i - 1] %= 10;
	}
	if (sum_[l]) temp += sum_[l] + '0';
	for (i = l - 1; i >= 0; i--) temp += sum_[i] + '0';
	return temp;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> s;
	for (auto& iter : s) {
		l++;
		check[iter - '0'] = 1;
	}
	if (check[4] || check[7]) {
		cout << sum_1() << " 3\n";
		for (int i = 0; i < 3; i++) cout << s_3[i] << '\n';
	}
	else {
		string s1 = sum_1(), s2 = sum_2();
		int l1 = s1.size(), l2 = s2.size();
		if (l1 > l2) {
			cout << s2 << " 4\n";
			for (int i = 0; i < 4; i++) cout << s_4[i] << '\n';
		}
		else if (l1 < l2) {
			cout << s1 << " 3\n";
			for (int i = 0; i < 3; i++) cout << s_3[i] << '\n';
		}
		else {
			if (s1 > s2) {
				cout << s2 << " 4\n";
				for (int i = 0; i < 4; i++) cout << s_4[i] << '\n';
			}
			else {
				cout << s1 << " 3\n";
				for (int i = 0; i < 3; i++) cout << s_3[i] << '\n';
			}
		}
	}
}
