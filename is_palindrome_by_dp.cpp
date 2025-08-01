const int M = 1e3 + 5;
int is[M][M], dp[M][M];
string s;
int is_palin(int l, int r)
{
    if (l >= r)
        return 1;
    int &ret = is[l][r];
    if (~ret)
        return ret;
    return ret = (s[l] == s[r]) && is_palin(l + 1, r - 1);
}
int clc(int l, int r)
{
    if (l > r)
        return 0;

    int &ret = dp[l][r];
    if (~ret)
        return ret;

    int ch1 = clc(l + 1, r);
    int ch2 = clc(l, r - 1);
    int ch3 = clc(l + 1, r - 1);

    return ret = ch1 + ch2 - ch3 + is_palin(l, r);
