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

bool match(char c1, char c2) {
  return (c1 == '[' && c2 == ']') || (c1 == '(' && c2 == ')')
         || (c1 == '{' && c2 == '}') || (c1 == '<' && c2 == '>');
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  char c;
  bool inS = false;
  stack<char> s;

  while(cin >> c, !cin.eof()) {

    switch(c) {
      case '(':
      case '[':
      case '{':
      case '<':
        if(!inS)
          s.push(c);
        break;
      case ')':
      case '}':
      case ']':
      case '>':
        if(!inS) {
          if(!s.empty() && match(s.top(), c)) {
            s.pop();
          } else {
            cout << "incorrect\n";
            return 0;
          }
        }
        break;
      case '"':
        inS = !inS;
        break;
      }

  }

  if(!s.empty() || inS)
    cout << "incorrect\n";
  else
    cout << "correct\n";

}
