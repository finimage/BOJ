#include<iostream>
#include<queue>
using namespace std;

struct info{
    int v, x, y;
};

struct cmp {
    bool operator()(const info& a, const info& b) {
        return a.v > b.v;
    }
};

int n, m, i_cnt = 0, arr[10][10], check[10][10], dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 }, dist[7][7], parent[7];
info isl[7];
bool visited[10][10];
priority_queue<info, vector<info>, cmp> pq;

void init() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) visited[i][j] = 0;
    }
}

void i_bfs(int a, int b) {
    int i, x, y;
    i_cnt++;
    visited[a][b] = 1;
    check[a][b] = i_cnt;
    queue<pair<int, int>> q;
    q.push({ a,b });
    while (!q.empty()) {
        a = q.front().first;
        b = q.front().second;
        q.pop();
        for (i = 0; i < 4; i++) {
            x = a + dx[i];
            y = b + dy[i];
            if (0 <= x && x < n && 0 <= y && y < m) {
                if (visited[x][y] || !arr[x][y]) continue;
                visited[x][y] = 1;
                check[x][y] = i_cnt;
                q.push({ x,y });
            }
        }
    }
}

void w_bfs(int v, int a, int b) {
    int i, x, y, k, temp;
    visited[a][b] = 1;
    queue<info> q;
    q.push({ 0,a,b });
    while (!q.empty()) {
        k = q.front().v;
        a = q.front().x;
        b = q.front().y;
        q.pop();
        for (i = 0; i < 4; i++) {
            x = a + dx[i];
            y = b + dy[i];
            temp = k;
            while (0 <= x && x < n && 0 <= y && y < m) {
                if (!visited[x][y] && check[x][y] == v) {
                    visited[x][y] = 1;
                    q.push({ 0,x,y });
                    break;
                }
                if (check[x][y] == v) break;
                if (check[x][y] > v) {
                    if (temp > 1) dist[v][check[x][y]] = min(dist[v][check[x][y]], temp);
                    //cout << x << ' ' << y << ' ' << a << ' ' << b << "  " << temp << '\n';
                    break;
                }
                if (check[x][y] != 0) break;
                temp++;
                x += dx[i];
                y += dy[i];
            }
        }
    }
    init();
}

int find(int a) {
    if (parent[a] == a) return a;
    return parent[a] = find(parent[a]);
}

bool comp(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 1;
    return 0;
}

void union_(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[a] = b;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int x, y, v, i, j, ans = 0, cnt = 0; cin >> n >> m;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) cin >> arr[i][j];
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (arr[i][j] == 1 && !visited[i][j]) {
                i_bfs(i, j);
                isl[i_cnt] = { i_cnt,i,j };
            }
        }
    }
    init();
    for (i = 1; i <= i_cnt; i++) {
        for (j = i + 1; j <= i_cnt; j++) dist[i][j] = 9;
    }
    for (i = 1; i < i_cnt; i++) w_bfs(isl[i].v, isl[i].x, isl[i].y);
    for (i = 1; i <= i_cnt; i++) {
        for (j = i + 1; j <= i_cnt; j++) {
            if (dist[i][j] < 9) pq.push({ dist[i][j],i,j });
        }
    }
    for (i = 1; i <= i_cnt; i++) parent[i] = i;
    while (!pq.empty()) {
        x = pq.top().x;
        y = pq.top().y;
        v = pq.top().v;
        pq.pop();
        if (comp(x, y)) continue;
        cnt++;
        union_(x, y);
        ans += v;
    }
    if (cnt == i_cnt - 1) cout << ans;
    else cout << -1;
}
