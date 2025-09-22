#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define FORIT(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
#define ROFIT(it,c) for (auto it = (c).rbegin(); it != (c).rend(); ++it)
#define mp(a,b) make_pair((a),(b))

const ll n = 90;
struct wire { string name; bool v; } wire[n];
const ll m = 222;
struct gate { ll i; string w1,op,w2,out; } gate[m];


ll output() {
	map<string,vector<ll>> neighs;
	FOR(i,0,n) FOR(j,0,m) if (wire[i].name == gate[j].w1 || wire[i].name == gate[j].w2) {
		neighs[wire[i].name].push_back(j);
	}
	FOR(i,0,m) FOR(j,0,m) if (gate[i].out == gate[j].w1 || gate[i].out == gate[j].w2) {
		neighs[gate[i].out].push_back(j);
	}
	map<string,ll> prev;
	FOR(i,0,45) {
		stringstream wtf;
		wtf << i;
		string zi = "z"+string((wtf.str().length()==1?"0":""))+wtf.str();
		FOR(j,0,m) if (gate[j].out == zi) prev[zi] = j;
	}
	
	// 45 * x
	// 45 * y
	set<pair<ll,string>> invalid;
	string c_i;
	FOR(i,0,n/2) {
		cout << i << endl;
		stringstream wtf;
		wtf << i;
		string xi = "x"+string((wtf.str().length()==1?"0":""))+wtf.str();
		string yi = "y"+string((wtf.str().length()==1?"0":""))+wtf.str();
		/*FORIT(xa,neighs[xi]) cout << *xa << " ";
		cout << endl;
		FORIT(ya,neighs[yi]) cout << *ya << " ";
		cout << endl;*/
		if (neighs[xi] != neighs[yi] || neighs[xi].size() != 2) {
			invalid.insert(mp(i,"First Case"));
			continue;
		}
		string xor_o;
		struct gate xor_g;
		string and_o;
		struct gate and_g;
		if (gate[neighs[xi][0]].op == "XOR" && gate[neighs[xi][1]].op == "AND") {
			xor_o = gate[neighs[xi][0]].out; xor_g = gate[neighs[xi][0]];
			and_o = gate[neighs[xi][1]].out; and_g = gate[neighs[xi][1]];
		} else if (gate[neighs[xi][1]].op == "XOR" && gate[neighs[xi][0]].op == "AND") {
			xor_o = gate[neighs[xi][1]].out; xor_g = gate[neighs[xi][1]];
			and_o = gate[neighs[xi][0]].out; and_g = gate[neighs[xi][0]];
		} else {
			invalid.insert(mp(i,"Second Case"));
			continue;
		}
		cout << "bl" << endl;
		if (i == 0) {
			if (xor_o != "z00") {
				invalid.insert(mp(i,"Third Case")); // Shouldn't happen, checked manually
				continue;
			}
			if (and_o[0] == 'z') {
				invalid.insert(mp(i,"Fourth Case"));
				continue;
			}
			c_i = and_o;
			continue;
		}
		
		string oc = c_i;
		
		cout << "DDDD " << endl;
		
		if (neighs[and_o].size() != 1 || gate[neighs[and_o][0]].op != "OR") {
			invalid.insert(mp(i,"Sixth Case"));
			continue;
		}
		
		c_i = gate[neighs[and_o][0]].out;
		
		cout << "I" << endl;
		string and_2;
		if (gate[neighs[and_o][0]].w1 == and_o) {
			and_2 = gate[neighs[and_o][0]].w2;
		} else if (gate[neighs[and_o][0]].w2 == and_o) {
			and_2 = gate[neighs[and_o][0]].w1;
		} else {
			invalid.insert(mp(i,"Eigth Case"));
			continue;
		}
		
		cout << "O:" << endl;
		
		if (neighs[oc].size() != 2) {
			invalid.insert(mp(i,"Ninth Case"));
			continue;
		}
		cout << ";)" << endl;
		struct gate xor_2g;
		struct gate and_2g;
		if (gate[neighs[oc][0]].op == "AND" && gate[neighs[oc][1]].op == "XOR") {
			and_2g = gate[neighs[oc][0]];
			xor_2g = gate[neighs[oc][1]];
		} else if (gate[neighs[oc][1]].op == "AND" && gate[neighs[oc][0]].op == "XOR") {
			and_2g = gate[neighs[oc][1]];
			xor_2g = gate[neighs[oc][0]];
		} else {
			invalid.insert(mp(i,"Tenth Case"));
			continue;
		}
		
		cout << "UFF" << endl;
		
		if (and_2g.out != and_2) {
			invalid.insert(mp(i,"Fifth Case"));
			continue;
		}
		
		//cout << "Q" << endl;
		//string xor_o2 = neighs[c_i][0];
		string zi = "z"+string((wtf.str().length()==1?"0":""))+wtf.str();
		cout << "zi"<<zi << endl;
		ll prv_gate = prev[zi];
		cout << "p " << prv_gate << endl;
		if (gate[prv_gate].op != "XOR") {
			stringstream ufa;
			ufa << gate[prv_gate].i << endl;
			invalid.insert(mp(i,"Seventh Case - Counterpart at "));
			continue;
		}
		
		if (xor_2g.i != gate[prv_gate].i) {
			invalid.insert(mp(i,"Eleventh Case"));
			continue;
		}
		
		if (neighs[xor_o]!=neighs[oc]) {
			invalid.insert(mp(i,"Twelth Case"));
			continue;
		}
	}		
	cout << "Invalids ---" << endl;
	FORIT(x,invalid) cout << x->first << ": " << x->second << endl;
	return -1;
}

void read_input() {
	FOR(i,0,n) {
		string s;
		cin >> s >> wire[i].v;
		wire[i].name = s.substr(0,s.length()-1);
	}
	
	//FOR(i,0,n) cout << wire[i].name << " " << wire[i].v << endl;
}

void read_gates() {
	FOR(i,0,m) {
		string arrow;
		cin >> gate[i].w1 >> gate[i].op >> gate[i].w2 >> arrow >> gate[i].out;
		gate[i].i = i;
	}
	
	map<string,ll> coniof;
	FOR(i,0,m) coniof[gate[i].op]++;
	FORIT(x,coniof) cout << x->first << ": " << x->second << endl;
	//FOR(i,0,m) cout << gate[i].w1 << " " << gate[i].op << " " << gate[i].w2 << " " << gate[i].out << endl;
}

void main() {
	read_input();
	read_gates();
	
	cout << output() << endl;
}
