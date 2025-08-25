class trie
{
private:
    struct node
    {
        int word = 0, prefix = 0, child[26];
        node() {
            memset(child, -1, sizeof child);
        }
    };
    vector<node> tri = vector<node>(1);

public:
    void insert(const string& s, int cnt = 1) {
        int cur = 0;
        for (auto it : s) {
            int to = it - 'a';
            if (tri[cur].child[to] == -1) {
                tri[cur].child[to] = tri.size();
                tri.emplace_back();
            }
            cur = tri[cur].child[to];
            tri[cur].prefix += cnt;
        }
        tri[cur].word += cnt;
    }

    void erase(const string& s) {
        int cur = 0;
        for (auto it : s) {
            int to = it - 'a';
            if (tri[cur].child[to] == -1 || tri[tri[cur].child[to]].prefix == 1) {
                tri[cur].child[to] = -1;
                return;
            }
            cur = tri[cur].child[to];
            tri[cur].prefix--;
        }
        tri[cur].word--;
    }

    int count_word(const string& s) {
        int cur = 0;
        for (auto it : s) {
            int to = it - 'a';
            if (tri[cur].child[to] == -1) {
                return 0;
            }
            cur = tri[cur].child[to];
        }
        return tri[cur].word;
    }

    int count_prefix(const string& s) {
        int cur = 0;
        for (auto it : s) {
            int to = it - 'a';
            if (tri[cur].child[to] == -1) {
                return 0;
            }
            cur = tri[cur].child[to];

        }
        return tri[cur].prefix;
    }
};
