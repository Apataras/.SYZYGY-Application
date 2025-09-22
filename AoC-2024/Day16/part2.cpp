#include <iostream>
#include <utility>
#include <set>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define mp(a,b) make_pair((a),(b))

const ll n = 141;
char maze[n][n];
struct pos { ll i,j; 
	bool operator<(const pos& other) const {
        if (i != other.i)
            return i < other.i; // Compare based on 'i' first
        return j < other.j;     // Compare based on 'j' if 'i' is equal
    }
};
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
// TODO upon return of lowest put shortes path in set => set size
pair<ll,set<pos>> find_lowest_score_path(pos from, pos to, dir sdir, ll score, ll count) {
	if (maze[from.i][from.j] == '#') return mp(max_ll,set<pos>{});
	if (from.i == to.i && from.j == to.j) return mp(score,set<pos>{to});
	
	if (score > 130536) return mp(max_ll, set<pos>{});
	
	if (low_score[from.i][from.j][sdir] < score) return mp(max_ll,set<pos>{});
	
	low_score[from.i][from.j][sdir] = score;
	ll lowest = max_ll;
	set<pos> s;
	s.insert(from);
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
			pair<ll,set<pos>> v = find_lowest_score_path(p_next, to, sdir, score+1, count+1);
			if (v.first < lowest) {
				lowest = v.first;
				s.clear();
				s.insert(from);
				s.insert(v.second.begin(), v.second.end());
			} else if (lowest != max_ll && v.first == lowest) {
				s.insert(v.second.begin(), v.second.end());
			}
		} else {
			pair<ll,set<pos>> v = find_lowest_score_path(from, to, (dir)d, score+1000, count);
			if (v.first < lowest) {
				lowest = v.first;
				s.clear();
				s.insert(from);
				s.insert(v.second.begin(), v.second.end());
			} else if (lowest != max_ll && v.first == lowest) {
				s.insert(v.second.begin(), v.second.end());
			}
		}
	}
	return mp(lowest,s);
}
ll find_lowest_score_path(pos from, pos to, dir sdir) {
	FOR(i,0,n) FOR(j,0,n) FOR(d,0,4) low_score[i][j][d] = max_ll;
	/*FOR(i,0,n) {
		FOR(j,0,n) cout << maze[i][j];
		cout << endl;
	}*/
	return find_lowest_score_path(from, to, sdir, 0, 0).second.size();
}


void main() {
	FOR(i,0,n) FOR(j,0,n) cin >> maze[i][j];
	
	pos spos = get_start_pos(), epos = get_end_pos();
	
	cout << find_lowest_score_path(spos, epos, east);
}