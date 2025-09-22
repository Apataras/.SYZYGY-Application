/*
Double grid horiz and vertic
Put in empty spaces valid fences
Go through all fences (from top left to bottom right) horizontal as well as vertical
2 fence count ints (to the top of it and bottom of fence). Reset to 0 if new region at resp. side else inc++.
If reset or eol get r_rep of region above/below and add v to it
*/
#include <iostream>
#include <initializer_list>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

#define mp(a,b) make_pair(a,b)
#define int long long

const int og_n = 140;//6;//140;
char og_grid[og_n][og_n];
const int n = 2 * og_n + 2 + 1 /*Eig. +2*/; // surround with fences and one empty space
char grid[n][n];

pair<int,int> r_rep[n][n];
const pair<int,int> IGNORE;
pair<int,int> region_rep(int i, int j, pair<int,int> r) {
	if (!(0 <= i && i < n && 0 <= j && j < n)) return IGNORE;
	if (grid[i][j] != grid[r.first][r.second]) return IGNORE;
	
	if (r_rep[i][j].first != -1) return r_rep[i][j];
	
	cout << i << " " << j << endl;
	
	r_rep[i][j] = r;
	for (auto [i_n,j_n] : {mp(i-1,j),mp(i,j+1),mp(i+1,j),mp(i,j-1)}) {
		(void)region_rep(i_n,j_n,r);
	}
	return r;
}

int calcArea(pair<int,int> r, char rv, set<pair<int,int>>& v) {
	auto [i,j] = r;
	if (!(0 <= i && i < og_n && 0 <= j && j < og_n)) return 0;
	if (og_grid[i][j] != rv) return 0;
	if (v.find(r) != v.end()) return 0;
	
	
	int area = 1; // self
	v.insert(r);
	for (auto r_n : {mp(i-1,j),mp(i,j+1),mp(i+1,j),mp(i,j-1)}) {
		area += calcArea(r_n, rv, v);
	}
	return area;
}

void main() {
	for (int i = 0; i < og_n; i++) {
		for (int j = 0; j < og_n; j++) {
			cin >> og_grid[i][j];
		}
	}

	// Double dimensions and include fences inbetween
	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < n-1; j++) {
			grid[i][j] = '-';
		}
	}
	for (int i = 0; i < og_n; i++) {
		for (int j = 0; j < og_n; j++) {
			grid[2*i+1+1][2*j+1+1] = og_grid[i][j];
		}
	}
	
	// Delete invalid fences (by spreading regions) => * 2 - 1 many
	for (int i = 1; i < n-2; i++) {
		for (int j = 1; j < n-1; j++) {
			if (grid[i][j] == '-') continue;
			if (grid[i][j] == grid[i+2][j]) {
				grid[i+1][j] = grid[i][j];
			}
		}
	}
	for (int j = 1; j < n-2; j++) {
		for (int i = 1; i < n-1; i++) {
			if (grid[i][j] == '-') continue;
			if (grid[i][j] == grid[i][j+2]) {
				grid[i][j+1] = grid[i][j];
			}
		}
	}
	/*for (int i = 0; i < og_n-1; i++) {
		for (int j = 0; j < og_n; j++) {
			if (og_grid[i][j] == og_grid[i+1][j]) {
				grid[2*i+1+1+1][2*j+1+1] = grid[2*i+1+1][2*j+1+1];
			}
		}
	}
	for (int j = 0; j < og_n-1; j++) {
		for (int i = 0; i < og_n; i++) {
			if (og_grid[i][j] == og_grid[i][j+1]) {
				grid[2*i+1+1][2*j+1+1+1] = grid[2*i+1+1][2*j+1+1];
			}
		}
	}*/
	
	cout << "PRINTING" << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j];
		}
		cout << '\n';
	}
	cout << "AHHHHH" << endl;
	
	
	//if (true) return;
	
	// Get region representatives
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			r_rep[i][j] = mp(-1,-1);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			(void)region_rep(i, j, mp(i,j));
		}
	}
	
	cout << "NOWW!" << endl;
	
	map<pair<int,int>,int> fence_price;
	// Go through all fences (horizontal)
	for (int i = 1; i < n-1; i++) {
		int ul = 0; pair<int,int> ur = mp(1,1);
		int ll = 0; pair<int,int> lr = mp(1,1);
		for (int j = 1; j < n-1; j++) {
			if (grid[i][j] != '-') {
				if (ul != 0) {
					fence_price[ur] += 1;//(ul+1) / 2;
					ul = 0; ur = r_rep[i-1][j];
				}
				if (ll != 0) {
					fence_price[lr] += 1;//(ll+1) / 2;
					ll = 0; lr = r_rep[i+1][j];
				}
				continue;
			}
			if (r_rep[i-1][j] != ur) {
				if (ul > 0) fence_price[ur] += 1;//(ul+1) / 2;
				ul = 0; ur = r_rep[i-1][j];
			}
			if (r_rep[i+1][j] != lr) {
				if (ll > 0) fence_price[lr] += 1;//(ll+1) / 2;
				ll = 0; lr = r_rep[i+1][j];
			}
			
			ul++;
			ll++;
		}
	}
	cout << "Hi?" << endl;
	
	// Go through all fences (vertical)
	for (int j = 1; j < n-1; j++) {
		int ul = 0; pair<int,int> ur = mp(1,1);
		int ll = 0; pair<int,int> lr = mp(1,1);
		for (int i = 1; i < n-1; i++) {
			if (grid[i][j] != '-') {
				if (ul != 0) {
					fence_price[ur] += 1;//(ul+1) / 2;
					ul = 0; ur = r_rep[i][j-1];
				}
				if (ll != 0) {
					fence_price[lr] += 1;//(ll+1) / 2;
					ll = 0; lr = r_rep[i][j+1];
				}
				continue;
			}
			if (r_rep[i][j-1] != ur) {
				if (ul > 0) fence_price[ur] += 1;//(ul+1) / 2;
				ul = 0; ur = r_rep[i][j-1];
			}
			if (r_rep[i][j+1] != lr) {
				if (ll > 0) fence_price[lr] += 1;//(ll+1) / 2;
				ll = 0; lr = r_rep[i][j+1];
			}
			
			ul++;
			ll++;
		}
	}
	cout << ":( " << endl;
	
	int price = 0;
	for (auto [k,v] : fence_price) {
		if (grid[k.first][k.second] == '-') continue;
		cout << k.first << " " << k.second << " ----- " << v << endl;
		cout << og_grid[(k.first-2)/2][(k.second-2)/2] << endl;
		cout << mp((k.first-2)/2,(k.second-2)/2).first << endl;
		cout << calcArea(mp((k.first-2)/2,(k.second-2)/2), og_grid[(k.first-2)/2][(k.second-2)/2], set<pair<int,int>>{}) << endl; 
		price += v * (calcArea(mp((k.first-2)/2,(k.second-2)/2), og_grid[(k.first-2)/2][(k.second-2)/2], set<pair<int,int>>{}));
	}
	
	cout << price << endl;
}

