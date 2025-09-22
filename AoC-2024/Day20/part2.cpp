#include <iostream>
#include <queue>
#include<utility>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
struct pos { ll i, j; };
const ll oo = 0x3f3f3f;
#define mp(a,b) make_pair((a),(b))

const ll n = 141;
char map[n][n];

ll d[n][n];
void bfs(pos spos) {
	FOR(i,0,n) FOR(j,0,n) d[i][j] = oo;
	queue<pair<ll,pos>> Q;
	Q.push(mp(0,spos));
	while (!Q.empty()) {
		auto x = Q.front();
		auto c = x.first;
		auto [i,j] = x.second;
		Q.pop();
		if (!(0 <= i && i < n && 0 <= j && j < n)) continue;
		if (map[i][j] == '#') continue;
		if (d[i][j] < oo) continue;
		d[i][j]=c;
		Q.push(make_pair(c+1,pos{i-1,j}));
		Q.push(make_pair(c+1,pos{i,j+1}));
		Q.push(make_pair(c+1,pos{i+1,j}));
		Q.push(make_pair(c+1,pos{i,j-1}));
	}
}

ll no_good_cheats(ll i, ll j) {
	ll no = 0;
	FOR(ri,-20,21) FOR(rj,-20,21) {
		ll ct = abs(ri)+abs(rj);
		if (ct <= 20) {
			if (0 <= i+ri && i+ri < n && 0 <= j+rj && j+rj < n) no += d[i][j]-d[i+ri][j+rj] >= 100+ct;
		}
	}
	return no;
}

ll no_good_cheats() {
	pos epos;
	FOR(i,0,n) FOR(j,0,n) if (map[i][j] == 'E') epos = {i,j};
	bfs(epos);
	ll no = 0;
	FOR(i,0,n) FOR(j,0,n) if (map[i][j] != '#') no += no_good_cheats(i, j);
	return no;
}

void read_map() {
	FOR(i,0,n) FOR(j,0,n) cin >> map[i][j];
}

void main() {
	read_map();
	
	cout << no_good_cheats();
}