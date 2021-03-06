// Meysam Aghighi

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

struct edge{
	int u, v, w;
	edge(int _u, int _v, int _w): u(_u), v(_v), w(_w){} // member initialization
};

#define N 505
int n,m,s,t,u,v,w;
long long g[N][N], rg[N][N], f[N], max_flow, path_flow;
int p[N];

long long bfs(int s, int t){
    bool visited[n]; memset(visited,false,sizeof(visited)); visited[s] = true;
    queue <int> q; q.push(s);
    p[s] = -1; // needed?
    f[s] = INT_MAX;
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (int v=0; v<n; v++){
            if (visited[v]==false && rg[u][v] > 0){
                q.push(v);
                p[v] = u;
                visited[v] = true;
                f[v] = min(f[u],rg[u][v]);
            }
        }
    }
    return (visited[t]?f[t]:0);
}


void fordFulkerson(int s, int t){
    max_flow = 0;
    while (path_flow = bfs(s, t)){
        for (v=t; v != s; v=p[v]){
            u = p[v];
            rg[u][v] -= path_flow;
            rg[v][u] += path_flow;
        }
        max_flow += path_flow;
    }

    // Print output
    vector<edge> used_edges;
    for (int i=0;i<n;i++)
    	for (int j=0;j<n;j++)
    		if (g[i][j] > 0 && rg[i][j] < g[i][j])
    			used_edges.push_back(edge(i,j,g[i][j]-rg[i][j]));

    // ashghal in ghesmat be jaye "n" mioomadam tedade node haye estefade shoda ro mizashtam... ah!
    cout << n << " " << max_flow << " " << used_edges.size() << endl;
    for (int i=0;i<used_edges.size();i++)
    	cout << used_edges[i].u << " " << used_edges[i].v << " " << used_edges[i].w << endl;
}

int main(){
	cin >> n >> m >> s >> t;
	memset(g,0,sizeof(g));
	memset(rg,0,sizeof(rg));
	for (int i=0;i<m;i++){
		cin >> u >> v >> w;
		g[u][v] = rg[u][v] = w;
	}
	fordFulkerson(s,t);
	return 0;
}
