const int MAX = 1e5 + 10;
vector<vector<int>> g;
int sz[MAX], pc[MAX];
bitset<MAX> dead;

void dfs(int v, int p = -1){
    sz[v] = 1;
    for (int u: g[v])
        if (u != p && !dead[u]){
            dfs(u, v);
            sz[v] += sz[u];
        }
}

int findCentroid(int num, int v, int p = -1){
    for (int u: g[v])
        if (u != p && !dead[u] && 2*sz[u] > num)
            return findCentroid(num, u, v);
    return v;
}

void decompose(int v, int p = -1){
    dfs(v);
    int cent = findCentroid(sz[v], v);
    pc[cent] = p;
    dead[cent] = true;
    for (int u: g[cent])
        if (!dead[u])
            decompose(u, cent);
}
