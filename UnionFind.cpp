const int MAX_N = 100000;

int par[MAX_N + 1], r[MAX_N + 1];

void init(int n){
	for(int i = 0; i < n; ++i){
		par[i] = i;
		r[i] = 0;
	}	
}

int find(int x){
	if(par[x] == x)
		return x;
	else
		return par[x] = find(par[x]);
}

void unite(int x, int y){
	x = find(x);
	y = find(y);
	if(x == y)
		return;
		
	if(r[x] < r[y]){
		par[x] = y;
	}
	else{
		par[y] = x;
		if(r[x] == r[y])
			r[x]++;
	}
}

bool same(int x, int y){
	return find(x) == find(y);
}