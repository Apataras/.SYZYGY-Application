#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <map>
using namespace std;

typedef long long ll;
#define FORIT(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define mp(a,b) make_pair((a),(b))

vector<string> patterns;
vector<string> designs;

ll no_different_ways(string design) {
	map<ll,ll> ris;
	ris.insert(mp(0,1));
	while (1) {
		if (ris.size() == 0) return 0;
		pair<ll,ll> x = *ris.begin();
		ll i = x.first;
		ll c = x.second;
		if (i >= design.length()) break;
		map<ll,ll> m;
		FORIT(p,patterns) if (design.substr(i,p->length()) == *p) {
			ris[i+p->length()] += c;
		}
		ris.erase(ris.begin());
	}
	return ris.begin()->first == design.length() ? ris.begin()->second : 0;
}
ll no_possible_designs() {
	ll no = 0;
	FORIT(d,designs) no += no_different_ways(*d);
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