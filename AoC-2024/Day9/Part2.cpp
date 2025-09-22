#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// FUCK \n as the last char ajenb lfbasiupefiaesuifuisahfihasihf aiufhuiaehiufhi
const int n = 19999;//19;//20000;
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
	
	cout << "LAST" << diskmap[n-1] << " F " << diskmap[n-2] << endl;
	
	map<int, vector<int>> no_free_spaces_to_locs;
	// Disk full of files (no files 0 block size) => Max free block size is 9 (since files from right to left moved)
	for (int i = 1; i <= 9; i++) {
		no_free_spaces_to_locs[i] = {};
	}
	for (int i = 0, loc = 0; i < n; loc += diskmap[i]-'0', i++) {
		///cout << "DM " << diskmap[i] << " loc " << loc << endl;
			if (loc < 0) cout << "IJOJIOJJO" << endl;
		if (i%2 && diskmap[i] != '0') no_free_spaces_to_locs[diskmap[i]-'0'].push_back(loc);
	}
	for (auto& entry : no_free_spaces_to_locs) {
		reverse(entry.second.begin(), entry.second.end());
		/*cout << "F ";
		for (auto&entry2 : entry.second) {
			cout << entry2 << " ";
		}
		cout << endl;*/
	}
	
	int loc_c = len;
	for (int ri = n-1-(n-1)%2; ri; ri -= 2) {
		loc_c -= diskmap[ri]-'0';
		if (ri+1<n) loc_c -= diskmap[ri+1]-'0';
		int leftmost_sz = 0;
		int leftmost_new_pos = loc_c;
		//cout << "SWAPPING " << ri/2 << " " << diskmap[ri] << " IOJIO " << leftmost_new_pos << endl;

		for (int sz = diskmap[ri]-'0'; sz <= 9; sz++) {
			if (no_free_spaces_to_locs[sz].empty()) continue;
			int new_pos = no_free_spaces_to_locs[sz].back();
			/*if (ri/2 == 2) for (auto& entry : no_free_spaces_to_locs) {
				//reverse(entry.second.begin(), entry.second.end());
				cout << "RI222 ";
				for (auto&entry2 : entry.second) {
					cout << entry2 << " ";
				}
				cout << endl;
			}		
			cout << "AHHHH" << new_pos << endl;*/
			if (new_pos < leftmost_new_pos) {
				//cout << ":(" << endl;
				leftmost_sz = sz;
				leftmost_new_pos = new_pos;
			}
		}
		
		if (!leftmost_sz) {
			continue;
		}
		
		//cout << leftmost_sz << " JIOO " << leftmost_new_pos << " RI " << ri << endl;
		
		auto x = no_free_spaces_to_locs[leftmost_sz];//.pop_back();
		x.pop_back();
		no_free_spaces_to_locs[leftmost_sz] = x;
		for (int i = 0; i < diskmap[ri]-'0'; i++) {
			disk[leftmost_new_pos+i] = ri/2 + 1;
			disk[loc_c+i] = 0;
		}
		if (leftmost_sz - (diskmap[ri]-'0')) {
			vector<int> xa = no_free_spaces_to_locs[leftmost_sz-(diskmap[ri]-'0')];
			xa.push_back(leftmost_new_pos+(diskmap[ri]-'0'));
			sort(xa.begin(), xa.end(), greater<int>());
			no_free_spaces_to_locs[leftmost_sz-(diskmap[ri]-'0')] = xa;
		}
	}
	
	
	long long chsum = 0;
	long long skipped = 0;
	for (int i = 0; i < len; i++) {
		//cout << (char)(disk[i]-1+'0');
		if (!disk[i]) {/* skipped++;*/ continue; }
		chsum += (i-skipped) * (long long)(disk[i]-1);
	}
	//cout << endl;
	
	cout << chsum << endl;
}