#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define FORIT(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define mp(a,b) make_pair((a),(b))

const ll n = 5;
char c[n][4];

const char num_kp[4][3] = {
	{ '7', '8', '9' },
		{ '4', '5', '6' },
			{ '1', '2', '3' },
				{ '\0', '0', 'A' }
};
const char dir_kp[2][3] = {
	{ '\0', '^', 'A' },
		{ '<', 'v', '>' }
};
ll row(ll kp_id, char c) {
	if (kp_id == 0) { FOR(i,0,4) FOR(j,0,3) if (num_kp[i][j] == c) return i; }
	else { FOR(i,0,2) FOR(j,0,3) if (dir_kp[i][j] == c) return i; }
	__assume(false);
}
ll column(ll kp_id, char c) {
	if (kp_id == 0) { FOR(i,0,4) FOR(j,0,3) if (num_kp[i][j] == c) return j; }
	else { FOR(i,0,2) FOR(j,0,3) if (dir_kp[i][j] == c) return j; }
	__assume(false);
}

string simulate_typing(ll kp_id, char k, char p[4]) {
	if (kp_id == 3) return {k};
	vector<char> buttons;
	bool goes_up = false, goes_down = false;
	FOR(_,column(kp_id,p[kp_id]),column(kp_id,k)) buttons.push_back('>');
	FOR(_,row(kp_id,k),row(kp_id,p[kp_id])) buttons.push_back('^'), goes_up = true;
	FOR(_,row(kp_id,p[kp_id]),row(kp_id,k)) buttons.push_back('v'), goes_down = true;
	FOR(_,column(kp_id,k),column(kp_id,p[kp_id])) buttons.push_back('<');
	buttons.push_back('A');
	string s = "";
	{
		char p_tmp[4]; FOR(i,0,4) p_tmp[i] = p[i];
		FORIT(b,buttons) s += simulate_typing(kp_id+1, *b, p);
		
		if (goes_up && p[kp_id+1] != '<' && (kp_id != 0 || kp_id == 0 && (row(0,p[0]) != 3 || column(0,k) >= 1)) 
			|| goes_down && p[kp_id+1] != '^' && (kp_id != 0 || kp_id == 0 && (row(0,k) != 3 || column(0,p[0]) >= 1))
			|| !goes_up && !goes_down) {
			char p_tmptmp[4]; FOR(i,0,4) p_tmptmp[i] = p[i];
			FOR(i,0,4) p[i] = p_tmp[i];
			buttons.pop_back();
			reverse(buttons.begin(), buttons.end());
			buttons.push_back('A');
			string s2 = "";
			FORIT(b,buttons) s2 += simulate_typing(kp_id+1, *b, p);
			if (s2.length() < s.length()) {
				s = s2;
			} else {
				FOR(i,0,4) p[i] = p_tmptmp[i];
			}
		}
	}
	
	p[kp_id] = k;
	return s;
}



ll row(char c) {
	FOR(i,0,2) FOR(j,0,3) if (dir_kp[i][j] == c) return i;
	__assume(false);
}
ll column(char c) {
	FOR(i,0,2) FOR(j,0,3) if (dir_kp[i][j] == c) return j;
	__assume(false);
}

