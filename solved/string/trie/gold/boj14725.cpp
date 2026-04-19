#include<iostream>
#include<vector>
#include<map>
using namespace std;

class Node {
public:
	map<string, int> child;
};

class Trie {
private:
	vector<Node> trie;
	int plus_node() {
		Node node;
		trie.push_back(node);
		return trie.size() - 1;
	}
	void add_str_(vector<string>& v, int ind, int node) {
		if (v.size() == ind) return;
		if (!trie[node].child.count(v[ind])) trie[node].child[v[ind]] = plus_node();
		add_str_(v, ind + 1, trie[node].child[v[ind]]);
	}
	void print_(int node, int dep) {
		for (auto& iter : trie[node].child) {
			for (int i = 0; i < dep; i++) cout << "--";
			cout << iter.first << '\n';
			print_(iter.second, dep + 1);
		}
	}
public:
	Trie() {
		plus_node();
	}
	void add_str(vector<string>& v) {
		add_str_(v, 0, 0);
	}
	void print() {
		print_(0, 0);
	}
};

vector<string> temp;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	Trie str_trie;
	int n, k, i, j; cin >> n;
	for (i = 0; i < n; i++) {
		cin >> k;
		temp = vector<string>(k);
		for (j = 0; j < k; j++) cin >> temp[j];
		str_trie.add_str(temp);
		temp.clear();
	}
	str_trie.print();
}
