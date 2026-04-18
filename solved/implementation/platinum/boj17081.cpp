#include<iostream>
using namespace std;

struct Monster {
	string name;
	int W, A, H, E;
};

struct Item {
	char T;
	int N;
	string S;
};

struct State {
	int x, y;
	int LV, HP[2], ATT[2], DEF[2], EXP[2];
	int item_cnt;
	bool HR, RE, CO, EX, DX, HU, CU;
};

string order;
int N, M;
bool Boss = true;
char greed[101][101];
Monster M_info[101][101];
Item I_info[101][101];
State Character = { 0,0,1,20,20,2,0,2,0,0,5,0,0,0,0,0,0,0,0 };

void ans() {
	int turn = 0, x = Character.x, y = Character.y, start[2] = { Character.x,Character.y };
	for (auto iter = order.begin(); iter != order.end(); iter++) {
		turn++;
		switch (*iter) {
		case 'U':
			x--;
			break;
		case 'D':
			x++;
			break;
		case 'R':
			y++;
			break;
		case 'L':
			y--;
			break;
		}
		if (x == N) x--;
		if (x < 0) x++;
		if (y == M) y--;
		if (y < 0) y++;
		if (greed[x][y] == '#') {
			x = Character.x;
			y = Character.y;
		}
		if (greed[x][y] == '^') {
			Character.HP[0] -= 5;
			if (Character.DX) Character.HP[0] += 4;
		}
		else if (greed[x][y] == '&') {
			int at = max(1, (Character.ATT[0] + Character.ATT[1]) * (1 + ((Character.CO) ? 1 : 0) + ((Character.CO && Character.DX) ? 1 : 0)) - M_info[x][y].A);
			if (at >= M_info[x][y].H) {
				Character.EXP[0] += (int)((float)((Character.EX) ? 1.2 : 1) * M_info[x][y].E);
				if (Character.EXP[0] >= Character.EXP[1]) {
					Character.LV++;
					Character.EXP[1] += 5;
					Character.EXP[0] = 0;
					Character.HP[1] += 5;
					Character.HP[0] = Character.HP[1];
					Character.ATT[0] += 2;
					Character.DEF[0] += 2;
				}
				if (Character.HR) Character.HP[0] = min(Character.HP[0] + 3, Character.HP[1]);
				greed[x][y] = '.';
			}
			else {
				M_info[x][y].H -= at;
				int de = max(1, M_info[x][y].W - Character.DEF[0] - Character.DEF[1]);
				at = max(1, Character.ATT[0] + Character.ATT[1] - M_info[x][y].A);
				int l1 = Character.HP[0] / de + ((Character.HP[0] % de == 0) ? 0 : 1);
				int l2 = M_info[x][y].H / at + ((M_info[x][y].H % at == 0) ? 0 : 1);
				if (l1 <= l2) {
					at = max(1, (Character.ATT[0] + Character.ATT[1]) * (1 + ((Character.CO) ? 1 : 0) + ((Character.CO && Character.DX) ? 1 : 0)) - M_info[x][y].A);
					Character.HP[0] = 0;
					M_info[x][y].H += at;
				}
				else {
					Character.HP[0] -= l2 * de;
					Character.EXP[0] += (int)((float)((Character.EX) ? 1.2 : 1) * M_info[x][y].E);
					if (Character.EXP[0] >= Character.EXP[1]) {
						Character.LV++;
						Character.EXP[1] += 5;
						Character.EXP[0] = 0;
						Character.HP[1] += 5;
						Character.HP[0] = Character.HP[1];
						Character.ATT[0] += 2;
						Character.DEF[0] += 2;
					}
					if (Character.HR) Character.HP[0] = min(Character.HP[0] + 3, Character.HP[1]);
					greed[x][y] = '.';
				}
			}
		}
		else if (greed[x][y] == 'M') {
			if (Character.HU) {
				Character.HP[0] = Character.HP[1];
			}
			int at = max(1, (Character.ATT[0] + Character.ATT[1]) * (1 + ((Character.CO) ? 1 : 0) + ((Character.CO && Character.DX) ? 1 : 0)) - M_info[x][y].A);
			if (at >= M_info[x][y].H) {
				Character.EXP[0] += (int)((float)((Character.EX) ? 1.2 : 1) * M_info[x][y].E);
				if (Character.EXP[0] >= Character.EXP[1]) {
					Character.LV++;
					Character.EXP[1] += 5;
					Character.EXP[0] = 0;
					Character.HP[1] += 5;
					Character.HP[0] = Character.HP[1];
					Character.ATT[0] += 2;
					Character.DEF[0] += 2;
				}
				if (Character.HR) Character.HP[0] = min(Character.HP[0] + 3, Character.HP[1]);
				greed[x][y] = '.';
				Boss = 0;
			}
			else {
				M_info[x][y].H -= at;
				int de = max(1, M_info[x][y].W - Character.DEF[0] - Character.DEF[1]);
				at = max(1, Character.ATT[0] + Character.ATT[1] - M_info[x][y].A);
				if (Character.HU) {
					Character.HP[0] += de;
				}
				int l1 = Character.HP[0] / de + ((Character.HP[0] % de == 0) ? 0 : 1);
				int l2 = M_info[x][y].H / at + ((M_info[x][y].H % at == 0) ? 0 : 1);
				if (l1 <= l2) {
					at = max(1, (Character.ATT[0] + Character.ATT[1]) * (1 + ((Character.CO) ? 1 : 0) + ((Character.CO && Character.DX) ? 1 : 0)) - M_info[x][y].A);
					Character.HP[0] = 0;
					M_info[x][y].H += at;
				}
				else {
					Character.HP[0] -= l2 * de;
					Character.EXP[0] += (int)((float)((Character.EX) ? 1.2 : 1) * M_info[x][y].E);
					if (Character.EXP[0] >= Character.EXP[1]) {
						Character.LV++;
						Character.EXP[1] += 5;
						Character.EXP[0] = 0;
						Character.HP[1] += 5;
						Character.HP[0] = Character.HP[1];
						Character.ATT[0] += 2;
						Character.DEF[0] += 2;
					}
					if (Character.HR) Character.HP[0] = min(Character.HP[0] + 3, Character.HP[1]);
					greed[x][y] = '.';
					Boss = 0;
				}
			}
		}
		else if (greed[x][y] == 'B') {
			if (I_info[x][y].T == 'O') {
				if (Character.item_cnt < 4) {
					if (I_info[x][y].S == "HR" && !Character.HR) {
						Character.item_cnt++;
						Character.HR = 1;
					}
					else if (I_info[x][y].S == "RE" && !Character.RE) {
						Character.item_cnt++;
						Character.RE = 1;
					}
					else if (I_info[x][y].S == "CO" && !Character.CO) {
						Character.item_cnt++;
						Character.CO = 1;
					}
					else if (I_info[x][y].S == "EX" && !Character.EX) {
						Character.item_cnt++;
						Character.EX = 1;
					}
					else if (I_info[x][y].S == "DX" && !Character.DX) {
						Character.item_cnt++;
						Character.DX = 1;
					}
					else if (I_info[x][y].S == "HU" && !Character.HU) {
						Character.item_cnt++;
						Character.HU = 1;
					}
					else if (I_info[x][y].S == "CU" && !Character.CU) {
						Character.item_cnt++;
						Character.CU = 1;
					}
				}
			}
			else if (I_info[x][y].T == 'W') {
				Character.ATT[1] = I_info[x][y].N;
			}
			else if (I_info[x][y].T == 'A') {
				Character.DEF[1] = I_info[x][y].N;
			}
			greed[x][y] = '.';
		}
		Character.x = x;
		Character.y = y;
		if (Character.HP[0] <= 0 && Character.RE) {
			Character.RE = 0;
			Character.item_cnt--;
			Character.HP[0] = Character.HP[1];
			Character.x = start[0];
			x = start[0];
			Character.y = start[1];
			y = start[1];
		}
		else if (Character.HP[0] <= 0) {
			break;
		}
		else if (!Boss) {
			break;
		}
	}
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			if (i == Character.x && j == Character.y && Character.HP[0] > 0) {
				cout << '@';
				continue;
			}
			cout << greed[i][j];
		}
		cout << '\n';
	}
	cout << "Passed Turns : " << turn << '\n';
	cout << "LV : " << Character.LV << '\n';
	cout << "HP : " << Character.HP[0] << '/' << Character.HP[1] << '\n';
	cout << "ATT : " << Character.ATT[0] << '+' << Character.ATT[1] << '\n';
	cout << "DEF : " << Character.DEF[0] << '+' << Character.DEF[1] << '\n';
	cout << "EXP : " << Character.EXP[0] << '/' << Character.EXP[1] << '\n';
	if (Character.HP[0] <= 0) {
		if (greed[x][y] == '^') cout << "YOU HAVE BEEN KILLED BY SPIKE TRAP..";
		else cout << "YOU HAVE BEEN KILLED BY " << M_info[x][y].name << "..";
	}
	else {
		if (Boss) cout << "Press any key to continue.";
		else cout << "YOU WIN!";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int i, j, M_cnt = 0, I_cnt = 0, x, y;
	cin >> N >> M;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			cin >> greed[i][j];
			if (greed[i][j] == '&' || greed[i][j] == 'M') M_cnt++;
			else if (greed[i][j] == 'B') I_cnt++;
			else if (greed[i][j] == '@') {
				Character.x = i;
				Character.y = j;
				greed[i][j] = '.';
			}
		}
	}
	cin >> order;
	for (i = 0; i < M_cnt; i++) {
		cin >> x >> y;
		x--;
		y--;
		cin >> M_info[x][y].name >> M_info[x][y].W >> M_info[x][y].A >> M_info[x][y].H >> M_info[x][y].E;
	}
	for (i = 0; i < I_cnt; i++) {
		cin >> x >> y;
		x--;
		y--;
		cin >> I_info[x][y].T;
		if (I_info[x][y].T == 'O') cin >> I_info[x][y].S;
		else cin >> I_info[x][y].N;
	}
	ans();
}
