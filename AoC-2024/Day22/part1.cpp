#include <iostream>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

const ll n = 2000;
const ll X = 2000;
ll s[n];

ll sum_of_Xth_generated_secret_numbers() {
	FOR(i,0,n) FOR(_,0,X) {
		s[i] ^= s[i]*64;
		s[i] %= 16777216;
		s[i] ^= s[i]/32;
		s[i] %= 16777216;
		s[i] ^= s[i]*2048;
		s[i] %= 16777216;
	}
	ll sum = 0;
	FOR(i,0,n) sum += s[i];
	return sum;
}

void read_initial_secret_numbers() {
	FOR(i,0,n) cin >> s[i];
}

void main() {
	read_initial_secret_numbers();
	
	cout << sum_of_Xth_generated_secret_numbers();
}