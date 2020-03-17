#include <bits/stdc++.h>
using namespace std;
#define FOR(a, b, c) for(auto (a) = (b); (a) < (c); ++(a))
#define F0R(a, b) for(auto (a) = 0; (a) < (b); ++(a))
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
#define ALL(x) (x).begin(), (x).end()


int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int tc;
  cin >> tc;

  long double s = 0;
  FOR(i, 0, tc) {
    int n;
    cin >> n;

    s += 1.0/n;
  }

  cout << fixed << setprecision(9) << tc/s << endl;
}
