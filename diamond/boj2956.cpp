#include<iostream>
#include<unordered_map>
#include<algorithm>
using namespace std;

struct Info {
	char alp;
	int cnt;
};

bool cmp(const Info& a, const Info& b) {
    return a.alp < b.alp;
}

Info info[26];
int print_col[51];
unordered_map<int, int> um;
char arr[51][30001], diagonal[30001];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, k, odd = 0, i, j, p, ind = 0; cin >> n >> k;
	for (i = 0; i < k; i++) {
		cin >> info[i].alp >> info[i].cnt;
		if (info[i].cnt % 2 == 1) odd++;
	}
	cin >> p;
	for (i = 0; i < p; i++) {
		cin >> print_col[i];
        print_col[i]--;
		um[print_col[i]] = i + 1;
	}
	if (odd > n) {
		cout << "IMPOSSIBLE";
		return 0;
	}
    sort(info, info + k, cmp);
    for (i = 0; i < n; i++) {
        while (info[ind].cnt == 0) ind++;
        if (!diagonal[i]) {
            if (info[ind].cnt % 2 == 1) {
                odd--;
                info[ind].cnt--;
                diagonal[i] = info[ind].alp;
                if (um.count(i)) arr[um[i]][i] = info[ind].alp;
            }
            else if (n - i - 1 > odd) {
                info[ind].cnt -= 2;
                diagonal[i] = info[ind].alp;
                if (um.count(i)) arr[um[i]][i] = info[ind].alp;
                diagonal[i + 1] = info[ind].alp;
                if (um.count(i + 1)) arr[um[i + 1]][i + 1] = info[ind].alp;
            }
            else {
                int temp = ind;
                while (info[temp].cnt % 2 == 0) temp++;
                info[temp].cnt--;
                odd--;
                diagonal[i] = info[temp].alp;
                if (um.count(i)) arr[um[i]][i] = info[temp].alp;
            }
        }
        else if (info[ind].cnt % 2 == 1) {
            odd--;
            info[ind].cnt--;
            diagonal[i + 1] = info[ind].alp;
            if (um.count(i + 1)) arr[um[i + 1]][i + 1] = info[ind].alp;
        }
        if (info[ind].cnt / 2 >= n - i - 1) {
            info[ind].cnt -= 2 * (n - i - 1);
            for (j = 0; j < p; j++) {
                if (print_col[j] > i)  arr[um[print_col[j]]][i] = info[ind].alp;
            }
            if (um.count(i)) {
                for (j = i + 1; j < n; j++) arr[um[i]][j] = info[ind].alp;
            }
            if (info[ind].cnt == 0) ind++;
        }
        else {
            int temp = ind, need = n - i - 1, start = i + 1;
            while (need) {
                if (info[temp].cnt / 2 >= need) {
                    info[temp].cnt -= 2 * need;
                    for (j = 0; j < p; j++) {
                        if (print_col[j] >= start) arr[um[print_col[j]]][i] = info[temp].alp;
                    }
                    if (um.count(i)) {
                        for (j = start; j < n; j++) arr[um[i]][j] = info[temp].alp;
                    }
                    need = 0;
                }
                else {
                    for (j = 0; j < p; j++) {
                        if (print_col[j] >= start + info[temp].cnt / 2) break;
                        if (print_col[j] >= start) arr[um[print_col[j]]][i] = info[temp].alp;
                    }
                    if (um.count(i)) {
                        for (j = start; j < start + info[temp].cnt / 2; j++) arr[um[i]][j] = info[temp].alp;
                    }
                    need -= info[temp].cnt / 2;
                    start += info[temp].cnt / 2;
                    info[temp].cnt -= info[temp].cnt / 2 * 2;
                    temp++;
                }
            }
        }
	}
	for (i = 0; i < n; i++) {
		for (j = 1; j <= p; j++) cout << arr[j][i];
		cout << '\n';
	}
}
