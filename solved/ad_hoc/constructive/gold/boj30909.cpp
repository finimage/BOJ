#include<bits/stdc++.h>
using namespace std;

string s;
string miss = "miss", hit = "hit", sunk = "sunk";
int dx[4] = {1,0,0,-1}, dy[4] = {0,1,-1,0};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int i, j, n, K; cin >> n >> K;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (abs(i - j) % 5 == 0) {
                cout << i << ' ' << j << endl;
                cin >> s;
                if (s == miss) continue;
                else if (s == hit) {
                    for (int t = 0; t < 4; t++) {
                        for (int k = 1; k <= 4; k++) {
                            int x = i + dx[t] * k;
                            int y = j + dy[t] * k;
                            if (!(1 <= x && x <= n && 1 <= y && y <= n)) continue;
                            cout << x << ' ' << y << endl;
                            cin >> s;
                            if (s == sunk) K--;
                            if (K == 0) return 0;
                        }
                    }
                }
                else K--;
                if (K == 0) return 0;
            }
        }
    }
}
