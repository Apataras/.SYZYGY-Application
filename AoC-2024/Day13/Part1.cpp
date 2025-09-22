#include <iostream>
#include <utility>
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

const int n = 320;
pll a[n];
pll b[n];
pll price[n];

void main() {
	FOR(i,0,n) {
		char _;
		FOR(i,0,10) cin >> _;
		cin >> a[i].first;
		FOR(i,0,3) cin >> _;
		cin >> a[i].second;
		FOR(i,0,10) cin >> _;
		cin >> b[i].first;
		FOR(i,0,3) cin >> _;
		cin >> b[i].second;
		FOR(i,0,8) cin >> _;
		cin >> price[i].first;
		FOR(i,0,3) cin >> _;
		cin >> price[i].second;
	}
	ll total_fewest_tokens = 0;
	FOR(i,0,n) {
		ll TOO_MUCH = 100 * 3 + 100 * 1 + 1;
		ll fewest_tokens = TOO_MUCH;
		FOR(n_a,0,101) {
			FOR(n_b,0,101) {
				if (n_a * a[i].first + n_b * b[i].first == price[i].first 
					&& n_a * a[i].second + n_b * b[i].second == price[i].second) {
					fewest_tokens = min(n_a * 3 + n_b * 1, fewest_tokens);
				}						
			}
		}
		if (fewest_tokens < TOO_MUCH)
			total_fewest_tokens += fewest_tokens;
	}
	cout << total_fewest_tokens;
}