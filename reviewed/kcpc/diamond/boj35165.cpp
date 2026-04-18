#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 998244353
using namespace std;
 
struct SAMNode {
    int len, slink;
    map<char, int> edge;
};
 
struct Info {
    double rval;
    int cnt;
};
 
SAMNode g[200001];
int sz, last;
string S, T;
Info dp1[100001], dp2[100001];
int L[100001];
double eps = 1e-9;

void upt(char c) {
    int tmp = sz++;
    g[tmp].len = g[last].len + 1;
    int p = last;
    while (p != -1 && !g[p].edge.count(c)) {
        g[p].edge[c] = tmp;
        p = g[p].slink;
    }
    if (p == -1) g[tmp].slink = 0;
    else {
        int q = g[p].edge[c];
        if (g[q].len == g[p].len + 1) g[tmp].slink = q;
        else {
            int cl = sz++;
            g[cl].len = g[p].len + 1;
            g[cl].slink = g[q].slink;
            g[cl].edge = g[q].edge;
            while (p != -1 && g[p].edge[c] == q) {
                g[p].edge[c] = cl;
                p = g[p].slink;
            }
            g[q].slink = g[tmp].slink = cl;
        }
    }
    last = tmp;
}
 
void make_L(int node, int Tind, int ind) {
    if (Tind == (int)T.size()) {
        for (int i = ind; i <= (int)T.size(); i++) L[i] = (int)T.size();
        return;
    }
    if (g[node].edge.count(T[Tind])) make_L(g[node].edge[T[Tind]], Tind + 1, ind);
    else {
        int tmp = Tind + 1 - ind;
        while (tmp > g[g[node].slink].len) {
            L[ind++] = Tind;
            tmp--;
        }
        make_L(g[node].slink, Tind, ind);
    }
}

double inf = 1e9;
 
struct Line{
    int ind;
	double dpval;
	double get(int x){
		return (x > ind ? log(x - ind) + dpval : -inf);
	}
};
 
struct Node{
	int l, r;
	int s, e;
	Line line;
};
 
struct Li_Chao{
	vector<Node> tree;
 
	void init(int s, int e){
		tree.push_back({-1, -1, s, e, {100001, -inf}});
	}
 
	void update(int node, Line v){
		int s = tree[node].s, e = tree[node].e;
		int m = (s + e) >> 1;
 
		Line low = tree[node].line, high = v;
		if (low.get(s) > high.get(s)) swap(low, high);
 
		if (low.get(e) <= high.get(e)){
			tree[node].line = high; return;
		}
 
		if (low.get(m) < high.get(m)){
			tree[node].line = high;
			if (tree[node].r == -1){
				tree[node].r = (int)tree.size();
				tree.push_back({ -1, -1, m + 1, e, { 100001, -inf } });
			}
			update(tree[node].r, low);
		}
		else{
			tree[node].line = low;
			if (tree[node].l == -1){
				tree[node].l = (int)tree.size();
				tree.push_back({ -1, -1, s, m, { 100001, -inf } });
			}
			update(tree[node].l, high);
		}
	}
 
	Line query(int node, int x){
		if (node == -1) return tree[0].line;
		int s = tree[node].s, e = tree[node].e;
		int m = (s + e) >> 1;
		if (x <= m) {
		    Line tmp = query(tree[node].l, x);
		    if (tree[node].line.get(x) < tmp.get(x)) return tmp;
		    else return tree[node].line;
		}
		else {
		    Line tmp = query(tree[node].r, x);
		    if (tree[node].line.get(x) < tmp.get(x)) return tmp;
		    else return tree[node].line;
		}
	}
};
 
Li_Chao lctree[331];
 
int cntcnt[100001];
 
void init() {
    for (int i = 1; i <= 330; i++) lctree[i].init(1, (int)T.size());
}
 
int query1(int le, int ri, int ind) {
    if (le > ri) return ind - 1;
    int i, res = le;
    Line rline = {le,dp1[le].rval};
    double rval = rline.get(ind);
    if ((le - 1) / 330 == (ri - 1) / 330) {
        for (i = le; i <= ri; i++) {
            Line tmp = {i,dp1[i].rval};
            if (rval < tmp.get(ind)) {
                res = i;
                rval = tmp.get(ind);
            }
        }
    }
    else {
        for (i = le; i <= (le - 1) / 330 * 330 + 330; i++) {
            Line tmp = {i,dp1[i].rval};
            if (rval < tmp.get(ind)) {
                res = i;
                rval = tmp.get(ind);
            }
        }
        for (i = (le - 1) / 330 + 2; i <= (ri - 1) / 330; i++) {
            Line tmp = lctree[i].query(0, ind);
            if (rval < tmp.get(ind)) {
                res = tmp.ind;
                rval = tmp.get(ind);
            }
        }
        for (i = (ri - 1) / 330 * 330 + 1; i <= ri; i++) {
            Line tmp = {i,dp1[i].rval};
            if (rval < tmp.get(ind)) {
                res = i;
                rval = tmp.get(ind);
            }
        }
    }
    return res;
}
 
void query2(int ind, double val) {
    lctree[(ind - 1) / 330 + 1].update(0,{ind,val});
}
 
void solve() {
    int i, j; cin >> S >> T;
    g[0].len = 0;
    g[0].slink = -1;
    sz++;
    for (auto& iter : S) upt(iter);
    make_L(0, 0, 1);
    //p1, n1
    init();
    dp1[1].rval = 0;
    dp1[1].cnt = 1;
    cntcnt[1] = 1;
    query2(1, dp1[1].rval);
    int tmp = 1;
    for (i = 2; i <= (int)T.size(); i++) {
        while (L[tmp] < i) tmp++;
        
        int qle = tmp - 1, qri = i - 1;
        if (tmp <= i && cntcnt[dp1[tmp - 1].cnt + 1]) qri = cntcnt[dp1[tmp - 1].cnt + 1] - 1;
        int ind = query1(qle, qri, i);
        
        dp1[i].rval = dp1[ind].rval + log(i - ind);
        dp1[i].cnt = dp1[ind].cnt + 1;
        
        if (!cntcnt[dp1[i].cnt] && dp1[i].cnt > dp1[i - 1].cnt) cntcnt[dp1[i].cnt] = i;
        
        query2(i, dp1[i].rval);
    }
    cout << fixed << setprecision(10);
    cout << dp1[T.size()].cnt << ' ' << dp1[T.size()].rval << '\n';
    
    //p2, n2
    dp2[1].rval = 0;
    dp2[1].cnt = 1;
    for (i = 2; i <= (int)T.size(); i++) {
        double temp = dp2[i - 1].rval;
        int tempcnt = dp2[i - 1].cnt + 1;
        for (j = i - 1; j >= max(1, i - 3); j--) {
            if (L[j] < i) break;
            if (temp < dp2[j - 1].rval + log(i - j + 1) + eps) {
                temp = dp2[j - 1].rval + log(i - j + 1);
                tempcnt = dp2[j - 1].cnt + 1;
            }
            else if (abs(temp - dp2[j - 1].rval - log(i - j + 1)) < eps) tempcnt = min(tempcnt, dp2[j - 1].cnt + 1);
        }
        dp2[i].rval = temp;
        dp2[i].cnt = tempcnt;
    }
    cout << dp2[T.size()].rval << ' ' << dp2[T.size()].cnt << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
