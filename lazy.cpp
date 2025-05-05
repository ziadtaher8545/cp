
class seg_tree {
    private:
        struct node {
            int val = 0, lazy = 0;
            bool islazy = 0;
            node(int v = 0) {
                val = v;
                lazy = 0;
                islazy = false;
            }
            void update(int v, int lx, int rx) {
    
                val += v * (rx - lx + 1);
                lazy += v;
                islazy = true;
    
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
            return node(l.val + r.val);
        }
        void propagate(int nd, int lx, int rx) {
            if (rx - lx == 0 || !seg[nd].islazy)return;
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
            if (lx > r || rx < l)return;
            int mid = (lx + rx) / 2;
            update(val, lx, mid, 2 * nd + 1, l, r);
            update(val, mid + 1, rx, 2 * nd + 2, l, r);
            seg[nd] = merge(seg[2 * nd + 1], seg[2 * nd + 2]);
    
        }
        node get(int lx, int rx, int nd, int l, int r) {
            propagate(nd, lx, rx);
            if (l <= lx && rx <= r)return seg[nd];
            if (lx > r || rx < l)return node();
            int mid = (lx + rx) / 2;
            node left = get(lx, mid, 2 * nd + 1, l, r);
            node right = get(mid + 1, rx, 2 * nd + 2, l, r);
            return merge(left, right);
        }
    public:
        void build(vector<int>& v) {
            build(v, 0, sze - 1, 0);
        }
        int get(int l, int r) {
            return get(0, sze - 1, 0, l, r).val;
        }
        void update(int val, int l, int r) {
            update(val, 0, sze - 1, 0, l, r);
        }
    };
