class seg_tree {
private:
    struct node {
        int val;
        node(int v = 1e18) {

            val = v;
        }
        void change(int v) {

            val = v;
        }
    };
    int sze;
    vector<node>seg;
public:
    seg_tree(int si) {
        sze = 1;
        while (sze < si) sze <<= 1;
        seg.assign(2 * sze, node());
    }
private:
    void build(vector<int>& v, int lx, int rx, int nd) {
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
    node merge(node& l, node& r) {
        return node(min(l.val, r.val));
    }
    void update(int i, int val, int lx, int rx, int nd) {
        if (rx - lx == 0) {
            seg[nd].change(val);
            return;
        }
        int mid = (lx + rx) / 2;
        if (i <= mid)update(i, val, lx, mid, 2 * nd + 1);
        else update(i, val, mid + 1, rx, 2 * nd + 2);

        seg[nd] = merge(seg[2 * nd + 1], seg[2 * nd + 2]);
    }
    node get(int lx, int rx, int nd, int l, int r) {
        if (l <= lx && rx <= r)return seg[nd];
        if (lx > r || rx < l)return node();
        int mid = (lx + rx) / 2;
        node left = get(lx, mid, 2 * nd + 1, l, r);
        node right = get(mid + 1, rx, 2 * nd + 2, l, r);
        return merge(left, right);
    }
    int search(int lx, int rx, int nd, int ix) {
        if (rx - lx == 0)return (ix ? 0 : lx);
        int mid = (lx + rx) / 2;
        if (seg[2 * nd + 1].val > ix) {
            return search(lx, mid, 2 * nd + 1, ix);
        }
        else {
            return search(mid + 1, rx, 2 * nd + 2, ix - seg[2 * nd + 1].val);
        }
    }
public:
    void build(vector<int>& v) {
        build(v, 0, sze - 1, 0);
    }
    int get(int l, int r) {
        return get(0, sze - 1, 0, l, r).val;
    }
    void update(int i, int val) {
        update(i, val, 0, sze - 1, 0);
    }
    int search(int ix) {
        return search(0, sze - 1, 0, ix);
    }
};
