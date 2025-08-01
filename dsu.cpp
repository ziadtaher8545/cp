class Dsu
{
private:
    vector<int> par, sze;

public:
    Dsu(int n)
    {
        par.resize(n + 10);
        iota(par.begin(), par.end(), 0);
        sze.resize(n + 10, 1);
    }
    int get_leader(int u)
    {
        if (par[u] == u)
            return u;
        return par[u] = get_leader(par[u]);
    }
    void merge(int u, int v)
    {
        u = get_leader(u);
        v = get_leader(v);
        if (u == v)
            return;
        if (sze[u] > sze[v])
            swap(u, v);
        par[u] = v;
        sze[v] += sze[u];
    }
    bool is_sleader(int u, int v)
    {
        return get_leader(u) == get_leader(v);
    }
};
