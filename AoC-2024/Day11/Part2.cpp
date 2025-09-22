#include <iostream>
#include <queue>
using namespace std;

#define int long long

const int n = 8;
int stone[n];
const int BLINK_TIMES = 75;

int mem[10][BLINK_TIMES];
int dp(int x, int n) {
	if (n == 0) return 1;
	
	if (x < 10 && mem[x][n]) return mem[x][n];
	
	
	int r;
	if (x == 0) {
		r = dp(1,n-1);
	} else {
		int d = 0;
		int xc = x;
		while (xc) {
			xc /= 10;
			d++;
		}
		
		if (d % 2 == 0) {
			int f = 1;
			for (int i = 0; i < d/2; i++) {
				f *= 10;
			}
			r = dp(x/f,n-1) + dp(x%f,n-1);
		} else {
			r = dp(x*2024,n-1);
		}
	}
	if (x < 10) mem[x][n] = r;
	return r;
}

void main() {
	for (int i = 0; i < n; i++) {
		cin >> stone[i];
	}
	
	int sn = 0;
	for (int i = 0; i < n; i++) {
		sn += dp(stone[i],BLINK_TIMES);
	}
	
	cout << sn << endl;
}