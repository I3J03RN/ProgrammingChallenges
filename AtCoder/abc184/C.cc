// this line is here for a reason
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define fi first
#define se second
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define endl '\n'
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define SZ(x) (int)(x).size()
#define FOR(a, b, c) for (auto a = (b); (a) < (c); ++(a))
#define F0R(a, b) FOR (a, 0, (b))
template <typename T>
bool ckmin(T& a, const T& b) { return a > b ? a = b, true : false; }
template <typename T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, true : false; }
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout if (DEBUG) cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
  if (r1 == r2 && c1 == c2) {
    cout << 0 << endl;
    return 0;
  }
  auto one = [c = r2, d = c2](int a, int b) -> bool {
    return a + b == c + d || a - b == c - d || abs(a - c) + abs(b - d) <= 3;
  };
  if (one(r1, c1)) {
    cout << 1 << endl;
    return 0;
  }

  if (((r1 + c1) & 1) == ((r2 + c2) & 1)) {
    cout << 2 << endl;
    return 0;
  }

  for (int dr = -3; dr <= 3; ++dr) {
    for (int dc = -3; dc <= 3; ++dc) {
      if (abs(dr) + abs(dc) > 3) continue;
      if (one(r1 + dr, c1 + dc)) {
        cout << 2 << endl;
        return 0;
      }
    }
  }


  cout << 3 << endl;
  
  return 0;
}
