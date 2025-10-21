class PST {
    int n;
public:
    long long  merge(int a, int b) {
        return a + b;
    }
    struct node {
        long long  val{};
        node* left, * right;

        node() : left(nullptr), right(nullptr), val(0) {}

        node(int val) : val(val), left(nullptr), right(nullptr) {}

        node(node* l, node* r) {
            left = l;
            right = r;
            val = 0;
            if (left) val = merge(val, left->val);
            if (right) val = merge(val, right->val);
        }
        long long  merge(int a, int b) {
            return a + b;
        }
    };
    vector<node*> roots;

    node* build(int lx, int rx, vector<int>& a) {
        if (lx == rx) return new node(a[lx]);
        int mid = (lx + rx) >> 1;
        auto left = build(lx, mid, a);
        auto right = build(mid + 1, rx, a);
        return new node(left, right);
    }

    node* update(node* cur, int lx, int rx, int i, int x) {
        if (lx == rx) return new node(x);
        int mid = (lx + rx) >> 1;
        if (i <= mid)
            return new node(update(cur->left, lx, mid, i, x), cur->right);
        else
            return new node(cur->left, update(cur->right, mid + 1, rx, i, x));
    }

    long long query(node* cur, int lx, int rx, int l, int r) {
        if (lx > r || rx < l) return 0;
        if (l <= lx && rx <= r) return cur->val;
        int mid = (lx + rx) >> 1;
        return merge(query(cur->left, lx, mid, l, r), query(cur->right, mid + 1, rx, l, r));
    }

    PST(vector<int>& a) {
        n = a.size();
        roots.push_back(build(0, n - 1, a));
    }

    void update(int k, int i, int x) {
        roots[k] = update(roots[k], 0, n - 1, i, x);
    }

    long long query(int k, int l, int r) {
        return query(roots[k], 0, n - 1, l, r);
    }

    void makeCopy(int k) {
        roots.push_back(roots[k]);
    }
};
