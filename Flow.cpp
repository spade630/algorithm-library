// 最大マッチング(二部)

const int MAX_V = 100010;

int V;
vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];

bool dfs(int v){
	used[v] = true;
	for(int i = 0; i < G1[v].size(); ++i){
		int u = G1[v][i], w = match[u];
		if(w < 0 || !used[w] && dfs(w)){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}

int bipartite_matching(){
	int res = 0;
	memset(match, -1, sizeof(match));
	for(int v = 0; v < V; ++v){
		if(match[v] < 0){
			memset(used, 0, sizeof(used));
			if(dfs(v)){
				res++;
			}
		}
	}
	return res;
}

// 最大流(最小カット)

const int INF = 1e+9;
const int MAX_V = 100010;

struct edge {
	int to, cap, rev;
	edge(int t, int c, int r) : to(t), cap(c), rev(r){}
};

int V;
vector<edge> G[MAX_V];
int level[MAX_V];
int iter[MAX_V];

void bfs(int s) {
	memset(level, -1, sizeof(level));
	queue<int> que;
	level[s] = 0;
	que.push(s);
	while(!que.empty()){
		int v = que.front(); 
		que.pop();
		for(int i = 0; i < G[v].size(); ++i){
			edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0){
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}

int dfs(int v, int t, int f){
	if(v == t)
		return f;
		
	for(int &i = iter[v]; i < G[v].size(); ++i){
		edge &e = G[v][i];
		if(e.cap > 0 && level[v] < level[e.to]){
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0){
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow(int s, int t){
	int flow = 0;
	for(;;){
		bfs(s);
		if(level[t] < 0)
			return flow;
		memset(iter, 0, sizeof(iter));
		int f;
		while((f = dfs(s, t, INF)) > 0)
			flow += f;
	}
}