// Сложная задача

#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;
typedef std::vector<std::vector<int>> vvi;

int dfs(int v, int p, vvi& dp, vvi& adj) {
    dp[v][0] = 0;
    dp[v][1] = 1;
    int ret = 0;
    for (auto to : adj[v]) {
        if (to == p)
            continue;
        ret = std::max(ret, dfs(to, v, dp, adj));
        ret = std::max(ret, dp[v][0] + std::max(dp[to][0], dp[to][1]) + (adj[v].size() >= 2 ? (int)adj[v].size() - 2 : 0));
        ret = std::max(ret, dp[v][1] + dp[to][0]);
        dp[v][0] = std::max(dp[v][0], std::max(dp[to][0], dp[to][1]));
        dp[v][1] = std::max(dp[v][1], dp[to][0] + 1);
    }
    if (adj[v].size() >= 2)
        dp[v][0] += adj[v].size() - 2;
    ret = std::max(ret, std::max(dp[v][0], dp[v][1]));
    return ret;
}

int main() {
    int n;
    std::cin >> n;
    vvi adj(n);
    vvi dp(n, std::vector<int>(2));
    for (int i = 0; i < n - 1; ++i) {
        int p;
        int q;
        std::cin >> p >> q;
        --p;
        --q;
        adj[p].push_back(q);
        adj[q].push_back(p);
    }
    std::cout << dfs(0, -1, dp, adj) << std::endl;
}
