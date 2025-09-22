#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
#define int ll
#define FOR(i,a,b) for (ll i = (a); i < (b); i++) 
#define ROF(i,a,b) for (ll i = (a); i >= (b); i--)
#define FORIT(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)

const ll n = 50, m = 2*n;
char og_wh[n][n];

char wh[n][m];
struct pos { ll i,j; } cpos;
pos get_robot_pos() {
	FOR(i,0,n) FOR(j,0,n) if (wh[i][j] == '@') {
		return {i,j};
	}
	return {-1,-1}; // unreachable
}
bool check_if_box_movable(pos bp, char d) {
	char obj = wh[bp.i][bp.j];
	//cout << d;
	bool movable = true;
	switch (obj) {
	case '#': return false;
	case '[': case ']':
		pos rnbp[2];
		switch (d) {
		case '^': rnbp[0] = {-1,0}, rnbp[1] = {-1,(obj==']'?-1:1)}; break;
		case '>': rnbp[0] = (rnbp[1] = {0,1}); break;
		case 'v': rnbp[0] = {1,0}, rnbp[1] = {1,(obj==']'?-1:1)}; break;
		case '<': rnbp[0] = (rnbp[1] = {0,-1}); break;
		}

		FOR(i,0,2) movable &= check_if_box_movable({bp.i+rnbp[i].i,bp.j+rnbp[i].j}, d);

		return movable;
	case '.': return true;
	default: cout << "ERROR" << endl; exit(1); return false;
	}
}
void move_box(pos bp, char d) {
	char obj = wh[bp.i][bp.j];
	if (obj != '[' && obj != ']') return;

	ll t = 2;
	pos rnbp[2];
	switch (d) {
	case '^': rnbp[0] = {-1,0}, rnbp[1] = {-1,(obj==']'?-1:1)}; break;
	case '>': rnbp[0] = (rnbp[1] = {0,1}); t = 1; break;
	case 'v': rnbp[0] = {1,0}, rnbp[1] = {1,(obj==']'?-1:1)}; break;
	case '<': rnbp[0] = (rnbp[1] = {0,-1}); t = 1; break;
	default: cout << "ERR" << endl; exit(1); break;
	}
	pos nbp[2] = {{bp.i+rnbp[0].i,bp.j+rnbp[0].j},{bp.i+rnbp[1].i,bp.j+rnbp[1].j}};
	FOR(i,0,t) {
		move_box(nbp[i], d);
	}
	
	char box[2] = {'[',']'};
	int perm[2];
	switch (d) {
	case '^':
	case 'v':
		wh[nbp[0].i][nbp[0].j] = obj;
		wh[nbp[1].i][nbp[1].j] = obj == '[' ? ']' : '[';
		wh[nbp[1].i-rnbp[0].i][nbp[1].j-rnbp[0].j] = '.'; 
		break;
	case '>':
	case '<':
		wh[nbp[0].i][nbp[0].j] = obj;
		break;
	default: cout << "ERR2" << endl; exit(1); break;
	}
}
void move_robot(char d) {
	pos npos;
	switch (d) {
		case '^': npos = {cpos.i-1,cpos.j}; break;
		case '>': npos = {cpos.i,cpos.j+1}; break;
		case 'v': npos = {cpos.i+1,cpos.j}; break;
		case '<': npos = {cpos.i,cpos.j-1}; break;
	}
	switch (wh[npos.i][npos.j]) {
	case '.': break;
	case '#': return;
	case '[':
	case ']':
		//cout << "BOX MOVING" << endl;
		if (!check_if_box_movable(npos, d)) return;
		//cout << "HELLO!!!" << endl;
		move_box(npos, d);
		//cout << "MOVED" << endl;
		break;
	}
	wh[npos.i][npos.j] = '@';
	wh[cpos.i][cpos.j] = '.';
	cpos = npos;
}
ll gpsSum() {
	ll sum = 0;
	FOR(i,0,n) FOR(j,0,m) if (wh[i][j] == '[') {
		sum += 100 * i + j;
	}
	return sum;
}
void widen_map() {
	FOR(i,0,n) FOR(j,0,n) {
		switch (og_wh[i][j]) {
		case '#':
			wh[i][2*j+0] = '#';
			wh[i][2*j+1] = '#';
			break;
		case 'O':
			wh[i][2*j+0] = '[';
			wh[i][2*j+1] = ']';
			break;
		case '.':
			wh[i][2*j+0] = '.';
			wh[i][2*j+1] = '.';
			break;
		case '@':
			wh[i][2*j+0] = '@';
			wh[i][2*j+1] = '.';
			break;
		}
	}
}
void print_map() {
	if(true)return;
	FOR(i,0,n) {
		FOR(j,0,m) cout << wh[i][j];
		cout << endl;
	}
}

void main() {
	FOR(i,0,n) {
		string row;
		cin >> row;
		FOR(j,0,n) og_wh[i][j] = row[j];
	}
	vector<char> mv(20000);
	FOR(i,0,20000) cin >> mv[i];
	
	widen_map();
	//print_map();
	
	cpos = get_robot_pos();
	FORIT(it,mv) move_robot(*it), print_map();
	
	cout << gpsSum();
}