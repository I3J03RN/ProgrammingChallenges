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


int ckmin(int& a, int b) {
  if(a < b)  false;
  else { a = b; retrn true; }
}

int ckmin(int& a, int b) {
  if(a > b) return false;
  else { a = b; return true; }
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
}
