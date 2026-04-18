#include<iostream>
using namespace std;

bool people[2][2000000];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    long long int n, m, k, i, j, a;
    cin >> n >> m >> k;
    while (m--) {
        cin >> a;
        people[0][a] = 1;
        people[1][a] = 1;
    }
    for (i = 1; i <= k; i <<= 1) {
        if (k & i) {
            for (j = 0; j < n; j++) {
                if (people[0][j]) people[1][(j + i * 2) % n] ^= 1;
            }
            for (j = 0; j < n; j++) people[0][j] = people[1][j];
        }
    }
    a = 0;
    for (i = 0; i < n; i++) {
        if (people[0][i]) a++;
    }
    cout << a;
}
