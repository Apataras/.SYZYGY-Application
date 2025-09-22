#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <vector>
//#include <ranges>
#include <sstream>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (decltype(a) i = (a); i < (b); ++i)
#define FORIT(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define all(c) (c).begin(), (c).end()



std::string join(const std::set<std::string>& set, const std::string& delimiter) {
    std::ostringstream oss;
    for (auto it = set.begin(); it != set.end(); ++it) {
        if (it != set.begin()) {
            oss << delimiter; // Add delimiter between elements
        }
        oss << *it;
    }
    return oss.str();
}


const ll n = 3380;
string cons[n][2];

bool starts_with_t(string s) {
	return s[0] == 't';
}
map<string,map<string,bool>> mat;
set<set<string>> cliques_of_size_n(set<set<string>> cliques_n_m_1, ll n) {
	set<set<string>> result;
	for (auto it1 = cliques_n_m_1.begin(); it1 != cliques_n_m_1.end(); ++it1) {
		/*bool has_t = false;
		FORIT(c,*it1) if (starts_with_t(*c)) has_t = true;
		if (!has_t) continue;*/
        for (auto it2 = std::next(it1); it2 != cliques_n_m_1.end(); ++it2) {
            set<string> cliq;
			cliq.insert(it1->begin(), it1->end());
			cliq.insert(it2->begin(), it2->end());
			if (cliq.size() != n) continue;
			bool toAll = true;
			FORIT(v,*it1) FORIT(v2,*it2) if (*v!=*v2) {
				toAll &= mat[*v][*v2];
			}
			if (!toAll) continue;
			result.insert(cliq);
        }
    }
	return result;
}
// Tried am,bc,cz,dc,gy,hk,li,qf,th,tj,wf,xk
string password() {
	cout << "Password..." << endl;
	set<string> cps;
	FOR(i,0,n) cps.insert({cons[i][0],cons[i][1]});
	FORIT(cp,cps) {
		cout << *cp << " ";
	}
	cout << endl;
	set<string> tcps;
	FORIT(cp,cps) if (starts_with_t(*cp)) tcps.insert(*cp);
	
	map<string,set<string>> edges;
	FOR(i,0,n) edges[cons[i][0]].insert(cons[i][1]), edges[cons[i][1]].insert(cons[i][0]);
	bool all_sz_13 = true; // no edges ohhhhh clique size 14
	FORIT(cp,cps) all_sz_13 &= edges[*cp].size() == 13;
	cout << "Checking all sz 13? " << all_sz_13 << endl;
	FORIT(cp,cps) edges[*cp].insert(*cp);
	
	ll cs = 3;
	set<string> max_clique;
	while (1) {
		cout << "Trying cliques of size" << cs << endl;
		bool acf = false;
		bool anyfaf = false;
		FORIT(tcp,tcps) {
			int limit = 1 << 14;
			int combination = (1 << cs) - 1;
			vector<string> vtcp;
			FORIT(s,edges[*tcp]) vtcp.push_back(*s);
			bool br = false;
			while (combination < limit) {
				//cout << combination << endl;
				set<string> pc;
				FOR(i,0,14) if (combination & 1<<i) pc.insert(vtcp[i]);
				bool cf = true; 
				FORIT(c,pc) {
					if (!includes(all(edges[*c]),all(pc))) {
						cf = false;
						break;
					}
				}
				if (cf) {
					/*if (acf) {
						// Already found one => multiple max cliques => next size
						acf = false;
						br = true;
						break;
					}*/
					acf = true;
					max_clique = pc;
					anyfaf = true;
					
					/*if (cs == 12) {
						cout << "UHHHH " << endl;
						FORIT(mc,max_clique) {
							cout << *mc << " --- ";
							FORIT(edga,edges[*mc]) cout << *edga << " ";
							cout << endl;
						}
						cout << endl;
					}*/
					br = true;
					break;
				}
				
				// Gosper's Hack: Generate the next combination with n bits set
				int x = combination & -combination;
				int y = combination + x;
				combination = ((combination & ~y) / x >> 1) | y;
			}
			if (br) break;
		}
		cout << "Found Any? " << anyfaf << endl;
		if (anyfaf/*!acf*/) { 
			cs++; // TODO maybe 13 -> 0 to be sure to get the max (3 < x <= 13)
		} else {
			
			break;
		}
	}
	return join(max_clique, ",");
}

