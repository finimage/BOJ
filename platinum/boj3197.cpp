#include<iostream>
#include<queue>
using namespace std;

int n, m, swan_co[2] = { 0, }, dx[4] = { 0,1,0,-1 }, dy[4] = { 1,0,-1,0 };
char swan[1501][1501] = { 0, };
bool swan_check[1501][1501] = { 0, }, tf = false;
queue<pair<int, int>> sq[2], wq[2];

void swan_bfs(int k1, int k2) {
	int x, y, a, b, i;
	while (!(sq[k1].empty()) && !tf) {
		a = sq[k1].front().first;
		b = sq[k1].front().second;
		sq[k1].pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < m) {
				if (swan[x][y] == '.' && !swan_check[x][y]) sq[k1].push({ x,y });
				if (swan[x][y] == 'L' && !swan_check[x][y]) {
					tf = true;
					break;
				}
				if (swan[x][y] == 'X' && !swan_check[x][y]) sq[k2].push({ x,y });
				swan_check[x][y] = true;
			}
		}
	}
}

void water_bfs(int k1, int k2) {
	int x, y, a, b, i;
	while (!(wq[k1].empty())) {
		a = wq[k1].front().first;
		b = wq[k1].front().second;
		wq[k1].pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < m) {
				if (swan[x][y] == 'X') {
					swan[x][y] = '.';
					wq[k2].push({ x,y });
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int i, j, time = 0, k1, k2;
	cin >> n >> m;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			cin >> swan[i][j];
			if (swan[i][j] == '.') wq[0].push({ i,j });
			else if (swan[i][j] == 'L') {
				swan_co[0] = i;
				swan_co[1] = j;
				wq[0].push({ i,j });
			}
		}
	}
	sq[0].push({ swan_co[0], swan_co[1] });
	swan_check[swan_co[0]][swan_co[1]] = true;
	while (!tf) {
		k1 = time % 2;
		k2 = (time + 1) % 2;
		swan_bfs(k1,k2);
		if (!tf) {
			water_bfs(k1,k2);
			time++;
		}
	}
	cout << time;
}
