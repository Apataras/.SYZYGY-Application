#include <iostream>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
const ll n = 500;
struct { ll x, y; } p[n], v[n];
const ll w = 101, h = 103;
const ll t = 100;

// What a bullshit puzzle
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
	
	char _;
	ll s = 0;
	ll start = 7570;
	while (true) {
		FOR(i,0,n) {
			p[i].x = ((p[i].x + v[i].x) % w + w) % w;
			p[i].y = ((p[i].y + v[i].y) % h + h) % h;
		}
		s++;
		if (s < start) continue;
		char o[h][w];
		FOR(i,0,h) FOR(j,0,w) o[i][j] = ' ';
		FOR(i,0,n) o[p[i].y][p[i].x] = 'X';
		FOR(i,0,h) {
			FOR(j,0,w) cout << o[i][j];
			cout << '\n';
		}
		cout << s << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		if (s % 100 == 76) std::this_thread::sleep_for(std::chrono::seconds(10));
	}
}