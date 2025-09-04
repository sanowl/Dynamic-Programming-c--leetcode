// Sort nodes by asymptotic order using lex order of sequence
// S(u) = [leaves(L(u)), leaves(L(R(u))), leaves(L(R(R(u)))), ...]
// Leaves have S(u) = []. Shorter sequence is smaller if prefixes equal.
// We build ranks for these sequences using suffix-array-style doubling
// over the right-chain with a sentinel at leaves.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n; cin >> n;
        vector<int> L(n + 1), R(n + 1);
        for (int i = 1; i <= n; ++i) {
            int l, r; cin >> l >> r; L[i] = l; R[i] = r;
        }

        // Postorder to compute leaf counts
        vector<int> leafCount(n + 1, 0);
        vector<int> order; order.reserve(n);
        {
            vector<int> st; st.reserve(n);
            st.push_back(1);
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                order.push_back(u);
                if (L[u]) st.push_back(L[u]);
                if (R[u]) st.push_back(R[u]);
            }
            for (int i = (int)order.size() - 1; i >= 0; --i) {
                int u = order[i];
                if (L[u] == 0 && R[u] == 0) leafCount[u] = 1;
                else leafCount[u] = (L[u] ? leafCount[L[u]] : 0) + (R[u] ? leafCount[R[u]] : 0);
            }
        }

        // Prepare values and successor pointers for doubling over right chains
        const int MAX_LOG = 20; // 2^20 > 1e6 > max possible chain length
        vector<int> val(n + 1);         // first symbol in sequence; -1 for leaves
        vector<array<int, MAX_LOG>> succ(n + 1);

        for (int u = 1; u <= n; ++u) {
            bool isLeaf = (L[u] == 0 && R[u] == 0);
            if (isLeaf) {
                val[u] = -1; // sentinel smaller than any positive count
                succ[u][0] = u; // stays at leaf
            } else {
                val[u] = leafCount[L[u]]; // >= 1
                succ[u][0] = R[u];
            }
        }

        for (int k = 1; k < MAX_LOG; ++k) {
            for (int u = 1; u <= n; ++u) {
                succ[u][k] = succ[succ[u][k-1]][k-1];
            }
        }

        // Initial ranks based on first symbol (val)
        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        vector<int> rank_prev(n + 1), rank_cur(n + 1);
        sort(nodes.begin(), nodes.end(), [&](int a, int b){ return val[a] < val[b]; });
        int cur_rank = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && val[nodes[i]] != val[nodes[i-1]]) ++cur_rank;
            rank_prev[nodes[i]] = cur_rank;
        }

        // Doubling: compare pairs (rank, rank at 2^{k-1} step)
        vector<pair<pair<int,int>, int>> key(n);
        for (int k = 1; k < MAX_LOG; ++k) {
            for (int i = 1; i <= n; ++i) {
                key[i-1] = {{rank_prev[i], rank_prev[succ[i][k-1]]}, i};
            }
            sort(key.begin(), key.end(), [&](const auto& A, const auto& B){
                if (A.first.first != B.first.first) return A.first.first < B.first.first;
                if (A.first.second != B.first.second) return A.first.second < B.first.second;
                return A.second < B.second; // keep deterministic
            });
            cur_rank = 0;
            for (int i = 0; i < n; ++i) {
                if (i > 0 && key[i].first != key[i-1].first) ++cur_rank;
                rank_cur[key[i].second] = cur_rank;
            }
            rank_prev.swap(rank_cur);
        }

        // Final sorting by full-sequence rank, tie by node index
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        stable_sort(nodes.begin(), nodes.end(), [&](int a, int b){
            if (rank_prev[a] != rank_prev[b]) return rank_prev[a] < rank_prev[b];
            return a < b;
        });

        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << nodes[i];
        }
        cout << '\n';
    }
    return 0;
}