ll x = 0;
char next(char c, char r) {
	switch (r) {
	case '^': return num_kp[row(c)-1][column(c)];
	case '>': return num_kp[row(c)][column(c)+1];
	case 'v': return num_kp[row(c)+1][column(c)];
	case '<': return num_kp[row(c)][column(c)-1];
	default: __assume(false);
	}
}
ll row2(char c) {
	FOR(i,0,2) FOR(j,0,3) if (dir_kp[i][j] == c) return i;
	__assume(false);
}
ll column2(char c) {
	FOR(i,0,2) FOR(j,0,3) if (dir_kp[i][j] == c) return j;
	__assume(false);
}
ll move_weight(char p[4], char to, ll kpid) {
	//FOR(i,0,4) cout << p[i] << " ";
	//cout << endl;
	//cout << "--- " << to << " - " << kpid << endl;
	if (kpid == 3) cout << to;
	if (kpid == 0) {
		vector<char> dirs;
		ll add_m_presses = 0;
		if (row(to) < row(p[0])) dirs.push_back('^'), add_m_presses += row(p[0]) - row(to) - 1;
		if (column(to) > column(p[0])) dirs.push_back('>'), add_m_presses += column(to) - column(p[0]) - 1;
		if (row(to) > row(p[0])) dirs.push_back('v'), add_m_presses += row(to) - row(p[0]) - 1;
		if (column(to) < column(p[0])) dirs.push_back('<'), add_m_presses += column(p[0]) - column(to) - 1;
		ll sum = 0;
		char from[4];
		FOR(i,0,4) from[i] = p[i];
		FORIT(d,dirs) sum += move_weight(p, *d, kpid+1), p[kpid] = next(p[kpid], *d);
		sum += move_weight(p, 'A', kpid+1);
		//FOR(i,0,4) p[i] = from[i];
		ll sum2 = 10000;
		reverse(dirs.begin(), dirs.end());
		//FORIT(d,dirs) sum2 += move_weight(p, *d, kpid+1), p[kpid] = next(p[kpid], *d);
		//sum2 += move_weight(p, 'A', kpid+1);
		return min(sum, sum2) + add_m_presses + 1;
	}
	if (kpid == 3) {
		x++;
		return 1;
	}
	
	if (kpid == 2) {
		vector<char> dirs;
		ll add_m_presses = 0;
		if (row2(to) < row2(p[kpid])) dirs.push_back('^'), add_m_presses += row2(p[kpid]) - row2(to) - 1;
		if (column2(to) > column2(p[kpid])) dirs.push_back('>'), add_m_presses += column2(to) - column2(p[kpid]) - 1;
		if (row2(to) > row2(p[kpid])) dirs.push_back('v'), add_m_presses += row2(to) - row2(p[kpid]) - 1;
		if (column2(to) < column2(p[kpid])) dirs.push_back('<'), add_m_presses += column2(p[kpid]) - column2(to) - 1;
		char from[4];
		FOR(i,0,4) from[i] = p[i];
		ll sum = 0;
		FORIT(d,dirs) sum += move_weight(p, *d, kpid+1), p[kpid] = next(p[kpid], *d);
		sum += move_weight(p, 'A', kpid+1);
		//FOR(i,0,4) p[i] = from[i];
		ll sum2 = 100000;
		reverse(dirs.begin(), dirs.end());
		//FORIT(d,dirs) sum2 += move_weight(p, *d, kpid+1), p[kpid] = next(p[kpid], *d);
		//sum2 += move_weight(p, 'A', kpid+1);
		return min(sum, sum2) + 1; //+ add_m_presses + 1;
	}
	
	vector<char> dirs;
	ll add_m_presses = 0;
	if (row2(to) < row2(p[kpid])) dirs.push_back('^'), add_m_presses += row2(p[kpid]) - row2(to) - 1;
	if (column2(to) > column2(p[kpid])) dirs.push_back('>'), add_m_presses += column2(to) - column2(p[kpid]) - 1;
	if (row2(to) > row2(p[kpid])) dirs.push_back('v'), add_m_presses += row2(to) - row2(p[kpid]) - 1;
	if (column2(to) < column2(p[kpid])) dirs.push_back('<'), add_m_presses += column2(p[kpid]) - column2(to) - 1;
	char from[4];
	FOR(i,0,4) from[i] = p[i];
	ll sum = 0;
	FORIT(d,dirs) sum += move_weight(p, *d, kpid+1), p[kpid] = next(p[kpid], *d);
	sum += move_weight(p, 'A', kpid+1);
	//FOR(i,0,4) p[i] = from[i];
	ll sum2 = 100000;
	reverse(dirs.begin(), dirs.end());
	//FORIT(d,dirs) sum2 += move_weight(p, *d, kpid+1), p[kpid] = next(p[kpid], *d);
	//sum2 += move_weight(p, 'A', kpid+1);
	return min(sum, sum2) + add_m_presses + 1;
}
ll loss(char c[4]) {
	ll w = 0;
	char p[4] = {'A','A','A', '\0'};
	FOR(i,0,4) {
		string s = simulate_typing(0, c[i], p);
		cout << endl;
		FOR(i,0,4) cout << p[i] << " ";
		cout << endl;
		cout << "THAT WAS p" << endl;
		cout << s << endl;
		w += s.length();
	}
	//FOR(i,0,4) w += move_weight(p, c[i], 0), cout << endl;
	return w;
}
ll np(char c[4]) {
	ll v = 0;
	FOR(i,0,4) if (c[i] != 'A') {
		v *= 10;
		v += c[i]-'0';
	}
	return v;
}
ll complexity(char c[4]) {
	FOR(i,0,4) cout << c[i];
	cout << endl;
	ll xa = loss(c);
	cout << "loss " << xa << " np " << np(c) << endl;
	cout << "X " << x << endl;
	return xa * np(c);
}
// 225588180 too high
ll complexity_sum() {
	ll sum = 0;
	FOR(i,0,n) sum += complexity(c[i]);
	return sum;
}

void read_codes() {
	FOR(i,0,n) FOR(j,0,4) cin >> c[i][j];
}

void main() {
	read_codes();
	
	cout << complexity_sum();
}