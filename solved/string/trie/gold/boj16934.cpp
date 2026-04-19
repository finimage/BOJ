#include<iostream>
#include<vector>
using namespace std;

class Node {
public:
	bool fin;
	int arr[26], cnt;
	Node() {
		fin = 0;
		cnt = 0;
		for (int i = 0; i < 26; i++) arr[i] = -1;
	}
};

class Trie {
private:
	vector<Node> trie;
	int plus_node() {
		Node node;
		trie.push_back(node);
		return trie.size() - 1;
	}
	void Swap(char* a, char* b) {
		char temp = *a;
		*a = *b;
		*b = temp;
	}
	string itos_(int k) {
		string s = "";
		while (k) {
			s += (char)(k % 10 + '0');
			k /= 10;
		}
		int i, l = s.size();
		for (i = 0; i < l / 2; i++) Swap(&s[i], &s[l - i - 1]);
		return s;
	}
	void add_n_(string& s, int ind, int node, string* res, bool tf) {
		if (s.size() == ind) {
			trie[node].fin = 1;
			trie[node].cnt++;
			if (!tf && trie[node].cnt > 1) (*res) += itos_(trie[node].cnt);
			return;
		}
		if (!tf) (*res) += s[ind];
		if (trie[node].arr[s[ind] - 'a'] == -1) {
			trie[node].arr[s[ind] - 'a'] = plus_node();
			if (tf) add_n_(s, ind + 1, trie[node].arr[s[ind] - 'a'], res, 1);
			else add_n_(s, ind + 1, trie[node].arr[s[ind] - 'a'], res, 1);
		}
		else add_n_(s, ind + 1, trie[node].arr[s[ind] - 'a'], res, tf);
	}
public:
	Trie() {
		plus_node();
	}
	string add_n(string& s) {
		string res = "";
		add_n_(s, 0, 0, &res, 0);
		return res;
	}
};

vector<string> ans;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, ind; cin >> n;
	string s, temp;
	Trie n_trie;
	for (i = 0; i < n; i++) {
		cin >> s;
		ans.push_back(n_trie.add_n(s));
	}
	for (auto& iter : ans) cout << iter << '\n';
}
