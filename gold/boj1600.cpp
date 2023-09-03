#include<iostream>
#include<queue>
using namespace std;

struct info {
	int x, y, cnt, count;
};

queue<info> q;
int arr[201][201], dx[12] = { 1,0,0,-1,2,2,-2,-2,1,1,-1,-1 }, dy[12] = { 0,1,-1,0,1,-1,1,-1,2,-2,2,-2 };
bool visited[201][201][31];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int K, W, H, i, j, a, b, cnt, count, x, y, ans = -1; cin >> K >> W >> H;
	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++) cin >> arr[i][j];
	}
	q.push({ 0,0,K });
	visited[0][0][K] = 1;
	while (!q.empty()) {
		a = q.front().x;
		b = q.front().y;
		cnt = q.front().cnt;
		count = q.front().count;
		q.pop();
		if (a == H - 1 && b == W - 1) {
			ans = count;
			break;
		}
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < H && 0 <= y && y < W) {
				if (visited[x][y][cnt]) continue;
				if (arr[x][y] == 1) continue;
				visited[x][y][cnt] = 1;
				q.push({ x,y,cnt,count + 1 });
			}
		}
		if (!cnt) continue;
		for (i = 4; i < 12; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < H && 0 <= y && y < W) {
				if (visited[x][y][cnt - 1]) continue;
				if (arr[x][y] == 1) continue;
				visited[x][y][cnt - 1] = 1;
				q.push({ x,y,cnt - 1,count + 1 });
			}
		}
	}
	cout << ans;
}
