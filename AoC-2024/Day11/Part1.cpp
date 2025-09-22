#include <iostream>
#include <queue>
using namespace std;

#define int long long

const int n = 8;
int stone[n];
const int BLINK_TIMES = 25;
const int SENTINEL = -1;
queue<int> stones; 

void blink() {
	while (true) {
		int s = stones.front();
		stones.pop();
		if (s == SENTINEL) {
			stones.push(SENTINEL);
			return;
		}
		if (s == 0) {
			stones.push(1);
			continue;
		}
		int sc = s;
		int dn = 0;
		while (sc) {
			sc /= 10;
			dn++;
		}
		if (dn % 2 == 0) {
			int f = 1;
			for (int i = 0; i < dn/2; i++) {
				f *= 10;
			}
			stones.push(s / f);
			stones.push(s % f);
		} else {
			stones.push(s * 2024);
		}
	}
}

void main() {
	for (int i = 0; i < n; i++) {
		cin >> stone[i];
	}
	
	for (int i = 0; i < n; i++) {
		stones.push(stone[i]);
	}
	stones.push(SENTINEL);
	
	for (int i = 0; i < BLINK_TIMES; i++) {
		blink();
		cout << stones.size() << endl;
	}
	
	cout << stones.size()-1 << endl;
}
