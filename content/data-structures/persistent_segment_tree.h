const int N = 2e5 + 10;
const int M = 1e7 + 10;
typedef int T;

T arr[M];
int L[M], R[M], root[N];
size_t sz;
int nodes = 0, cnt = 0;
T val;
T (*f)(T, T);

void build(T a[], int v, int tl, int tr){
    if (tl == tr) arr[v] = a[tl];
    else{
        int tm = (tl + tr) / 2;
        build(a, L[v] = nodes++, tl, tm);
        build(a, R[v] = nodes++, tm+1, tr);
        arr[v] = f(arr[L[v]], arr[R[v]]);
    }
}
void PSEGtree(T a[], size_t n, T (*func)(T, T), T x){
    sz = n, f = func, val = x;
    build(a, root[cnt++] = nodes++, 0, sz-1);
}
void reset(){ nodes = cnt = 0; }

T query(int v, int l, int r, int tl, int tr){
    if (l > tr || r < tl) return val;
    if (l <= tl && r >= tr) return arr[v];
    int tm = (tl + tr) / 2;
    return f(query(L[v], l, r, tl, tm),
            query(R[v], l, r, tm+1, tr));
}
T query(int l, int r, int rt){
    return query(root[rt], l, r, 0, sz-1);
}

void update(int cur, int prev, int pos, T x, int tl, int tr){
    if (tl == tr) return void(arr[cur] = x);
    int tm = (tl + tr) / 2;
    if (pos <= tm){
      R[cur] = R[prev], L[cur] = nodes++;
      update(L[cur], L[prev], pos, x, tl, tm);
    }
    else{
      L[cur] = L[prev], R[cur] = nodes++;
      update(R[cur], R[prev], pos, x, tm+1, tr);
    }
    arr[cur] = f(arr[L[cur]], arr[R[cur]]);
}
int update(int pos, T x, int rt = -1){
  if (rt < 0) rt = cnt-1;
  update(root[cnt] = nodes++, root[rt], pos, x, 0, sz-1);
  return cnt++;
}
