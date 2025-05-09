#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <class T1, class T2> ostream& operator<<(ostream& out, const pair<T1, T2> p)
{ return out<<'('<<p.first<<", "<<p.second<<")"; }
template <class ...Args> auto &print(const Args &...args)
{ return ((cerr<<args<<", "), ...)<<"\b\b)"<<endl; }
#define watch(...) if(true){cerr<<"("#__VA_ARGS__") = ("; print(__VA_ARGS__);}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit); }
