class Sqrt_decomposition {
    vector<long long > v, bl;
    int sq, n;
public:
    Sqrt_decomposition(int n, vector<long long >& a) {
        v = a;
        sq = (int)sqrt(n) + 1;
        bl = vector<long long >(sq, 0);
        this->n = n;
        build();
    }

    void build() {
        for (int i = 0; i < n; i++) {
            bl[i / sq] += v[i];
        }
    }

    long long  query(int l, int r) {
        long long  ret = 0;
        for (int i = l; i <= r;) {
            if (i % sq == 0 && i + sq - 1 <= r) {
                ret += bl[i / sq];
                i += sq;
            }
            else {
                ret += v[i];
                i++;
            }
        }
        return ret;
    }

    void update(int idx, long long val) {
        bl[idx / sq] -= v[idx];
        v[idx] = val;
        bl[idx / sq] += v[idx];
    }
};
