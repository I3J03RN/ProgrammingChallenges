#include <bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(auto (a) = (b); (a) < (c); ++(a))
#define F0R(a, b) for(auto (a) = 0; (a) < (b); ++(a))
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (x).size()
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define fst(x) get<0>((x))
#define snd(x) get<1>((x))
#define thd(x) get<2>((x))
#define fs first
#define se second


int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n;
  cin >> n;

  string out = "a";
  out.reserve(n);

  char next = 'b';
  list<pair<char, int>> l = {mp('a', 1)};

  for (int i = 2; i <= n; ++i) {
    int cnt = 1;
    bool found = false;
    for (auto it = l.begin(); it != l.end(); ++it) {
      cout << "? " << (*it).se << " " << i << endl;
      fflush(stdout);
      int k;
      cin >> k;
      if (k == cnt) {
        out.pb((*it).fs);
        l.erase(it);
        l.push_front(mp(out.back(), i));
        found = true;
        break;
      }
      cnt++;
    }
    if (!found) {
      out.pb(next++);
      l.push_front(mp(out.back(), i));
    }
  }
  cout << "! " << out << endl;
}
