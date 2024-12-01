/**
 * Author: Simon Lindholm
 * Date: 2020-10-12
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Misra_%26_Gries_edge_coloring_algorithm
 * https://codeforces.com/blog/entry/75431 for the note about bipartite graphs.
 * Description: Given a simple, undirected graph with max degree $D$, computes a
 * $(D + 1)$-coloring of the edges such that no neighboring edges share a color.
 * ($D$-coloring is NP-hard, but can be done for bipartite graphs by repeated matchings of
 * max-degree nodes.)
 * Time: O(NM)
 * Status: stress-tested, tested on kattis:gamescheduling
 */

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
