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

// For a^x = b(mod m) calculates x
int64_t discrete_log(int64_t a, int64_t b, int64_t m){
    a %= m, b %= m;
    int64_t k = 1, add = 0, g, i, n, e, cur;

    for (g = __gcd(a, m); g > 1; g = __gcd(a, m)){
        if (b == k)
            return add;
        if (b % g)
            return -1;
        b /= g, m /= g, ++add;
        k = (k * a / g) % m;
    }

    n = ceil(sqrt(1.0 * m));
    e = 1;
    unordered_map<int64_t, int64_t> vals;
    for (i = 0; i < n; ++i){
        vals[(e * b) % m] = i;
        e = (e * a) % m;
    }

    for (i = 1, cur = k; i <= n; ++i) {
        cur = (cur * e) % m;
        if (vals.count(cur))
            return n * i - vals[cur] + add;
    }
    return -1;
}
