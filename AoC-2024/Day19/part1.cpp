#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;
#define FORIT(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)

vector<string> patterns;
vector<string> designs;

bool is_design_possible(string design) {
	set<ll> ris;
	ris.insert(0);
	while (1) {
		if (ris.size() == 0) return false;
		ll i = *ris.begin();
		if (i >= design.length()) break;
		FORIT(p,patterns) if (design.substr(i,p->length()) == *p) {
			ris.insert(i+p->length());
		}
		ris.erase(ris.begin());
	}
	return *ris.begin() == design.length();
}
ll no_possible_designs() {
	ll no = 0;
	FORIT(d,designs) no += is_design_possible(*d);
	return no;
}

// for string delimiter
std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

vector<string> read_patterns() {
	string patterns;
	getline(cin, patterns);
	
	std::vector<std::string> result = split(patterns, ", ");
	return result;
}
vector<string> read_designs() {
	vector<string> result;
	string s;
	while (cin >> s) result.push_back(s);
	return result;
}
void main() {
	patterns = read_patterns();
	designs = read_designs();
	
	cout << no_possible_designs();
}