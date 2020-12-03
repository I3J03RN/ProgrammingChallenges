template<typename F>
vector<string> input(F f) {
  vector<string> ss;
  for (string s; getline(cin, s); ss.pb(s)) {
    stringstream inp(s);
    f(inp);
  }
  return ss;
}


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  @
  
  return 0;
}
