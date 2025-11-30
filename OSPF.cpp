#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)1e15;

vector<ll> dijkstra(int src, const vector<vector<pair<int,ll>>> &adj, vector<int> &parent){
    int n = adj.size()-1;
    vector<ll> dist(n+1, INF);
    parent.assign(n+1, -1);
    dist[src] = 0;

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.push({0,src});

    while(!pq.empty()){
        auto p = pq.top(); pq.pop();
        ll d = p.first; 
        int u = p.second;

        if(d != dist[u]) continue;

        for(auto &e: adj[u]){
            int v = e.first; 
            ll w = e.second;

            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int next_hop(int src, int dest, const vector<int> &parent){
    if(parent[dest] == -1) return -1;

    int cur = dest;
    int prev = parent[cur];

    while(prev != src && prev != -1){
        cur = prev;
        prev = parent[cur];
    }

    if(prev == -1 && src != dest) return -1;
    if(src == dest) return dest;

    return cur;
}

int main(){

    int n, m;

    // 🔹 Added user-friendly input prompts
    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    cout << "Enter edges as: u v w\n";

    vector<vector<pair<int,ll>>> adj(n+1);

    for(int i=0; i<m; i++){
        int u, v; 
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    cout << "\nOSPF-style routing tables (Destination, Cost, NextHop)\n\n";

    for(int src = 1; src <= n; ++src){
        vector<int> parent;
        auto dist = dijkstra(src, adj, parent);

        cout << "Routing table for node " << src << ":\n";
        cout << "Dest\tCost\tNextHop\n";

        for(int dest = 1; dest <= n; ++dest){
            if(dist[dest] == INF){
                cout << dest << "\t-\t-\n";
                continue;
            }

            int nh = next_hop(src, dest, parent);

            if(nh == -1){
                if(src == dest)
                    cout << dest << "\t0\t" << src << "\n";
                else
                    cout << dest << "\t" << dist[dest] << "\t-\n";
            }
            else 
                cout << dest << "\t" << dist[dest] << "\t" << nh << "\n";
        }
        cout << "\n";
    }
    return 0;
}
