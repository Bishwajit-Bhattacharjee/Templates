#include <bits/stdc++.h>
using namespace std;

int const N = 2e5 + 10;
int const LOG = 19;
vector<vector<int>> g;
int dp[LOG][N], tin[N], tout[N];
int timer;

void dfs(int u, int p){
    dp[0][u] = p;
    tin[u] = ++timer;
    for (auto v : g[u]){
        dfs(v, u);
    }
    tout[u] = ++timer;
}


bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v){
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;

    for (int i = LOG-1; i >= 0; i--){
        if (!is_ancestor(dp[i][u], v)) {
            u = dp[i][u];
        }
    }
    return dp[0][u];
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;
    g.assign(n+1, vector<int>());

    for (int i = 2; i <= n; i++){
        int boss;
        cin >> boss;
        g[boss].push_back(i);
    }
    // very careful, parent of root has to be root
    dfs(1, 1);  // parent of root is root

    for (int i = 1; i < LOG; i++){
        for (int j = 1; j <= n; j++){
            dp[i][j] = dp[i-1][dp[i-1][j]];
        }
    }

    while (q--){
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
}