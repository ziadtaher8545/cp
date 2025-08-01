const int N = 1e6 + 5;
vector<int> spf(N + 5);
void SPF()
{
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; i <= N / i; ++i)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j <= N; j += i)
                spf[j] = (spf[j] == j ? i : spf[j]);
        }
    }
}
