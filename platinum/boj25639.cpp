#include<iostream>
#define ll long long
using namespace std;

struct info {
	ll Max, Le, Ri, Sum;
};

ll ori[100001], arr[100001];
info tree[400004];

void init(int start, int end, int index) {
	if (start == end) {
		tree[index] = { arr[start],arr[start],arr[start],arr[start] };
		return;
	}
	int mid = (start + end) / 2;
	init(start, mid, index * 2);
	init(mid + 1, end, index * 2 + 1);
	tree[index].Sum = tree[index * 2].Sum + tree[index * 2 + 1].Sum;
	tree[index].Le = max(tree[index * 2].Le, tree[index * 2].Sum + tree[index * 2 + 1].Le);
	tree[index].Ri = max(tree[index * 2 + 1].Ri, tree[index * 2].Ri + tree[index * 2 + 1].Sum);
	tree[index].Max = max(max(tree[index * 2].Max, tree[index * 2 + 1].Max), tree[index * 2].Ri + tree[index * 2 + 1].Le);
}

info res(int start, int end, int index, int le, int ri) {
	if (ri < start || end < le) return { 0,0,0,0 };
	if (le <= start && end <= ri) return tree[index];
	int mid = (start + end) / 2;
	info a = res(start, mid, index * 2, le, ri), b = res(mid + 1, end, index * 2 + 1, le, ri), k;
	k.Sum = a.Sum + b.Sum;
	k.Le = max(a.Le, a.Sum + b.Le);
	k.Ri = max(b.Ri, a.Ri + b.Sum);
	k.Max = max(max(a.Max, b.Max), a.Ri + b.Le);
	return k;
}

void update(int start, int end, int index, int i) {
	if (i < start || end < i) return;
	if (start == end) {
		tree[index] = { arr[start],arr[start],arr[start],arr[start] };
		return;
	}
	int mid = (start + end) / 2;
	update(start, mid, index * 2, i);
	update(mid + 1, end, index * 2 + 1, i);
	tree[index].Sum = tree[index * 2].Sum + tree[index * 2 + 1].Sum;
	tree[index].Le = max(tree[index * 2].Le, tree[index * 2].Sum + tree[index * 2 + 1].Le);
	tree[index].Ri = max(tree[index * 2 + 1].Ri, tree[index * 2].Ri + tree[index * 2 + 1].Sum);
	tree[index].Max = max(max(tree[index * 2].Max, tree[index * 2 + 1].Max), tree[index * 2].Ri + tree[index * 2 + 1].Le);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, i, a, b, order; cin >> n;
	for (i = 1; i <= n; i++) {
		cin >> ori[i];
		arr[i] = ori[i] - ori[i - 1];
	}
	arr[1] = 0;
	init(1, n, 1);
	cin >> m;
	while (m--) {
		cin >> order >> a >> b;
		if (order == 1) {
			ori[a] = b;
			if (a == 1) {
				arr[a + 1] = ori[a + 1] - ori[a];
				update(1, n, 1, a + 1);
			}
			else if (a == n) {
				arr[a] = ori[a] - ori[a - 1];
				update(1, n, 1, a);
			}
			else {
				arr[a] = ori[a] - ori[a - 1];
				arr[a + 1] = ori[a + 1] - ori[a];
				update(1, n, 1, a);
				update(1, n, 1, a + 1);
			}
		}
		else {
			if (a == b) cout << 0 << '\n';
			else cout << max(res(1, n, 1, a + 1, b).Max, (ll)0) << '\n';
		}
	}
}
