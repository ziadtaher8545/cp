auto sum = [&](string s, string x) -> string
{
    int sz1 = s.size(), sz2 = x.size();
    int car = 0;
    string ret = "";
    int i = sz1 - 1, j = sz2 - 1;
    while (i >= 0 || j >= 0 || car)
    {
        int nm1 = (i >= 0) ? s[i--] - '0' : 0;
        int nm2 = (j >= 0) ? x[j--] - '0' : 0;
        int sm = nm1 + nm2 + car;
        ret += (sm % 10 + '0');
        car = sm / 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
};
