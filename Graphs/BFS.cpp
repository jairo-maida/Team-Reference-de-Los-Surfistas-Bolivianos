vector<vector<ll>> g;

void bfs(ll u){
  ll n = g.size(); 
  
  queue<ll> q;
  vector<bool> visi(n);

  q.push(s);
  visi[u] = true;
  while (!q.empty()) {
      ll v = q.front();
      q.pop();
      for (ll u : g[v]) {
          if (!visi[u]) {
              visi[u] = true;
              q.push(u);
          }
      }
  }
}
