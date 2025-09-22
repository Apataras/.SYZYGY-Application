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

bool is_exit_reachable() {
	pos exit = { n-1, n-1 };
	set<pos> V;
	queue<pos> Q;
	Q.push({0,0});
	while (!(Q.empty())) {
		pos cpos = Q.front();
		Q.pop();
		if (!(0 <= cpos.i && cpos.i < n && 0 <= cpos.j && cpos.j < n)) continue;
		if (mem[cpos.i][cpos.j] == '#') continue;
		if (cpos == exit) return true;
		if (V.find(cpos) != V.end()) continue;
		
		V.insert(cpos);
		Q.push({cpos.i-1,cpos.j});
		Q.push({cpos.i,cpos.j+1});
		Q.push({cpos.i+1,cpos.j});
		Q.push({cpos.i,cpos.j-1});
	}
	return false;
}

void simulate_byte_falling(ll x) {
	mem[fb[x].i][fb[x].j] = '#';
}

pos first_to_make_impossible() {
	FOR(i,0,1024) simulate_byte_falling(i); // We know we can reach the exit from part 1
	FOR(x,1024,m) {
		simulate_byte_falling(x);
		if (!is_exit_reachable()) return fb[x];
	}
	__assume(false);
}

void read_falling_bytes() {
	FOR(i,0,m) {
		char comma;
		cin >> fb[i].i >> comma >> fb[i].j;
	}
}

void main() {
	read_falling_bytes();
	
	pos denyer = first_to_make_impossible();
	cout << denyer.i << "," << denyer.j;
}