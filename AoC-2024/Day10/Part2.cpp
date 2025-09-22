#include <iostream>
#include <vector>
#include <utility> // for std::make_pair
#include <initializer_list>
#include <set>
#include <optional>
#include <algorithm>

using namespace std;

#define mp(a,b) make_pair(a,b)

const int n = 40;//8;//40;//8;//40;
int grid[n][n];
long long mem[n][n];
long long rating(int i, int j) {
	if (grid[i][j] == 9) return 1;
	
	if (mem[i][j] != -1) return mem[i][j];
	
	long long rating_v = 0;
	for (auto& mov : {mp(i-1,j),mp(i,j+1),mp(i+1,j),mp(i,j-1)}) {
		int mi = mov.first;
		int mj = mov.second;
		if (!(0 <= mi && mi < n && 0 <= mj && mj < n)) continue;
		if (grid[mi][mj] == grid[i][j]+1) {
			rating_v += rating(mi,mj);
		}
	}
	mem[i][j] = rating_v;
	return rating_v;
}

void main() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			char digit;
			cin >> digit;
			if (digit == '\n' || digit == '\r') {
				cout << "CRY" << endl;
			}
			grid[i][j] = digit - '0';
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mem[i][j] = -1;
		}
	}
	vector<pair<int,int>> trailheads;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0) {
				trailheads.push_back(mp(i,j));
			}
		}
	}
	long long ratingSum = 0;
	for (auto& th : trailheads) {
		ratingSum += rating(th.first, th.second);
	}
	cout << ratingSum << endl;
}
