ll INF = 1e18 // Asegurarse que el valor de infinito 
              // supere a la distancia más grande posible en el problema
vector<ll> dijkstra(vector<vector<pair<ll, ll>>> &g, ll source){
    ll n = g.size();
    vector<ll> dis(n, 1e9);
    vector<bool> vis(n);
    priority_queue<pair<ll, ll>> que;
    que.push({0, source});
    dis[source] = 0;
    while(!que.empty()){
        ll node = que.top().s;
        que.pop();
        if(vis[node]) continue;
        vis[node] = 1;
        for(ii ed : g[node])
            if(dis[ed.f] > dis[node] + ed.s){
                dis[ed.f] = dis[node] + ed.s;
                que.push({-dis[ed.f], ed.f});
            }
    }
    return dis;
}
