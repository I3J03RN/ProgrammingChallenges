struct pps : vector<map<string, string>> {
  pps(vector<string> ss, const string& lsep = "", char csep = ':') {
    vector<string> ps = concatLines(ss, lsep);
    for (const string& s : ps) {
      push_back(parse(s, csep));
    }
  }
  vector<string> concatLines(const vector<string>& ss, const string& sep) {
    vector<string> ps;
    string s;
    F0R (i, SZ(ss)) {
      if (ss[i] == sep && s != "") {
        ps.pb(s);
        s = "";
      }
      s += " " + ss[i];
    }
    if (s != "") ps.pb(s);
    return ps;
  }
  map<string, string> parse(const string& s, char sep) {
    map<string, string> m;
    string k, v;
    int p = 0;
    F0R (i, SZ(s) + 1) {
      char c = i < SZ(s) ? s[i] : ' ';
      if (isspace(c)) {
        if (p) m[k] = v;
        p = 0;
        k = v = "";
      } else if (c == sep && p == 0) {
        ++p;
      } else {
        if (p) {
          v += c;
        } else {
          k += c;
        }
      }
    }
    return m;
  }
  template<typename F>
  int ck(F f) {
    int cnt = 0;
    for (const auto& m : (*this)) {
      cnt += f(m);
    }
    return cnt;
  }
};
