#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> parent, rank;
    int components;
    
    UnionFind(int n) : parent(n), rank(n, 0), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        components--;
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<long long> g(n);
        for (int i = 0; i < n; i++) {
            cin >> g[i];
        }
        
        UnionFind uf(n);
        long long total_cost = 0;
        
        while (uf.components > 1) {
            long long min_cost = LLONG_MAX;
            int best_i = -1, best_j = -1;
            
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (uf.find(i) != uf.find(j)) {
                        long long cost = max(g[i], g[j]);
                        if (cost < min_cost) {
                            min_cost = cost;
                            best_i = i;
                            best_j = j;
                        }
                    }
                }
            }
            
            uf.unite(best_i, best_j);
            total_cost += min_cost;
            
            long long decrease = min(g[best_i], g[best_j]);
            g[best_i] -= decrease;
            g[best_j] -= decrease;
        }
        
        cout << total_cost << "\n";
    }
    
    return 0;
}