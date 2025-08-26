vector<vector<ll>> g;
vector<bool> visi;

void dfs(ll v){
  visi[v] = true;

  for(ll u: g[v]){
    if(!visi[u]){
      dfs(u);
    }
  }
}
