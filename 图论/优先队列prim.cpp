struct edge{
	int v, w;
};
vector<edge> adj[N];
int d[N];
bool intree[N];
const int INF = (N-1)*W;

void prim() {
	int s = 0;
	for (int i = 0; i < n; ++i) d[i] = INF;
	d[s] = 0;

	typedef pair<int, int> pii;   // d[i], i
	priority_queue<pii> q;
	q.push(pii(d[s],s));
	for (int i = 0; i < n; ++i) {
		int u;
		do{
			pii k = q.top(); q.pop();
			u = k.second;
		}while (intree[u]);
		intree[u] = 1;

		for (int i = 0; i < adj[u].size(); ++i) {
			edge e = adj[u][i]; int v = e.v, w = e.w;
			if (!intree[v] && w < d[v]) {
				d[v] = w;
				q.push(d[v], v);
			}
		}
	}
}

