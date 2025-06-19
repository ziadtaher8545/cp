#include <bits/stdc++.h>
using namespace std;

#define el "\n"
#define int long long

/*   وَلَا تَيْأَسُوا مِن رَّوْحِ اللَّهِ ۖ إِنَّهُ لَا يَيْأَسُ مِن رَّوْحِ اللَّهِ إِلَّا الْقَوْمُ الْكَافِرُون   */
class MO {

    struct query {
        int l, r, idx;
    };
    int sq;
    int n;
    vector<query>q;
    vector<long long >v;
    vector<int>frq;
    long long res = 0;

    void add(int ix) {
        int val = v[ix];
        res += val;
    }
    void remove(int ix) {
        int val = v[ix];
        res -= val;
    }
    int clc() {
        return res;
    }

public:
    MO(vector<long long >& a) {
        v = a;
        sq = sqrt(a.size());
        n = 0;
    }
    void add_query(int l, int r) {
        q.push_back({l, r, n++});
    }
    void process() {
        vector<int>ans(n);
        std::sort(q.begin(), q.end(), [&] (query& a, query& b) {
            if (a.l / sq != b.l / sq)
                return a.l / sq < b.l / sq;
            return ((a.l / sq) & 1 ? a.r<b.r : a.r>b.r);

        });
        int l = 0, r = -1;
        for (auto [lq, rq, ind] : q) {
            while (r < rq)add(++r);
            while (l > lq)add(--l);
            while (r > rq)remove(r--);
            while (l < lq)remove(l++);
            ans[ind] = clc();
        }
        for (auto it : ans) {
            cout << it << el;
        }
        for (int i = q.back().l; i <= q.back().r; i++) remove(i);
    }

};
void ziad()
{
}

signed main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    if (fopen("inp.txt", "r"))
    {
        freopen("inp.txt", "r", stdin);
        freopen("outp.txt", "w", stdout);
    }
    int testcase = 1;
    // cin >> testcase;
    for (int i = 1; i <= testcase; i++)
    {
        ziad();
    }
    return 0;
}
