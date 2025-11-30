#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)1e15;

int main(){

    int n, m;
    cout<<"Enter no of vertices: ";
    cin>> n;

    cout<<"Enter no of Edges: ";
    cin>> m;

    cout<<"Enter m Edges in the form x connected to y: x y\n";
    vector<vector<pair<int,ll>>> adj(n+1);
    for(int i=0;i<m;i++){
        int u,v; ll w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    cout<<"Enter the Source And Destination"<<"\n";
    int src, dest; cin >> src >> dest;
    vector<ll> dist(n+1, INF);
    vector<int> parent(n+1, -1);
    dist[src]=0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.push(make_pair(0, src));
    while(!pq.empty()){
        pair<ll,int> top = pq.top(); pq.pop();
        ll d = top.first;
        int u = top.second;
        if(d != dist[u]) continue;
        for(size_t i=0;i<adj[u].size();++i){
            int v = adj[u][i].first;
            ll w = adj[u][i].second;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    cout << "Distance from " << src << " to:\n";
    for(int i=1;i<=n;i++){
        if(dist[i]==INF) cout << i << " -> INF\n";
        else cout << i << " -> " << dist[i] << "\n";
    }
    if(dist[dest]==INF){
        cout << "\nNo path from " << src << " to " << dest << "\n";
        return 0;
    }
    vector<int> path;
    for(int v=dest; v!=-1; v=parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "\nShortest path from " << src << " to " << dest << ": ";
    for(size_t i=0;i<path.size();i++){
        cout << path[i];
        if(i+1<path.size()) cout << " -> ";
    }
    cout << "\nDistance = " << dist[dest] << "\n";
    return 0;
}