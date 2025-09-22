#include <iostream>

using namespace std;

const int n = 20000;
char diskmap[n];

int disk[n*9];

void main() {
	for (int i = 0; i < n; i++) {
		cin >> diskmap[i];
	}
	
	int len = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < diskmap[i]-'0'; j++) {
			disk[len++] = i%2 ? 0 : (i/2)+1;
		}
	}
	
	int li = 0;
	int ri = len-1;
	while (true) {
		while (disk[li]) li++;
		while (!disk[ri]) ri--;
		if (li > ri) break;
		disk[li] = disk[ri];
		disk[ri] = FREE;
	}
	
	long long chsum = 0;
	for (int i = 0; i < li; i++) {
		chsum += i * (long long)(disk[i]-1);
	}
	
	cout << chsum << endl;
}