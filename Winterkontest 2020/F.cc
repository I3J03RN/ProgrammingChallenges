#include <bits/stdc++.h>
using namespace std;
#define FOR(a, b, c) for(auto (a) = (b); (a) < (c); ++(a))
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  FOR(j, 0, n) {
    int i;
    cin >> i;
    k += i;
  }

  cout << min(n, k - 1) << endl;
}
