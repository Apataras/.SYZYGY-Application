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
	if (0 <= i-2) no += d[i][j]-d[i-2][j] >= 102;
	if (i+2 < n) no += d[i][j]-d[i+2][j] >= 102;
	if (0 <= j-2) no += d[i][j]-d[i][j-2] >= 102;
	if (j+2 < n) no += d[i][j]-d[i][j+2] >= 102;
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