#include <iostream>
#include <utility>
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

using namespace std;
typedef long long ll;

const int n = 320;
struct Coord { ll x,y; };
Coord a[n];
Coord b[n];
Coord p[n];

// a * A_x + b * B_x = P_x
// a * A_y + b * B_y = P_y
// => b = (P_y - a * A_y) / B_y;
// ==> a * A_x + (P_y - a * A_y) / B_y * B_x = P_x
// ==> a = (P_x * B_y - P_y * B_x) / (A_x * B_y - A_y * B_x)

// lol should be incomplete but works for part 2
void main() {
	FOR(i,0,n) {
		char _;
		FOR(i,0,10) cin >> _;
		cin >> a[i].x;
		FOR(i,0,3) cin >> _;
		cin >> a[i].y;
		FOR(i,0,10) cin >> _;
		cin >> b[i].x;
		FOR(i,0,3) cin >> _;
		cin >> b[i].y;
		FOR(i,0,8) cin >> _;
		cin >> p[i].x;
		FOR(i,0,3) cin >> _;
		cin >> p[i].y;
	}
	FOR(i,0,n) p[i].x += 10000000000000, p[i].y += 10000000000000;
	ll total_fewest_tokens = 0;
	FOR(i,0,n) {
		ll n_n_a = p[i].x * b[i].y - p[i].y * b[i].x;
		ll d_n_a = a[i].x * b[i].y - a[i].y * b[i].x;
		ll n_a = n_n_a / d_n_a;
		ll n_n_b = p[i].y - n_a * a[i].y;
		ll d_n_b = b[i].y;
		ll n_b = n_n_b / d_n_b;
		if (n_n_a % d_n_a || n_n_b % d_n_b) continue;
		total_fewest_tokens += n_a * 3 + n_b * 1;
	}
	cout << total_fewest_tokens;
}