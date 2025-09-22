#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
#define int ll
#define FOR(i,a,b) for (ll i = (a); i < (b); i++) 
#define ROF(i,a,b) for (ll i = (a); i >= (b); i--)
#define FORIT(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)

const ll n = 50;
char wh[n][n];
const ll m = 20000;
char mv[m];

struct pos { ll i,j; } cpos;
pos get_robot_pos() {
	FOR(i,0,n) FOR(j,0,n) if (wh[i][j] == '@') {
		return {i,j};
	}
	return {-1,-1}; // unreachable
}
void move_robot(char d) {
	vector<pos> ahead;
	switch (d) {
		case '^': ROF(i,cpos.i-1,0) ahead.push_back({i,cpos.j}); break;
		case '>': FOR(j,cpos.j+1,n) ahead.push_back({cpos.i,j}); break;
		case 'v': FOR(i,cpos.i+1,n) ahead.push_back({i,cpos.j}); break;
		case '<': ROF(j,cpos.j-1,0) ahead.push_back({cpos.i,j}); break;
	}
	pos npos = ahead[0];
	switch (wh[npos.i][npos.j]) {
	case '.': break;
	case '#': return;
	case 'O':
		ll os = 1;
		while (wh[ahead[os].i][ahead[os].j] == 'O') os++;
		switch (wh[ahead[os].i][ahead[os].j]) {
		case '.':
			wh[ahead[os].i][ahead[os].j] = 'O';
			break;
		case '#': return;
		case 'O': return; // unreachable
		}
	}
	wh[npos.i][npos.j] = '@';
	wh[cpos.i][cpos.j] = '.';
	cpos = npos;
}

ll gpsSum() {
	ll sum = 0;
	FOR(i,0,n) FOR(j,0,n) if (wh[i][j] == 'O') {
		sum += 100 * i + j;
	}
	return sum;
}

void main() {
	FOR(i,0,n) {
		string row;
		cin >> row;
		FOR(j,0,n) wh[i][j] = row[j];
	}
	FOR(i,0,m) cin >> mv[i];
	
	cpos = get_robot_pos();
	FOR(i,0,m) move_robot(mv[i]);
	
	cout << gpsSum();
}