string password2() {
	set<string> computers;
	map<string,set<string>> edges;
	FOR(i,0,n) {
		mat[cons[i][0]][cons[i][1]] = true;
		mat[cons[i][1]][cons[i][0]] = true;
		computers.insert(cons[i][0]);
		computers.insert(cons[i][1]);
		//edges[cons[i][0]]
	}
	/*while (1) {
		string c = *computers.begin();
		FOR(i,0,
	}*/
	
	
	if (true) return "PAASSSS";
	// Find max-clique. > 3
	set<set<string>> cliques_3;
	FOR(i,0,n-2) {
		FOR(j,i+1,n-1) {
			bool connected = false;
			if (cons[i][0] == cons[j][0]) {
				connected = mat[cons[i][1]][cons[j][1]];
			} else if (cons[i][0] == cons[j][1]) {
				connected = mat[cons[i][1]][cons[j][0]];
			} else if (cons[i][1] == cons[j][0]) {
				connected = mat[cons[i][0]][cons[j][1]];
			} else if (cons[i][1] == cons[j][1]) {
				connected = mat[cons[i][0]][cons[j][0]];
			}
			if (!connected) continue;
			cliques_3.insert({cons[i][0],cons[i][1],cons[j][0],cons[j][1]});
		}
	}
	cout << "#Cliques_of_size_3: " << cliques_3.size() << endl;
	set<set<string>> cliques = cliques_3;
	ll sz = 3;
	while (cliques.size()>1) {
		cliques = cliques_of_size_n(cliques,sz+1);
		sz++;
		cout << "#Cliques_of_size_" << sz << ": " << cliques.size() << endl;
	}
	
	return "PW";
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

long long factorial(ll n) {
    long long result = 1;
    for (ll i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

long long nCr(ll n, ll r) {
    if (r > n) return 0; // nCr is 0 if r > n
    if (r > n - r) r = n - r; // Use symmetry property nCr = nC(n-r)
    return factorial(n) / (factorial(r) * factorial(n - r));
}
map<string,ll> d;
void read_cons() {
	
	FOR(i,0,n) {
		string con;
		cin >> con;
		cons[i][0] = con.substr(0,2);
		cons[i][1] = con.substr(3,2);
		/*cout << cons[i][0] << " -- " << cons[i][1] << endl;
		a.insert(cons[i][0]);
		a.insert(cons[i][1]);
		d[cons[i][0]]++;
		d[cons[i][1]]++;*/
	}
	if (true) {
		return;
	}
	set<string> a;
	// 520 computer
	// Every computer has 13 connections => clique of <= size 13 and > 3 and has to include computer starting with t
	ll mx = 0;
	ll c = 0;
	FORIT(xa,d) if (xa->second > mx) mx = xa->second, c = 1; else if (xa->second == mx) c++;
	cout << "MAX" << mx << " c " << c << endl;
	
	ll y = 0;
	FOR(i,0,26) FOR(j,0,26) if (i != j) y++;
	cout << y << endl;
	cout << a.size() << endl;
	// cout << cons[1][0] << "-" << cons[1][1] << endl;
	
	// Sum(k=4,k=13, 23*sum(L=1,L=k) L 
	ll z = 0;
	FORIT(ijaf,a) if (starts_with_t(*ijaf)) z++;
	cout << "ts :: " << z << endl;
	
	ll suma = 0;
	FOR(k,4,14) FOR(t,0,nCr(13,k)) FOR(L,1,k-1) suma += L;
	cout << suma << endl;
}

void main() {
	read_cons();
	
	cout << "---- PW ---- " << endl;
	cout << password();
}
