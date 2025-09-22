#include <iostream>
#include <initializer_list>
#include <vector>
#include <set>
using namespace std;

#define mp(a,b) make_pair(a,b)
#define int long long

const int n = 140;
char grid[n][n];

pair<int,int> r_rep[n][n];
const pair<int,int> IGNORE;
pair<int,int> region_rep(int i, int j, pair<int,int> r) {
	if (!(0 <= i && i < n && 0 <= j && j < n)) return IGNORE;
	if (grid[i][j] != grid[r.first][r.second]) return IGNORE;
	
	if (r_rep[i][j].first != -1) return r_rep[i][j];
	
	r_rep[i][j] = r;
	for (auto [i_n,j_n] : {mp(i-1,j),mp(i,j+1),mp(i+1,j),mp(i,j-1)}) {
		(void)region_rep(i_n,j_n,r);
	}
	return r;
}

int calcArea(pair<int,int> r, char rv, set<pair<int,int>>& v) {
	auto [i,j] = r;
	if (!(0 <= i && i < n && 0 <= j && j < n)) return 0;
	if (grid[i][j] != rv) return 0;
	if (v.find(r) != v.end()) return 0;
	
	
	int area = 1; // self
	v.insert(r);
	for (auto r_n : {mp(i-1,j),mp(i,j+1),mp(i+1,j),mp(i,j-1)}) {
		area += calcArea(r_n, rv, v);
	}
	return area;
}

int calcFences(pair<int,int> r, char rv, set<pair<int,int>>& v) {
	auto [i,j] = r;
	if (!(0 <= i && i < n && 0 <= j && j < n)) return 1;
	if (grid[i][j] != rv) return 1;
	if (v.find(r) != v.end()) return 0;
	
	int fences = 0;
	v.insert(r);
	for (auto r_n : {mp(i-1,j),mp(i,j+1),mp(i+1,j),mp(i,j-1)}) {
		fences += calcFences(r_n, rv, v);
	}
	return fences;
}

void main() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			r_rep[i][j] = mp(-1,-1);
		}
	}
	
	set<pair<int,int>> regions;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			regions.insert(region_rep(i, j, mp(i,j)));
		}
	}
	
	int price = 0;
	for (auto r : regions) {
		char rv = grid[r.first][r.second];
		price += calcArea(r, rv, set<pair<int,int>>{}) * calcFences(r, rv, set<pair<int,int>>{});
	}
	
	cout << price << endl;
}

