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
