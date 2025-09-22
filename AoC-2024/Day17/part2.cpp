/*ll combo(ll v) {
	switch (v) {
	case 0:
	case 1:
	case 2:
	case 3: return v;
	case 4: return A;
	case 5: return B;
	case 6: return C;
	case 7: 
	default: __assume(false);
	}
}

vector<ll> execute_program() {
	vector<ll> output;
	ll pc = 0;
	while (pc < n-1) {
		ll opcode = p[pc];
		ll operand = p[pc+1];
		switch (opcode) {
		case 0: A >>= combo(operand); break;
		case 1: B ^= operand; break;
		case 2: B = combo(operand)&7; break;
		case 3: if (A) { pc = operand; continue; } break;
		case 4: B ^= C; break;
		case 5: output.push_back(combo(operand)&7); break;
		case 6: B = A >> combo(operand); break;
		case 7: C = A >> combo(operand); break;
		default: __assume(false);
		}
		pc += 2;
	}
	return output;
}


B = A&7;
B ^= 7;
C = A >> B;
A >>= 3;
B ^= C;
B ^= 7;
cout << B&7;
if (A) goto 0;

<=>

B = ~A & 7;
C = A >> B;


0 ^ 0 = 0
1 ^ 0 = 1
2 ^ 0 = 2
...
1 ^ 1 = 0
2 ^ 1 = 3
3 ^ 1 = 2
4 ^ 1 = 5
5 ^ 1 = 4
6 ^ 1 = 7
7 ^ 1 = 6

3 ^ 5 = 6


(8-((8-A) % 8 ^ (A >> (8-A)%8) % 8)) % 8


<< ~((~A & 7) ^ (A >> (~A & 7))) & 7


set<ll> possible_initial_values(ll d) {
	ps = possible_initial_values(d+1);
	nps = {}
	FOR(poa,ps) {
		poa <<= 3
		FOR(i,0,7) {
			pob = poa+i;
			p[d] = ~((~pob & 7) ^ (pob >> (~pob & 7))) & 7
			if true then
				nps.add(pob)
		}
	}
	return nps
}

set<ll> possible[n+1];
possible[n] = 0
ROF(d,n,0) {
	FORIT(pos,possible[d+1]) {
		FOR(v,0,8) {
			pob = pois << 3 + i;
			if (~((~pob & 7) ^ (pob >> (~pob & 7))) & 7 == p[d]) {
				possible[d].add(pob);
			}
		}
	}
}


<=> 2 = ~((~A & 7) ^ (A >> (~A & 7))) & 7

<< ((~A & 7) & (A >> (~A & 7)) & 7) | (A&7 & (~A >> (~A&7)) & 7)


A >>= 3;
*/

#include <iostream>
#include <set>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define ROF(i,a,b) for (ll i = (a); i >= (b); i--)
#define FORIT(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
	
const ll n = 16;
ll p[n];

set<ll> cs[n+1];
ll lowest_initial_value() {
	FOR(i,0,n+1) cs[i] = set<ll>{};//.clear();
	cs[n].insert(0);
	ROF(d,n-1,0) {
		FORIT(c,cs[d+1]) {
			FOR(i,0,(d==n-1)?1024:8) { // 1024? 2^8?
				//cout << "A" << endl;
				ll A = (*c << 3) + i;
				//cout << "b" << endl;
				if ((~((~A & 7) ^ (A >> (~A & 7))) & 7) == p[d]) {
					cs[d].insert(A);
				}
				//cout << "c" << endl;
			}
		}
		
	}
	if (!cs[0].size()) {
		cout << "ERR" << endl;
		return -1;
	}
	return *cs[0].begin();
}

void read_registers() {
	cin.ignore(1024, '\n');
	cin.ignore(1024, '\n');
	cin.ignore(1024, '\n');
}
void read_program() {
	string _, program;
	cin >> _ >> program;
	FOR(i,0,n) p[i] = program[2*i]-'0';
}

void main() {
	read_registers();
	read_program();
	
	cout << lowest_initial_value();
}
