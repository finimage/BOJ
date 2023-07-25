#include<iostream>
using namespace std;

struct info {
	int Max, Le, Ri, Sum;
};

int arr[100001];
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
	if (ri < start || end < le) return { -100000001,-100000001,-100000001,-100000001 };
	if (le <= start && end <= ri) return tree[index];
	int mid = (start + end) / 2;
	info a = res(start, mid, index * 2, le, ri), b = res(mid + 1, end, index * 2 + 1, le, ri), k;
	if (a.Max != -100000001 && b.Max != -100000001) {
		k.Sum = a.Sum + b.Sum;
		k.Le = max(a.Le, a.Sum + b.Le);
		k.Ri = max(b.Ri, a.Ri + b.Sum);
		k.Max = max(max(a.Max, b.Max), a.Ri + b.Le);
	}
	else if (a.Max == -100000001 && b.Max != -100000001) k = b;
	else if (a.Max != -100000001 && b.Max == -100000001) k = a;
	return k;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, i, a, b; cin >> n;
	for (i = 1; i <= n; i++) cin >> arr[i];
	init(1, n, 1);
	cin >> m;
	while (m--) {
		cin >> a >> b;
		cout << res(1, n, 1, a, b).Max << '\n';
	}
}
