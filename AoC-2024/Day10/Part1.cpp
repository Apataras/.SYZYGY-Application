#include <iostream>
#include <vector>
#include <utility> // for std::make_pair
#include <initializer_list>
#include <set>
#include <optional>
#include <algorithm>

using namespace std;

#define mp(a,b) make_pair(a,b)

const int n = 40;//8;//40;
int grid[n][n];
optional<set<pair<int,int>>> mem[n][n];
set<pair<int,int>> reachables(int i, int j) {
	if (grid[i][j] == 9) return {mp(i,j)};
	
	if (mem[i][j]) return mem[i][j].value();
	
	set<pair<int,int>> reachables_set;
	for (auto& mov : {mp(i-1,j),mp(i,j+1),mp(i+1,j),mp(i,j-1)}) {
		int mi = mov.first;
		int mj = mov.second;
		if (!(0 <= mi && mi < n && 0 <= mj && mj < n)) continue;
		if (grid[mi][mj] == grid[i][j]+1) {
			auto set1 = reachables_set;
			auto set2 = reachables(mi, mj);
			set_union(set1.begin(), set1.end(),
              set2.begin(), set2.end(),
              inserter(reachables_set, reachables_set.begin()));
		}
	}
	mem[i][j] = reachables_set;
	return reachables_set;
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
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mem[i][j] = -1;
		}
	}*/
	vector<pair<int,int>> trailheads;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0) {
				trailheads.push_back(mp(i,j));
			}
		}
	}
	int scoreSum = 0;
	for (auto& th : trailheads) {
		int score = reachables(th.first, th.second).size();
		scoreSum += score;
	}
	cout << scoreSum << endl;
}
