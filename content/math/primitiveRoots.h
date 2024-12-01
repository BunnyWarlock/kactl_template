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

int generator(int p){
    vector<int> fact;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1) fact.push_back(n);

    for (int res = 2; res <= p; ++res){
        bool ok = true;
        for (int i = 0; i < fact.size() && ok; ++i)
            ok &= powMod(res, phi / fact[i], p) != 1;
        if (ok) return res;
    }
    return -1;
}

// j = 1;
// for (i = 0; i < P; ++i){
//     dlog[j] = i;
//     j = j * G % P;
// }
