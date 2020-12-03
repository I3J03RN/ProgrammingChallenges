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

  int n, y;
  char c;

  scanf("%d %c%d", &n, &c, &y);

  int x = c - 'a' + 1;

  int sX = x;
  int sY = y;

  cout << "queen\n";

  while(y <= n) {
    cout << (char)('a' + x - 1) << y++ << ' ';
  }


  y = sY - 1;
  while(y > 0) {
    cout << (char)('a' + x - 1) << y-- << ' ';
  }
  y++;

  x = 1;
  int dir = 1;
  while(x <= n) {
    if(x != sX) {
      while(y > 0 && y <= n) {
        cout << (char)('a' + x - 1) << y << ' ';
        y += dir;
      }
      y -= dir;
      dir *= -1;
    }
    x++;
  }
  cout << endl;
}
