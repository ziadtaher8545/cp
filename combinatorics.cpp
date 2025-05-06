const int N = 1e6 + 9, Mod = 1e9 + 7;
vector<int> fact(N, 1), invfact(N, 1);
int pw(int base, int n) {
    int res = 1;
    while (n) {
        if (n & 1)
            res = (res * base) % Mod;
        base = (base * base) % Mod;
        n >>= 1;
    }
    return res;
}
int modInverse(int a) {
    return pw(a, Mod - 2);
}

void pre() {
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % Mod;
    }
    invfact[N - 1] = modInverse(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--) {
        invfact[i] = invfact[i + 1] * (i + 1) % Mod;
    }
}
int npr(int a, int b) {
    if (a < b)
        return 0;
    return (fact[a] * invfact[b]) % Mod;
}
int ncr(int a, int b) {
    if (a < b)
        return 0;
    return (fact[a] * invfact[b] % Mod * invfact[a-b]) % Mod;
}
