#include<iostream>
#include<queue>
using namespace std;

struct info {
	int r[2], b[2], dir, count;
};

queue<info> q;
int n, m, dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
char arr[10][10];
bool visited[10][10][10][10];


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int i, j, rx, ry, bx, by;
	bool rtf, btf, tf = false, O[2];
	info init;
	init.dir = -1;
	init.count = 0;
	cin >> n >> m;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 'R') {
				init.r[0] = i;
				init.r[1] = j;
				arr[i][j] = '.';
			}
			else if (arr[i][j] == 'B') {
				init.b[0] = i;
				init.b[1] = j;
				arr[i][j] = '.';
			}
		}
	}
	q.push(init);
	while (!q.empty()) {
		init.r[0] = q.front().r[0];
		init.r[1] = q.front().r[1];
		init.b[0] = q.front().b[0];
		init.b[1] = q.front().b[1];
		init.dir = q.front().dir;
		init.count = q.front().count;
		q.pop();
		for (i = 0; i < 4; i++) {
			if (init.dir == i) continue;
			rx = init.r[0] + dx[i];
			ry = init.r[1] + dy[i];
			bx = init.b[0] + dx[i];
			by = init.b[1] + dy[i];
			if (((rx == init.b[0] && ry == init.b[1]) || arr[rx][ry] == '#') && ((bx == init.r[0] && by == init.r[1]) || arr[bx][by] == '#')) continue;
			rx -= dx[i];
			ry -= dy[i];
			bx -= dx[i];
			by -= dy[i];
			rtf = false;
			btf = false;
			O[0] = false;
			O[1] = false;
			while (1) {
				if (arr[rx][ry] != '#' && !(rx == bx && ry == by) && !rtf) {
					rx += dx[i];
					ry += dy[i];
					if (arr[rx][ry] == 'O') {
						O[0] = true;
						rtf = true;
					}
					else if (arr[rx][ry] == '#') {
						rx -= dx[i];
						ry -= dy[i];
						rtf = true;
					}
					else if (rx == bx && ry == by) {
						if (btf) rtf = true;
						rx -= dx[i];
						ry -= dy[i];
					}
				}
				if (arr[bx][by] != '#' && !(rx == bx && ry == by) && !btf) {
					bx += dx[i];
					by += dy[i];
					if (arr[bx][by] == 'O') {
						O[1] = true;
						btf = true;
					}
					else if (arr[bx][by] == '#') {
						bx -= dx[i];
						by -= dy[i];
						btf = true;
					}
					else if (bx == rx && by == ry) {
						if (rtf) btf = true;
						bx -= dx[i];
						by -= dy[i];
					}
				}
				if (O[1]) break;
				else if (O[0] && btf) {
					tf = true;
					break;
				}
				else if (rtf && btf) break;
			}
			if (tf) break;
			if (O[1]) continue;
			if (visited[rx][ry][bx][by]) continue;
			q.push({ {rx,ry},{bx,by},(i + 2) % 4,init.count + 1 });
			visited[rx][ry][bx][by] = true;
		}
		if (tf) break;
	}
	if (tf) cout << init.count + 1;
	else cout << -1;
}
