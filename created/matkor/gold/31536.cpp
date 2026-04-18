#include<bits/stdc++.h>
#define ll long long
#define INF 10000000000001
#define pll pair<ll, ll>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

struct info {
    int x1, y1, x2, y2;
};

info rec[2];
vector<pii> v;
vector<pii> out[2][4];

ll distance(pll a, pll b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void find_outside(int x1, int y1, int x2, int y2, int k, int ind) {
	vector<int> u(x2 - x1 + 1, -1), d(x2 - x1 + 1, -1), l(y2 - y1 + 1, -1), r(y2 - y1 + 1, -1);
	int i;
	for (i = 0; i < k; i++) {
		if (l[v[i].y - y1] == -1) l[v[i].y - y1] = i;
		else if (v[l[v[i].y - y1]].x > v[i].x) l[v[i].y - y1] = i;
		if (r[v[i].y - y1] == -1) r[v[i].y - y1] = i;
		else if (v[r[v[i].y - y1]].x < v[i].x) r[v[i].y - y1] = i;
		if (u[v[i].x - x1] == -1) u[v[i].x - x1] = i;
		else if (v[u[v[i].x - x1]].y < v[i].y) u[v[i].x - x1] = i;
		if (d[v[i].x - x1] == -1) d[v[i].x - x1] = i;
		else if (v[d[v[i].x - x1]].y > v[i].y) d[v[i].x - x1] = i;
	}
	for (i = 0; i <= x2 - x1; i++) {
		if (u[i] != -1) out[ind][0].push_back(v[u[i]]);
		if (d[i] != -1) out[ind][1].push_back(v[d[i]]);
	}
	for (i = 0; i <= y2 - y1; i++) {
		if (l[i] != -1) out[ind][2].push_back(v[l[i]]);
		if (r[i] != -1) out[ind][3].push_back(v[r[i]]);
	}
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, k[2], x, y, a;
    for (i = 0; i < 2; i++) {
		cin >> x >> y >> a;
        rec[i] = {x,y,x+a,y+a};
    }
    for (i = 0; i < 2; i++) {
        cin >> k[i];
    }
    for (i = 0; i < 2; i++) {
        v.resize(k[i]);
		for (j = 0; j < k[i]; j++) cin >> v[j].x >> v[j].y;
		find_outside(rec[i].x1, rec[i].y1, rec[i].x2, rec[i].y2, k[i], i);
    }
    ll ans = INF;
    pii rec0, rec1;
    if (rec[0].x2 < rec[1].x1) {
        int l1 = out[0][3].size(), l2 = out[1][2].size();
        for (i = 0; i < l1; i++) {
            for (j = 0; j < l2; j++) {
                ll tmp = distance(out[0][3][i], out[1][2][j]);
                if (ans > tmp) {
                    ans = tmp;
                    rec0 = out[0][3][i];
                    rec1 = out[1][2][j];
                }
            }
        }
    }
    else if (rec[1].x2 < rec[0].x1) {
        int l1 = out[0][2].size(), l2 = out[1][3].size();
        for (i = 0; i < l1; i++) {
            for (j = 0; j < l2; j++) {
                ll tmp = distance(out[0][2][i], out[1][3][j]);
                if (ans > tmp) {
                    ans = tmp;
                    rec0 = out[0][2][i];
                    rec1 = out[1][3][j];
                }
            }
        }
    }
    else if (rec[0].y2 < rec[1].y1) {
        int l1 = out[0][0].size(), l2 = out[1][1].size();
        for (i = 0; i < l1; i++) {
            for (j = 0; j < l2; j++) {
                ll tmp = distance(out[0][0][i], out[1][1][j]);
                if (ans > tmp) {
                    ans = tmp;
                    rec0 = out[0][0][i];
                    rec1 = out[1][1][j];
                }
            }
        }
    }
    else {
        int l1 = out[0][1].size(), l2 = out[1][0].size();
        for (i = 0; i < l1; i++) {
            for (j = 0; j < l2; j++) {
                ll tmp = distance(out[0][1][i], out[1][0][j]);
                if (ans > tmp) {
                    ans = tmp;
                    rec0 = out[0][1][i];
                    rec1 = out[1][0][j];
                }
            }
        }
    }
    cout << ans << '\n';
    cout << rec0.x << ' ' << rec0.y << '\n' << rec1.x << ' ' << rec1.y;
}
