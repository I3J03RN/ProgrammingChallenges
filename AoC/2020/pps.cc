struct pps : vector<map<string, string>> {
  pps(const vector<string>& ss, const string& lsep = "", char csep = ':') {
    map<string, string> cur;
    F0R (i, SZ(ss) + 1) {
      if (i == SZ(ss) || ss[i] == lsep) {
        if (not cur.empty()) pb(cur);
        cur.clear();
      }
      string k, v; int p = 0;
      F0R (j, SZ(ss[i]) + 1) {
        char c = j < SZ(ss[i]) ? ss[i][j] : ' ';
        if (isspace(c)) {
          if (p) cur[k] = v;
          p = 0;
          k = v = "";
        } else if (c == csep && p == 0) {
          ++p;
        } else {
          (p ? v : k) += c;
        }
      }
    }
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
