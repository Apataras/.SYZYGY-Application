#include <iostream>
#include <utility>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

const ll n = 141;
char maze[n][n];
struct pos { ll i,j; };
enum dir { north, east, south, west };

pos get_start_pos() {
	FOR(i,0,n) FOR(j,0,n) if (maze[i][j] == 'S') return {i,j};
	//unreachable();
	return {-1,-1};
}
pos get_end_pos() {
	FOR(i,0,n) FOR(j,0,n) if (maze[i][j] == 'E') return {i,j};
	//unreachable();
	return {-1,-1};
}
const long long max_ll = 9223372036854775807LL;
ll low_score[n][n][4];
ll find_lowest_score_path(pos from, pos to, dir sdir, ll score) {
	if (maze[from.i][from.j] == '#') return max_ll;
	if (from.i == to.i && from.j == to.j) return score;
	
	if (low_score[from.i][from.j][sdir] < score) return max_ll;
	
	low_score[from.i][from.j][sdir] = score;
	ll lowest = max_ll;
	FOR(d,0,4) {
		if (d == sdir) {
			pos p_next;
			switch (d) {
			case north: p_next = {from.i-1,from.j}; break;
			case east: p_next = {from.i,from.j+1}; break;
			case south: p_next = {from.i+1,from.j}; break;
			case west: p_next = {from.i,from.j-1}; break;
			default: cout << "ERRRORR" << endl; break;
			}
			lowest = min(lowest, find_lowest_score_path(p_next, to, sdir, score+1));
		} else {
			lowest = min(lowest, find_lowest_score_path(from, to, (dir)d, score+1000));
		}
	}
	return lowest;
}
ll find_lowest_score_path(pos from, pos to, dir sdir) {
	FOR(i,0,n) FOR(j,0,n) FOR(d,0,4) low_score[i][j][d] = max_ll;
	/*FOR(i,0,n) {
		FOR(j,0,n) cout << maze[i][j];
		cout << endl;
	}*/
	return find_lowest_score_path(from, to, sdir, 0);
}


void main() {
	FOR(i,0,n) FOR(j,0,n) cin >> maze[i][j];
	
	pos spos = get_start_pos(), epos = get_end_pos();
	
	cout << find_lowest_score_path(spos, epos, east);
}