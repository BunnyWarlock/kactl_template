typedef long long ll;
// Ideally blk should be pow(10, floor(log10(1e18/mod)))
ll strMod(string s, ll mod, int blk = 9) {
    ll x = 0, i, temp = pow(10, blk), n = s.size();
    for (i = 0; i < n; i += blk)
        x = (x*((i+blk<=n)?temp :(ll)pow(10, n-i)) +
            stoll(s.substr(i, blk))) % mod;
    return x;
}
