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
