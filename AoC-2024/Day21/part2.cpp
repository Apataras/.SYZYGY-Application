#include <iostream>
#include <vector>
#include <utility>
#include <map>
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
char next(ll kp_id, char c, char r) {
	if (kp_id == 0) {
		switch (r) {
		case '^': return num_kp[row(kp_id,c)-1][column(kp_id,c)];
		case '>': return num_kp[row(kp_id,c)][column(kp_id,c)+1];
		case 'v': return num_kp[row(kp_id,c)+1][column(kp_id,c)];
		case '<': return num_kp[row(kp_id,c)][column(kp_id,c)-1];
		case 'A': return c;
		default: __assume(false);
		}
	} else {
		switch (r) {
		case '^': return dir_kp[row(kp_id,c)-1][column(kp_id,c)];
		case '>': return dir_kp[row(kp_id,c)][column(kp_id,c)+1];
		case 'v': return dir_kp[row(kp_id,c)+1][column(kp_id,c)];
		case '<': return dir_kp[row(kp_id,c)][column(kp_id,c)-1];
		case 'A': return c;
		default: __assume(false);
		}
	}
}
const ll C = 20;//20;
const ll R = 25;//25;
map<pair<ll,pair<char,pair<ll,vector<char>>>>,pair<vector<char>,ll>> mem;
ll simulate_typing(ll kp_id, char k, char p[R+2]) {
	if (kp_id == R+1) return 1;
	
	if (kp_id > 0 && kp_id < R && (k == '<' && p[kp_id-1] == '^' || k == '^' && p[kp_id-1] == '<')) { 
	cout << "PANIC" << endl; 
		cout << k << endl;
		cout << kp_id << endl;
		cout << "p " << p[kp_id] << endl;
		FOR(i,0,R+2) cout << p[i];
		cout << endl;
		exit(1);
	}
	
	vector<char> key;
	if (kp_id >= R+2-C) {
		FOR(i,kp_id,R+2) key.push_back(p[i]);
		//if (cached.second > 0) {
		if (mem.find(mp(kp_id,mp(k,mp(key.size(),key)))) != mem.end()) {
			pair<vector<char>,ll> cached = mem[mp(kp_id,mp(k,mp(key.size(),key)))];
			ll cfsz = cached.first.size();
			FOR(i,0,cfsz) p[R+2-cfsz+i] = cached.first[i];
			return cached.second;
		}
	}
	
	vector<char> buttons;
	bool goes_up = false, goes_down = false;
	FOR(_,column(kp_id,p[kp_id]),column(kp_id,k)) buttons.push_back('>');
	FOR(_,row(kp_id,k),row(kp_id,p[kp_id])) {buttons.push_back('^'); goes_up = true;}
	FOR(_,row(kp_id,p[kp_id]),row(kp_id,k)) buttons.push_back('v'), goes_down = true;
	FOR(_,column(kp_id,k),column(kp_id,p[kp_id])) buttons.push_back('<');
	buttons.push_back('A');
	ll v = 0;
	{
		char p_tmp[R+2]; FOR(i,0,R+2) p_tmp[i] = p[i];
		FORIT(b,buttons) {v += simulate_typing(kp_id+1, *b, p); p[kp_id] = next(kp_id, p[kp_id], *b);}
		char p_tmptmp[R+2]; FOR(i,0,R+2) p_tmptmp[i] = p[i];
		FOR(i,0,R+2) p[i] = p_tmp[i];
		//cout << "Y" << endl;
		if (goes_up && p[kp_id] != '<' && (kp_id != 0 || kp_id == 0 && (row(0,p[0]) != 3 || column(0,k) >= 1)) 
			|| goes_down && (kp_id == 0 || kp_id != 0 && (column(kp_id,k)>=1)) && (kp_id != 0 || kp_id == 0 && (row(0,k) != 3 || column(0,p[0]) >= 1))) {
			buttons.pop_back();
			reverse(buttons.begin(), buttons.end());
			buttons.push_back('A');
			ll x = 0;
			//cout << kp_id+1 << endl;
			//cout << p[kp_id+1] << endl;
			//cout << "X" << " " << kp_id << endl;
			//cout << goes_up << " " << goes_down << endl;
			FORIT(b,buttons) {
			//	cout << "---------------" << endl;
			//	cout << "-- " << p[kp_id] << endl;
			//	cout << "-- " << *b << endl;
				x += simulate_typing(kp_id+1, *b, p);
				p[kp_id] = next(kp_id, p[kp_id], *b);
			//	cout << "-- " << p[kp_id] << endl;
			}
			if (x < v) {
				v = x;
			} else {
				FOR(i,0,R+2) p[i] = p_tmptmp[i];
			}
		} else {
			FOR(i,0,R+2) p[i] = p_tmptmp[i];
		}
	}
	if (p[kp_id] != k){
		cout << k << endl;
		cout << kp_id << endl;
		cout << "p " << p[kp_id] << endl;
		FOR(i,0,R+2) cout << p[i];
		cout << endl;
		cout << ":(" << endl;
		exit(1);
	}
	p[kp_id] = k;
	if (kp_id >= R+2-C) {
		vector<char> vs;
		FOR(i,kp_id,R+2) vs.push_back(p[i]);
		mem[mp(kp_id,mp(k,mp(key.size(),key)))] = mp(vs,v);
	}
	return v;
}

// 280641530069632
// 206126505083994
// 10872618386829721
char next(char c, char r) {
	/*switch (r) {
	case '^': return num_kp[row(kp_id,c)-1][column(kp_id,c)];
	case '>': return num_kp[row(kp_id,c)][column(kp_id,c)+1];
	case 'v': return num_kp[row(kp_id,c)+1][column(kp_id,c)];
	case '<': return num_kp[row(kp_id,c)][column(kp_id,c)-1];
	case 'A': return c;
	default: __assume(false);
	}*/
	return 0;
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
	char p[R+2];
	FOR(i,0,R+2-1) p[i] = 'A';
	p[R+2-1] = '\0';
	FOR(i,0,4) {
		w += simulate_typing(0, c[i], p);
		cout << "DONE WITH ONE" << endl;
	}
	//mem.clear(); cout << "CLEARED" << endl;
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
// 293489329 too low
// 206126505083994 too low
// 206126505083994
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