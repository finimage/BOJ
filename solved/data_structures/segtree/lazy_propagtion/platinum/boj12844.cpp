#include<iostream>
using namespace std;

int arr[500001], tree[2000004], tree_lazy[2000004];

int init(int start, int end, int index) {
	if (start == end) return tree[index] = arr[start];
	int mid = (start + end) / 2;
	return tree[index] = init(start, mid, index * 2) ^ init(mid + 1, end, index * 2 + 1);
}

void lazy(int start, int end, int index) {
	int k = tree_lazy[index];
	if (k == 0) return;
	tree_lazy[index] = 0;
	tree[index] ^= ((end - start + 1) % 2 == 1) ? k : 0;
	if (start == end) return;
	tree_lazy[index * 2] ^= k;
	tree_lazy[index * 2 + 1] ^= k;
}

int modify(int start, int end, int index, int le, int ri, int k) {
	lazy(start, end, index);
	if (ri < start || end < le) return tree[index];
	if (le <= start && end <= ri) {
		tree[index] ^= ((end - start + 1) % 2 == 1) ? k : 0;
		if (start != end) {
			tree_lazy[index * 2] ^= k;
			tree_lazy[index * 2 + 1] ^= k;
		}
		return tree[index];
	}
	int mid = (start + end) / 2;
	return tree[index] = modify(start, mid, index * 2, le, ri, k) ^ modify(mid + 1, end, index * 2 + 1, le, ri, k);
}

int XOR(int start, int end, int index, int le, int ri) {
	lazy(start, end, index);
	if (ri < start || end < le) return 0;
	if (le <= start && end <= ri) return tree[index];
	int mid = (start + end) / 2;
	return XOR(start, mid, index * 2, le, ri) ^ XOR(mid + 1, end, index * 2 + 1, le, ri);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int N, M, i, a, b, c, d; cin >> N;
	for (i = 1; i <= N; i++) cin >> arr[i];
	init(1, N, 1);
	cin >> M;
	while (M--) {
		cin >> a >> b >> c;
		b++;
		c++;
		if (a == 1) {
			cin >> d;
			modify(1, N, 1, b, c, d);
		}
		else cout << XOR(1, N, 1, b, c) << '\n';
	}
}
