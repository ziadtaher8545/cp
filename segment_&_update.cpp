class seg_tree
{
public:
    static const int  mod1 = 1e9 + 7, mod2 = 2e9 + 7, base1 = 211, base2 = 223;
    static vector<int> pw1, pw2, psum1, psum2;

    struct node
    {
        int len = 0, lazy = 0;
        pair<int, int>pre, suf;

        bool islazy = 0;
        node(int v = 0) {
            pre = suf = {v, v};
            lazy = 0;
            islazy = false;
            len = v > 0;
        }
        void update(int v, int lx, int rx) {

            lazy = v;
            islazy = true;
            len = rx - lx + 1;
            pre = suf = {(psum1[len - 1] % mod1 * v % mod1) % mod1, (psum2[len - 1] % mod2 * v % mod2) % mod2};
        }
    };
    int sze;
    vector<node> seg;

public:
    seg_tree() {}
    seg_tree(int si, string& s) {
        sze = 1;
        while (sze < si)
            sze <<= 1;
        seg.assign(2 * sze, node());
        while (pw1.size() <= si)
            pw1.push_back(0), pw2.push_back(0), psum1.push_back(0), psum2.push_back(0);
        pw1[0] = pw2[0] = 1;
        psum1[0] = psum2[0] = 1;
        for (int i = 1; i <= s.size(); i++) {
            pw1[i] = (base1 * pw1[i - 1]) % mod1;
            pw2[i] = (base2 * pw2[i - 1]) % mod2;
            psum1[i] = pw1[i];
            psum2[i] = pw2[i];
        }
        for (int i = 1; i <= s.size(); i++) {
            psum1[i] += psum1[i - 1];
            psum1[i] %= mod1;
            psum2[i] += psum2[i - 1];
            psum2[i] %= mod2;
        }


        build(s, 0, sze - 1, 0);
    }

private:
    pair<int, int> merge(pair<int, int> h1, pair<int, int> h2, int l2) {
        pair<int, int> ret;
        ret.first = ((h1.first % mod1 * pw1[l2] % mod1) % mod1 + h2.first % mod1) % mod1;
        ret.second = ((h1.second % mod2 * pw2[l2] % mod2) % mod2 + h2.second % mod2) % mod2;
        return ret;
    }
    node merge(node& l, node& r) {
        node ret = node();
        ret.pre = merge(l.pre, r.pre, r.len);
        ret.suf = merge(r.suf, l.suf, l.len);
        ret.len = l.len + r.len;
        return ret;
    }
    void build(string& v, int lx, int rx, int nd) {
        if (rx - lx == 0) {
            if (lx < v.size())
                seg[nd] = node(v[lx]);
            return;
        }
        int mid = (lx + rx) / 2;
        build(v, lx, mid, 2 * nd + 1);
        build(v, mid + 1, rx, 2 * nd + 2);
        seg[nd] = merge(seg[2 * nd + 1], seg[2 * nd + 2]);
    }
    void propagate(int nd, int lx, int rx) {
        if (rx - lx == 0 || !seg[nd].islazy)
            return;
        int lef = 2 * nd + 1, rig = 2 * nd + 2, mid = (lx + rx) / 2;
        seg[lef].update(seg[nd].lazy, lx, mid);
        seg[rig].update(seg[nd].lazy, mid + 1, rx);
        seg[nd].lazy = seg[nd].islazy = 0;
    }
    void update(int val, int lx, int rx, int nd, int l, int r) {
        propagate(nd, lx, rx);
        if (l <= lx && rx <= r) {
            seg[nd].update(val, lx, rx);
            return;
        }
        if (lx > r || rx < l)
            return;
        int mid = (lx + rx) / 2;
        update(val, lx, mid, 2 * nd + 1, l, r);
        update(val, mid + 1, rx, 2 * nd + 2, l, r);
        seg[nd] = merge(seg[2 * nd + 1], seg[2 * nd + 2]);
    }
    node get(int lx, int rx, int nd, int l, int r) {
        propagate(nd, lx, rx);
        if (l <= lx && rx <= r)
            return seg[nd];
        if (lx > r || rx < l)
            return node();
        int mid = (lx + rx) / 2;
        node left = get(lx, mid, 2 * nd + 1, l, r);
        node right = get(mid + 1, rx, 2 * nd + 2, l, r);
        return merge(left, right);
    }

public:
    auto get(int l, int r) {
        return get(0, sze - 1, 0, l, r);
    }
    void update(int val, int l, int r) {
        update(val, 0, sze - 1, 0, l, r);
    }
    bool is_palin(int l, int r) {
        return get(l, r).pre == get(l, r).suf;
    }
};
vector<int> seg_tree::pw1, seg_tree::pw2, seg_tree::psum1, seg_tree::psum2;

