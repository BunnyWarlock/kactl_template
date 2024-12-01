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
static int C; // initialized below

// Arithmetic mod two primes and 2^32 simultaneously.
// "typedef uint64_t H;" instead if Thue-Morse does not apply.
template<int M, class B>
struct A {
	int x; B b; A(int x = 0): x(x), b(x) {}
	A(int x, B b): x(x), b(b) {}
	A operator+(A o){ int y = x+o.x; return{ y - (y>=M)*M, b+o.b }; }
	A operator-(A o){ int y = x-o.x; return{ y + (y< 0)*M, b-o.b }; }
	A operator*(A o) { return { (int)(1LL*x*o.x % M), b*o.b }; }
	explicit operator ull() { return x ^ (ull) b << 21; }
	bool operator==(A o) const { return (ull)*this == (ull)o; }
	bool operator<(A o) const { return (ull)*this < (ull)o; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;
// typedef A<1000000007, unsigned> H; // Use this for single hashing

vector<H> pw;
void updatePW(int s){
    while(pw.size() <= s)
        pw.push_back(pw.back() * C);
}

struct HashInterval {
	vector<H> ha;
    HashInterval(){}
	HashInterval(string& str) : ha(str.size()+1){
        updatePW(str.size());
		for (int i = 0; i < str.size(); ++i)
			ha[i+1] = ha[i] * C + str[i];
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

// Get hash of all substring in str of a specific length
vector<H> getHashes(string& str, int length) {
    updatePW(length);
	if (str.size() < length) return {};
	H h = 0;
	for (int i = 0; i < length; ++i)
		h = h * C + str[i];
	vector<H> ret = {h};
	for (int i = length; i < str.size(); ++i)
		ret.push_back(h = h * C + str[i] - pw[length] * str[i-length]);
	return ret;
}

H hashString(string& s){
	H h{};
	for(char c: s)
		h = h*C + c;
	return h;
}

void init(){
	timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	// assert((ull)(H(1)*2+1-3) == 0);

    pw.push_back(1);
}

H concatHash(H str1, H str2, int len2){
    updatePW(len2);
    return str1*pw[len2] + str2;
}

void pointUpdateHash(H& a, string& s, char c, int i){
    updatePW(s.size());
    a = a + pw[s.size()-1-i]*(c-s[i]);
}

vector<int> robinKarp(string text, string pattern){
	vector<int> ind;
	vector<H> hashes = getHashes(text, pattern.size());
	ull h = (ull)hashString(pattern);
	for (int i = 0; i < hashes.size(); ++i)
		if ((ull)hashes[i] == h)
			ind.push_back(i);
	return ind;
}

struct PalindromeHash{
    HashInterval f, r;
    int n;
    PalindromeHash(string str): f(str), n(str.size()){
        reverse(str.begin(), str.end());
        r = HashInterval(str);
    }
    H HashF(int a, int b){ return f.hashInterval(a, b); } // hash [a, b)
    H HashR(int a, int b){ return r.hashInterval(n-b, n-a); } // hash [a, b)
    bool isPalindrome(int a, int b){ // checks [a, b)
        return (ull)HashF(a, b) == (ull)HashR(a, b);
    }
};
