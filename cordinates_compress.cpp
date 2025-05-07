void cordinates_compress(vector<int>& v) {
    vector<int>temp = v;
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());
    for (auto& x : v) {
        x = lower_bound(temp.begin(), temp.end(), x) - temp.begin() + 1;
    }
}
