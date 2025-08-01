
// calc 1e9 in 42ms,can calc more but need big integer
/*
sum(x/1*1+x/2*2+x/3*3+x/4*4......)
  */
ll sumRangeDivisors(ll x) {
ll ans = 0, left = 1, right;
for (; left <= x; left = right + 1) {
right = x / (x / left);
ans += (x / left) * (left + right) * (right - left + 1) / 2;
}
return ans;
}
