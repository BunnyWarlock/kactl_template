/**
 * Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Input should be a vector of (dest, global edge index), where
 * for undirected graphs, forward/backward edges have the same index.
 * Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 * empty list if no cycle/path exists.
 * To get edge indices back, add .second to s and ret.
 * Time: O(V + E)
 * Status: stress-tested
 */


const int MAX = 1010;
const int LOG = 10;
vector<int> g[MAX];
int parent[MAX][LOG], depth[MAX], k; // k = 33 - __builtin_clz(n);

void dfs(int s, int p = 0){
  parent[s][0] = p;
  for (int i = 1; i < k; ++i)
    parent[s][i] = parent[parent[s][i-1]][i-1];

  for (auto& x: g[s])
    if (x != p){
      depth[x] = depth[s]+1;
      dfs(x, s);
    }
}

int jump(int n, int x){
  for (int i = 0; i < k; ++i)
    if ((x>>i)&1) n = parent[n][i];
  return n;
}

int lca(int a, int b){
  if (depth[a] < depth[b]) swap(a, b);
	a = jump(a, depth[a] - depth[b]);
	if (a == b) return a;
  for (int i = k-1; i >= 0; --i){
    int c = parent[a][i], d = parent[b][i];
    if (c != d) a = c, b = d;
  }
  return parent[a][0];
}
