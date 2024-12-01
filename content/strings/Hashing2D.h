/**
 * Author: Stjepan Glavina
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * Description: Finds the lexicographically smallest rotation of a string.
 * Time: O(N)
 * Usage:
 *  rotate(v.begin(), v.begin()+minRotation(v), v.end());
 * Status: Stress-tested
 */

typedef uint64_t ull;
static int C1, C2; // initialized below

// Place struct A from Hashing.h

void init(){
	timeval tp;
	gettimeofday(&tp, 0);
	C1 = (int)tp.tv_usec * 3731LL % 998244353;
	C2 = (int)tp.tv_usec * 2999LL % 998244353;
}

struct Hash2D{
    vector<vector<H>> hs;
    vector<H> p1, p2;
    int n, m;
    Hash2D(){}
    Hash2D(vector<string>& s){
        n = (int)s.size(), m = (int)s[0].size();
        p1.resize(m+1); p1[0] = 1;
        p2.resize(n+1); p2[0] = 1;
        for (int i = 1; i <= m; ++i) p1[i] = p1[i-1] * C1;
        for (int i = 1; i <= n; ++i) p2[i] = p2[i-1] * C2;

        hs.assign(n+1, vector<H>(m+1));
        for (int i = 0; i <= max(n, m); ++i)
            hs[min(n, i)][0] = hs[0][min(m, i)] = H();
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                hs[i][j] = hs[i][j-1]*C1 + hs[i-1][j]*C2 -
                           hs[i-1][j-1]*C1*C2 + s[i-1][j-1];
    }
    H getHash(int x1, int y1, int x2, int y2){
        // assert(x1 >= 0 && x1 <= x2 && x2 < n);
        // assert(y1 >= 0 && y1 <= y2 && y2 < m);
        int dx = x2-x1+1, dy = y2-y1+1;
        return hs[x2+1][y2+1] - hs[x2+1][y1]*p1[dy] -
               hs[x1][y2+1]*p2[dx] + hs[x1][y1]*p1[dy]*p2[dx];
    }
    H getHash(){ return getHash(0, 0, n-1, m-1); }
};
