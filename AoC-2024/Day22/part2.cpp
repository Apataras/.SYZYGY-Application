#include <iostream>
#include <map>
#include <array>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define FORIT(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)


const ll n = 2000;
const ll X = 2000;
ll s[n];

array<ll,4> seq[n];
ll sum_of_Xth_generated_secret_numbers() {
	map<array<ll,4>,array<ll,n>> max_b; // map<seq,max_bananas[i]>
	FOR(i,0,n) FOR(t,0,X) {
		ll x = s[i];
		x ^= x*64;
		x %= 16777216;
		x ^= x/32;
		x %= 16777216;
		x ^= x*2048;
		x %= 16777216;
		FOR(j,1,4) seq[i][j-1] = seq[i][j];
		seq[i][3] = s[i]%10-x%10;
		s[i] = x;
		if (t < 3) continue;
		if (!max_b[seq[i]][i]) max_b[seq[i]][i] = x % 10;
	}
	ll mx = -1;
	FORIT(y,max_b) {
		ll sum = 0;
		FOR(i,0,n) sum += y->second[i];
		mx = max(sum,mx);
	}
	return mx;
}

void read_initial_secret_numbers() {
	FOR(i,0,n) cin >> s[i];
}

void main() {
	read_initial_secret_numbers();
	
	cout << sum_of_Xth_generated_secret_numbers();
}