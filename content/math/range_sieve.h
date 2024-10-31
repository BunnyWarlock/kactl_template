void sieveRange(ll l, ll r){
  rangePrime.set();
  for (int i: p) // p is a vector of primes
    for (ll j = max(i*1LL*i, (l+i-1)/ i*1LL*i); j <= r; j += i)
      rangePrime[j-l]= false;
  if (l == 1) rangePrime[0] = false;

  // Problem Specific. Can Ignore.
  for (int i = 0; i < r-l+1; ++i)
    if (rangePrime[i]) cout<<i+l<<endl;
  cout<<endl;
}
