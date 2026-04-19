#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;

struct co {
	ll x, y;
};

struct line {
    co a, b;
};

int n, parent[10001];
line arr[10001];

bool cmp(co a, co b) {
    if (a.x < b.x) return 1;
    else if (a.x == b.x && a.y < b.y) return 1;
    return 0;
}

ll ccw(co a, co b, co c) {
	return a.x * b.y - a.y * b.x - (a.x * c.y - a.y * c.x) + b.x * c.y - b.y * c.x;
}

bool checking(ll a, ll b, ll c, ll d) {
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return b < c || d < a;
}

ll change__(ll a) {
    if (a > 0) return 1;
    else if (a == 0) return 0;
    return -1;
}

bool line_cross(co a, co b, co c, co d) {
	ll A = change__(ccw(a, b, c)), B = change__(ccw(a, b, d));
	ll C = change__(ccw(c, d, a)), D = change__(ccw(c, d, b));
	if (A == 0 && B == 0 && C == 0 && D == 0) {
		return !checking(a.x, b.x, c.x, d.x) && !checking(a.y, b.y, c.y, d.y);
	}
	return 0;
}

int find_(int a) {
    if (a == parent[a]) return a;
    return parent[a] = find_(parent[a]);
}

int union_(int a, int b) {
    a = find_(a);
    b = find_(b);
    if (a == b) return 1;
    parent[b] = a;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, cnt = 0; cin >> n;
    for (i = 1; i <= n; i++) {
        parent[i] = i;
        double a, b, c, d;
        cin >> a >> b >> c >> d;
        arr[i].a.x = (ll)(a * 100 + 0.5);
        arr[i].a.y = (ll)(b * 100 + 0.5);
        arr[i].b.x = (ll)(c * 100 + 0.5);
        arr[i].b.y = (ll)(d * 100 + 0.5);
        co Arr[2] = { arr[i].a, arr[i].b };
        sort(Arr, Arr + 2, cmp);
        arr[i] = { Arr[0],Arr[1] };
        for (j = 1; j < i; j++) {
            int k = find_(j);
            if (i == k) continue;
            if (line_cross(arr[i].a, arr[i].b, arr[k].a, arr[k].b)) {
                if (union_(i, k)) continue;
                cnt++;
                co Arr[4] = { arr[i].a, arr[i].b, arr[k].a, arr[k].b };
                sort(Arr, Arr + 4, cmp);
                arr[i] = { Arr[0],Arr[3] };
            }
        }
    }
    cout << n - cnt;
}
