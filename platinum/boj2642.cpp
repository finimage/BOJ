#include<iostream>
#include<queue>
using namespace std;

int arr[7][7], x[7], y[7], check[7], row[6], col[6];
int a, b, na, nb, visited[7] = { 0,1,0, }, visited_n[7], dx[4] = {1,0,0,-1}, dy[4] = {0,1,-1,0};
string row_check = "", col_check = "";

void init() {
    for (int i = 0; i < 7; i++) visited_n[i] = 0;
}

void solve(int index, int x, int y, int change, int cnt, int dir) {
    if (cnt > 1 && (change == 0 || change == 2)) check[index] = arr[x][y];
    if (check[index] > 0) return;
    visited_n[arr[x][y]] = 1;
    int i;
    for (i = 0; i < 4; i++) {
        na = x + dx[i];
        nb = y + dy[i];
        if (0 <= na && na < 6 && 0 <= nb && nb < 6) {
            if (arr[na][nb] == 0) continue;
            if (visited_n[arr[na][nb]]) continue;
            solve(index, na, nb, change + ((dir != i) ? 1 : 0), cnt + 1, i);
        }
    }
}

queue<pair<int, int>> q;

void bfs() {
    int i;
    q.push({ x[1],y[1] });
    while (!q.empty()) {
        a = q.front().first;
        b = q.front().second;
        q.pop();
        for (i = 0; i < 4; i++) {
            na = a + dx[i];
            nb = b + dy[i];
            if (0 <= na && na < 6 && 0 <= nb && nb < 6) {
                if (visited[arr[na][nb]]) continue;
                if (arr[na][nb] == 0) continue;
                q.push({ na,nb });
                visited[arr[na][nb]] = 1;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, tf = 0, row_case = 0, col_case = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            cin >> arr[i][j];
            if (arr[i][j] > 0) {
                x[arr[i][j]] = i;
                y[arr[i][j]] = j;
                row[i]++;
                col[j]++;
            }
        }
    }
    bfs();
    for (i = 1; i <= 6; i++) {
        if (visited[i] == 0) tf = 1;
    }
    if (tf) {
        cout << 0;
        return 0;
    }
    tf = 0;
    for (i = 0; i < 6; i++) {
        if (!tf && row[i] > 0) tf = 1;
        if (tf && row[i] > 0) row_check += (char)(row[i] + '0');
        if (tf && row[i] == 0) break;
    }
    if (row_check == "141") row_case = 1;
    else if (row_check == "33") row_case = 4;
    else if (row_check == "11211") row_case = 5;
    else if (row_check == "222") row_case = 6;
    else if (row_check == "231" || row_check == "132") row_case = 7;
    else {
        int cnt[4] = { 0, };
        for (auto iter = row_check.begin(); iter != row_check.end(); iter++) cnt[*iter - '0']++;
        if (cnt[1] == 3 && cnt[2] == 0 && cnt[3] == 1) row_case = 2;
        else if (cnt[1] == 2 && cnt[2] == 2 && cnt[3] == 0) row_case = 3;
        else row_case = 0;
    }
    tf = 0;
    for (i = 0; i < 6; i++) {
        if (!tf && col[i] > 0) tf = 1;
        if (tf && col[i] > 0) col_check += (char)(col[i] + '0');
        if (tf && col[i] == 0) break;
    }
    if (col_check == "141") col_case = 1;
    else if (col_check == "33") col_case = 4;
    else if (col_check == "11211") col_case = 5;
    else if (col_check == "222") col_case = 6;
    else if (col_check == "231" || col_check == "132") col_case = 7;
    else {
        int cnt[4] = { 0, };
        for (auto iter = col_check.begin(); iter != col_check.end(); iter++) cnt[*iter - '0']++;
        if (cnt[1] == 3 && cnt[2] == 0 && cnt[3] == 1) col_case = 2;
        else if (cnt[1] == 2 && cnt[2] == 2 && cnt[3] == 0) col_case = 3;
        else col_case = 0;
    }
    tf = 1;
    if ((row_case == 1 || row_case == 7) && (col_case == 2 || col_case == 3)) tf = 0;
    if ((col_case == 1 || col_case == 7) && (row_case == 2 || row_case == 3)) tf = 0;
    if (row_case == 4 && col_case == 5) tf = 0;
    if (row_case == 5 && col_case == 4) tf = 0;
    if (row_case == 3 && col_case == 6) tf = 0;
    if (row_case == 6 && col_case == 3) tf = 0;
    if (tf) {
        cout << 0;
        return 0;
    }
    tf = 1;
    for (i = 1; i <= 6; i++) {
        init();
        solve(i, x[i], y[i], -1, 0, 10);
        if (check[i] == 0) tf = 0;
    }
    if (tf) cout << check[1];
    else cout << 0;
}
