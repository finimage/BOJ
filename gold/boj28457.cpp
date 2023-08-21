#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct key {
	int i, x;
};

struct info {
	string name;
	int price;
};

struct state {
	int place, money;
};

state State;
vector<info> board;
vector<bool> check;
int n, W, G, dice, D_I_cnt, tf;
queue<key> Key;
queue<pair<int, int>> Dice;

void input() {
	int i, a, b; cin >> n >> State.money >> W >> G;
	for (i = 0; i < G; i++) {
		cin >> a >> b;
		Key.push({ a,b });
	}
	board = vector<info>(4 * n - 4);
	check = vector<bool>(4 * n - 4);
	for (i = 0; i < 4 * n - 4; i++) {
		if (i == 0) board[i].name = "Start";
		else if (i == n - 1) board[i].name = "D_Island";
		else if (i == 2 * n - 2) board[i].name = "Welfare";
		else if (i == 3 * n - 3) board[i].name = "Space";
		else {
			cin >> board[i].name;
			if (board[i].name == "L") cin >> board[i].price;
		}
	}
	cin >> dice;
	for (i = 0; i < dice; i++) {
		cin >> a >> b;
		Dice.push({ a,b });
	}
}

void shift(int cnt) {//이동 자체를 담은 칸
	//시작 지나는가 고려
	//직접 지나가면 됨
	while (cnt--) {
		State.place++;
		State.place %= 4 * n - 4;
		if (State.place == 0) State.money += W;
	}
}

void solve() {
	while (!Dice.empty()) {
		pair<int, int> temp = Dice.front();
		Dice.pop();
		if (board[State.place].name == "D_Island") {
			//나갈 수 있는지 없는지에 따라
			if (D_I_cnt == 3) D_I_cnt = 0;
			else if (temp.first == temp.second) {
				D_I_cnt = 3;
				continue;
			}
			else {
				D_I_cnt++;
				continue;
			}
		}
		//이동
		shift(temp.first + temp.second);
		if (board[State.place].name == "Welfare") {
			State.money += board[State.place].price;
			board[State.place].price = 0;
		}
		else if (board[State.place].name == "Space") {
			shift(n - 1);
		}
		else if (board[State.place].name == "G") {
			key key_ = Key.front();
			Key.push(key_);
			Key.pop();
			if (key_.i == 1) State.money += key_.x;
			else if (key_.i == 2) {
				if (key_.x > State.money) {
					tf = 1;
					return;
				}
				State.money -= key_.x;
			}
			else if (key_.i == 3) {
				if (key_.x > State.money) {
					tf = 1;
					return;
				}
				State.money -= key_.x;
				board[2 * n - 2].price += key_.x;
			}
			else {
				shift(key_.x);
				if (board[State.place].name == "Welfare") {
					State.money += board[State.place].price;
					board[State.place].price = 0;
				}
				else if (board[State.place].name == "Space") {
					shift(n - 1);
				}
				else if (board[State.place].name == "L") {
					//check로 확인
					if (check[State.place]) continue;
					if (board[State.place].price > State.money) continue;
					else {
						State.money -= board[State.place].price;
						check[State.place] = 1;
					}
				}

			}
		}
		else if (board[State.place].name == "L") {
			//check로 확인
			if (check[State.place]) continue;
			if (board[State.place].price > State.money) continue;
			else {
				State.money -= board[State.place].price;
				check[State.place] = 1;
			}
		}
	}
}

string ans() {
	for (int i = 0; i < 4 * n - 4; i++) {
		if (board[i].name == "L") {
			if (check[i]) continue;
			else return "LOSE";
		}
	}
	return "WIN";
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	solve();
	if (tf) {
		cout << "LOSE";
		return 0;
	}
	cout << ans();
}
