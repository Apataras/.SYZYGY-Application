#include <iostream>
#include <map>
#include <set>
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
struct gate { string w1,op,w2,out;
	ll v1=-1,v2=-1;
} gate[m];


// (m nCr 2) nCr 4

// 6609724310168 too low
// 2nd try:
// 4336076702855 too low ups
ll output() {
	map<string,vector<ll>> neighs;
	FOR(i,0,n) FOR(j,0,m) if (wire[i].name == gate[j].w1 || wire[i].name == gate[j].w2) {
		neighs[wire[i].name].push_back(j);
	}
	FOR(i,0,m) FOR(j,0,m) if (gate[i].out == gate[j].w1 || gate[i].out == gate[j].w2) {
		neighs[gate[i].out].push_back(j);
	}
	//cout << "SZ" << endl;
	//cout << neighs["btr"].size() << endl;
	map<string,ll> ENDS;
	stack<pair<string,ll>> S;
	FOR(i,0,n) S.push(mp(wire[i].name,wire[i].v));
	vector<ll> satisfied;
	while (!S.empty()) {
		auto w = S.top(); S.pop();
		string name = w.first;
		ll v = w.second;
		//cout << "CURRENT: " << name << " --- " << v << endl;
		if (neighs.find(name) == neighs.end()) {
			cout << "SOMETHING ENDED: " << name << endl;
			ENDS[name] = v;
			continue;
		}
		FORIT(neigh_id,neighs[name]) {
			auto neigh = gate+*neigh_id;
			if (name == neigh->w1) {
				neigh->v1 = v;
			} else {
				neigh->v2 = v;
			}
			if (neigh->v1 == -1 || neigh->v2 == -1) continue;
			satisfied.push_back(*neigh_id);
			ll r;
			if (neigh->op == "AND") {
				r = neigh->v1 && neigh->v2;
			} else if (neigh->op == "OR") {
				r = neigh->v1 || neigh->v2;
			} else if (neigh->op == "XOR") {
				r = neigh->v1 ^ neigh->v2;
			} else {
				cout << "ERR" << endl;
				exit(1);
			}
			S.push(mp(neigh->out,r));
		}
	}
	cout << "UNSATISFIED:::::" << endl;
	set<ll> unsatisfied;
	FOR(i,0,m) unsatisfied.insert(i);
	FORIT(safa,satisfied) unsatisfied.erase(*safa);
	FORIT(xuxu,unsatisfied) cout << gate[*xuxu].w1 << " " << gate[*xuxu].op << " " << gate[*xuxu].w2 << " => " << gate[*xuxu].out << endl;
	set<string> SS;
	FORIT(xa,ENDS) SS.insert(xa->first);
	ll num = 0;
	ROFIT(xa,SS) {
		num <<= 1;
		num |= ENDS[*xa];
	}
	return num;
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
	}
	
	//FOR(i,0,m) cout << gate[i].w1 << " " << gate[i].op << " " << gate[i].w2 << " " << gate[i].out << endl;
}

void main() {
	read_input();
	read_gates();
	
	cout << output() << endl;
}
