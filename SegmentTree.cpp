typedef pair<int, int> P;
typedef vector<P> vp;
const int INF = 1e+9;
const int MAX_N = 1 << 17;

class SegmentTree {
	int n, dat[2 * MAX_N - 1];

	SegmentTree(int n_){
		n = 1;
		while(n < n_)
			n *= 2;
			
		for(int i = 0; i < 2 * n - 1; ++i)
			dat[i] = INF;
	}

	void update(int k, int a){
		k += n - 1;
		dat[k] = a;
		while(k > 0){
			k = (k - 1) / 2;
			dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
		}
	}

	int findMin(int a, int b){
		return query(a, b, 0, 0, N);
	}

	int query(int a, int b, int k, int l, int r){
		if(r <= a || b <= l)
			return INF;
			
		if(a <= l && r <= b)
			return dat[k];
		else{
			int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return min(vl, vr);
		}
	}
};

// 区間BIT

const int MAX_N = 200010;
typedef long long ll;
ll bit0[MAX_N], bit1[MAX_N];

ll sum(ll *b, int i){
	ll s = 0;
	while(i > 0){
		s += b[i];
		i -= i & -i;
	}
	return s;
}

void add(ll *b, int i, ll v){
	while(i <= MAX_N){
		b[i] += v;
		i += i & -i;
	}
}

ll query_sum(ll *b0, ll *b1, int l, int r){
	return sum(b0, r) + sum(b1, r) * r - sum(b0, l - 1) - sum(b1, l - 1) * (l - 1);
}

void query_add(ll *b0, ll *b1, int l, int r, ll x){
	add(b0, l, -x * (l - 1));
	add(b1, l, x);
	add(b0, r + 1, x * r);
	add(b1, r + 1, -x);
}

// 領域木

void init(int k, int l, int r){
	if(r - l == 1)
		dat[k].push_back(x[l]);
	else{
		int lch = k * 2 + 1, rch = k * 2 + 2;
		init(lch, l, (l + r) / 2);
		init(rch, (l + r) / 2, r);
		dat[k].resize(r - l);
		
		merge(dat[lch].begin(), dat[lch].end(), dat[rch].begin(), dat[rch].end(), dat[k].begin());
	}
}