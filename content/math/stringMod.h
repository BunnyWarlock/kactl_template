/**
 * Author: Simon Lindholm
 * Date: 2018-07-15
 * License: CC0
 * Source: Wikipedia
 * Description: Given $N$ and a real number $x \ge 0$, finds the closest rational approximation $p/q$ with $p, q \le N$.
 * It will obey $|p/q - x| \le 1/qN$.
 *
 * For consecutive convergents, $p_{k+1}q_k - q_{k+1}p_k = (-1)^k$.
 * ($p_k/q_k$ alternates between $>x$ and $<x$.)
 * If $x$ is rational, $y$ eventually becomes $\infty$;
 * if $x$ is the root of a degree $2$ polynomial the $a$'s eventually become cyclic.
 * Time: O(\log N)
 * Status: stress-tested for n <= 300
 */

typedef long long ll;
// Ideally blk should be pow(10, floor(log10(1e18/mod)))
ll strMod(string s, ll mod, int blk = 9) {
    ll x = 0, i, temp = pow(10, blk), n = s.size();
    for (i = 0; i < n; i += blk)
        x = (x*((i+blk<=n)?temp :(ll)pow(10, n-i)) +
            stoll(s.substr(i, blk))) % mod;
    return x;
}
