#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

vector<string> num, num_;
string tem = "";

bool cmp1(const string& s1, const string& s2) {
    if (s1 + s2 == s2 + s1) return s1.size() < s2.size();
    return s1 + s2 < s2 + s1;
}

bool cmp2(const string& s1, const string& s2) {
    return s1 + tem + s2 < s2 + tem + s1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, i, l, tf = 1;
    string temp;
    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> temp;
        if (temp[0] == '0') num_.push_back(temp);
        else num.push_back(temp);
    }
    if (num.size() == 0) cout << "INVALID";
    else {
        sort(num_.begin(), num_.end(), cmp1);
        l = num_.size();
        for (i = 0; i < l; i++) tem += num_[i];
        sort(num.begin(), num.end(), cmp2);
        cout << num[0] << tem;
        temp = num[0];
        sort(num.begin(), num.end(), cmp1);
        l = num.size();
        for (i = 0; i < l; i++) {
            if (num[i] == temp && tf) {
                tf = 0;
                continue;
            }
            cout << num[i];
        }
    }
}
