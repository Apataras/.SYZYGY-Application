#include <iostream>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
const ll n = 500;
struct { ll x, y; } p[n], v[n];
const ll w = 101, h = 103;
const ll t = 100;

void main() {
	FOR(i,0,n) {
		char _; 
		cin >> _; cin >> _;
		cin >> p[i].x;
		cin >> _;
		cin >> p[i].y;
		cin >> _; cin >> _;
		cin >> v[i].x;
		cin >> _;
		cin >> v[i].y;
	}
	
	ll q[2][2] = {};
	FOR(i,0,n) {
		ll x = ((p[i].x + t * v[i].x) % w + w) % w;
		ll y = ((p[i].y + t * v[i].y) % h + h) % h;
		if (x == w/2 || y == h/2) continue;
		q[x/((w+1)/2)][y/((h+1)/2)]++;
	}
	
	ll s = 1;
	FOR(i,0,2) FOR(j,0,2) s *= q[i][j];

	cout << s;
}