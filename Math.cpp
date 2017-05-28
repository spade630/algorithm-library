
long long inv[200001], fac[200001], facinv[200001];

// 逆元テーブル
inv[1] = 1;
for(long long i = 2; i <= N; ++i)
	inv[i] = mod - (mod / i) * inv[mod % i] % mod;

// 階乗逆元テーブル
fac[0] = facinv[0] = 1;
for(long long i = 1; i <= N; ++i){
	fac[i] = (fac[i - 1] * i) % mod;
	facinv[i] = (facinv[i - 1] * inv[i]) % mod;
}