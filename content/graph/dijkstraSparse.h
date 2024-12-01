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

vector<vector<pair<int, int>>> adj;

template <class T>
void dijkstra(int s, vector<T>& d, vector<int>& p) {
    d.assign(adj.size(), numeric_limits<T>::max());
    p.assign(adj.size(), -1);
    d[s] = 0;
    using P = pair<T, int>;
    priority_queue<P, vector<P>, greater<P>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [cost, now] = q.top();
        q.pop();
        if (cost != d[now]) continue;
        for (auto [to, len]: adj[now])
            if (d[now] + len < d[to]){
                d[to] = d[now] + len;
                p[to] = now;
                q.push({d[to], to});
            }
    }
}

vector<int> path(int s, int t, vector<int>& p) {
    vector<int> path;
    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);
    reverse(path.begin(), path.end());
    return path;
}
