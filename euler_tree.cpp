int timer = 0;
    vector<int>tin(n + 1), tout(n + 1);
    function<void(int, int)>dfs = [&] (int u, int p) {
        tin[u] = ++timer;
        for (auto v : adj[u])
            if (p != v)
                dfs(v, u);

        tout[u] = timer;

    };
    dfs(1, 0);
