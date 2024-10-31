vector<int> pi(string& s) {
	vector<int> p(s.size());
	for(int i = 1, g; i < s.size(); ++i) {
		g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vector<int> match(string& txt, string& pat){
  vector<int> m, lps = pi(pat);
  int i = 0, j = 0;
  while(i < txt.size()){
    if (pat[j] == txt[i])
      ++j, ++i;
    if (j == pat.size()){
      m.push_back(i-j);
      j = lps[j-1];
    }
    if (i < txt.size() && pat[j] != txt[i]){
      if (j) j = lps[j-1];
      else ++i;
    }
  }
  return m;
}
