#include <bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(auto (a) = (b); (a) < (c); ++(a))
#define F0R(a, b) for(auto (a) = 0; (a) < (b); ++(a))
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (x).size()
#define pb push_back
#define mp make_pair

void printAll(int n) {
  FOR(i, 1, n + 1)
    cout << i << ' ';
  cout << endl;
}

bitset<110> bs;
int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n, s, p;
  cin >> n >> s >> p;

  bs[p] = true;

  bool more1 = false;

  F0R(i, s) {
    int a, b;
    cin >> a >> b;

    if(a != -1 && b != -1) {
      bool tmp = bs[a];
      bs[a] = bs[b];
      bs[b] = tmp;
    } else if(a == -1 && b == -1) {
      printAll(n);
      return 0;
    } else if (a == -1) {
      if(bs[b]) {
        if(!more1) {
          bs.flip();
          continue;
        } else {
          printAll(n);
          return 0;
        }
      }
      bs[b] = 1;
      more1 = true;
    } else {
      if(bs[a]) {
        if(!more1) {
          bs.flip();
          continue;
        } else {
          printAll(n);
          return 0;
        }
      }
      bs[a] = 1;
      more1 = true;
    }
  }

  FOR(i, 1, n + 1)
    if(bs[i])
      cout << i << ' ';
  cout << endl;
}
