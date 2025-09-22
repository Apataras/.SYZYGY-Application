#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

ll A,B,C;
const ll n = 16;
ll p[n];

void print_output(vector<ll> output) {
	FOR(i,0,output.size()) {
		cout << output[i];
		if (i < output.size()-1) cout << ',';
	}
}

ll combo(ll v) {
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

void read_registers() {
	string reg, name;
	cin >> reg >> name >> A;
	cin >> reg >> name >> B;
	cin >> reg >> name >> C;
}
void read_program() {
	string program, line;
	cin >> program >> line;
	FOR(i,0,n) p[i] = line[2*i]-'0';
}

void main() {
	read_registers();
	read_program();
	
	auto output = execute_program();
	
	print_output(output);
}