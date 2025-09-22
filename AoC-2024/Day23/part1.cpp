#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (decltype(a) i = (a); i < (b); ++i)

const ll n = 3380;
string cons[n][2];

bool starts_with_t(string s) {
	return s[0] == 't';
}

ll no_lan_parties() {
	map<string,map<string,bool>> mat;
	set<string> keys;
	FOR(i,0,n) {
		mat[cons[i][0]][cons[i][1]] = true;
		mat[cons[i][1]][cons[i][0]] = true;
		keys.insert(cons[i][0]);
		keys.insert(cons[i][1]);
	}
	ll no = 0;
	FOR(i,0,n-1) FOR(j,i+1,n) {
		if (!starts_with_t(cons[i][0]) && !starts_with_t(cons[i][1]) && !starts_with_t(cons[j][0]) && !starts_with_t(cons[j][1])) continue;
		//cout << "i " << cons[i][0] << " " << cons[i][1] << endl;
		//cout << "j " << cons[j][0] << " " << cons[j][1] << endl;
		if (cons[i][0] == cons[j][0]) {
		//	cout << "HI" << endl;
			no += mat[cons[i][1]][cons[j][1]];
		} else if (cons[i][0] == cons[j][1]) {
			no += mat[cons[i][1]][cons[j][0]];
		} else if (cons[i][1] == cons[j][0]) {
			no += mat[cons[i][0]][cons[j][1]];
		} else if (cons[i][1] == cons[j][1]) {
		//	cout << "HI" << endl;
			no += mat[cons[i][0]][cons[j][0]];
		}
	}
	return no/3;
}

void read_cons() {
	FOR(i,0,n) {
		string con;
		cin >> con;
		cons[i][0] = con.substr(0,2);
		cons[i][1] = con.substr(3,2);
	}
	// cout << cons[1][0] << "-" << cons[1][1] << endl;
}

void main() {
	read_cons();
	
	cout << no_lan_parties();
}
