struct Manacher{
    array<vector<int>, 2> p;
    Manacher(const string& s) {
    	int n = s.size();
    	p = {vector<int>(n+1), vector<int>(n)};
    	for (int z = 0; z < 2; ++z)
            for (int i=0,l=0,r=0; i < n; i++) {
        		int t = r-i+!z;
        		if (i<r) p[z][i] = min(t, p[z][l+t]);
        		int L = i-p[z][i], R = i+p[z][i]-!z;
        		while (L>=1 && R+1<n && s[L-1] == s[R+1])
        			p[z][i]++, L--, R++;
        		if (R>r) l=L, r=R;
        	}
    }
    bool isPalindrome(int l, int r){ // [l, r]
        int len = r-l+1;
        return (p[len&1][(l+r+1)/2]*2 + 1 >= len);
    }
};
