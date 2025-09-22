#include <iostream>
#include <queue>
#include <set>
#include <utility>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

const ll m = 3450;
struct pos { ll i,j; 
	// Override operator==
    bool operator==(const pos& other) const {
        return i == other.i && j == other.j;
    }
	// Define the `<` operator
    bool operator<(const pos& other) const {
        if (i == other.i) {
            return j < other.j;
        }
        return i < other.i;
    }
} fb[m];

const ll n = 71;
char mem[n][n];

ll min_steps_to_reach_exit() {
	pos exit = { n-1, n-1 };
	ll s = 0;
	pos sv = {-1,-1};
	set<pos> V;
	queue<pos> Q;
	Q.push({0,0});
	Q.push(sv);
	while (!(Q.empty())) {
		pos cpos = Q.front();
		Q.pop();
		if (cpos == sv) {
			s++;
			Q.push(sv);
			continue;
		}
		if (!(0 <= cpos.i && cpos.i < n && 0 <= cpos.j && cpos.j < n)) continue;
		if (mem[cpos.i][cpos.j] == '#') continue;
		if (cpos == exit) break;
		if (V.find(cpos) != V.end()) continue;
		
		V.insert(cpos);
		Q.push({cpos.i-1,cpos.j});
		Q.push({cpos.i,cpos.j+1});
		Q.push({cpos.i+1,cpos.j});
		Q.push({cpos.i,cpos.j-1});
	}
	return s;
}

void simulate_bytes_falling(ll x) {
	FOR(i,0,x) mem[fb[i].i][fb[i].j] = '#';
}

void read_falling_bytes() {
	FOR(i,0,m) {
		char comma;
		cin >> fb[i].i >> comma >> fb[i].j;
	}
}

void main() {
	read_falling_bytes();
	
	simulate_bytes_falling(1024);
	
	cout << min_steps_to_reach_exit();
}