const int N = 2e6 + 5;
vector<int>adj[N];
int up[N][25], dep[N];
void dfs_(int u = 1, int p = 0) {
    up[u][0] = p;
    for (int i = 1; i < 25; i++)
        up[u][i] = up[up[u][i - 1]][i - 1];
    for (auto& v : adj[u]) {
        if (v == p)continue;
        dep[v] = dep[u] + 1;
        dfs_(v, u);
    }
}
int kthAnc(int u, int k) {

    if (dep[u] < k)return -1;
    for (int i = 0; i < 25; i++) {
        if (k & (1 << i)) {
            u = up[u][i];

        }
    }
    return u;
}

int Lca(int u, int v) {
    if (dep[u] < dep[v])swap(u, v);
    u = kthAnc(u, dep[u] - dep[v]);
    if (u == v)return v;
    for (int i = 24; ~i; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }

    }
    return up[u][0];
}
