// CF - Ice Baby
// For prefix 1..k, choose values a_i in [l_i, r_i] to maximize LNDS length.
// DP over current maximum chosen lower bound T among selected elements.
// Let dp[T] be max length achievable where the maximum l among chosen equals T.
// Processing interval [l, r]:
//  - For all T in [l, r], we can include this interval without changing T: dp[T] += 1.
//  - For all T <= min(r, l-1), we can include and raise T to l: dp[l] = max(dp[l], max_{T<=min(r,l-1)} dp[T] + 1).
// Maintain dp over discrete T values: sentinel T0 and all distinct l's. Use a segtree with:
//  - range add on [idx(l), idx(r)] over l-coordinates contained in [l, r]
//  - range max query on prefix up to value X = min(r, l-1)
//  - point chmax at idx(l) with queried + 1

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct SegmentTree {
    int n; // number of indices inclusive [0..n]
    struct Node {
        long long max_value;
        long long add_lazy;
    };
    vector<Node> tree;

    SegmentTree(int size) { init(size); }

    void init(int size) {
        n = size;
        tree.assign(4 * (n + 5), {LLONG_MIN / 4, 0});
    }

    void build_from_array(const vector<long long>& base) {
        build(1, 0, n, base);
    }

    void build(int node, int left, int right, const vector<long long>& base) {
        tree[node].add_lazy = 0;
        if (left == right) {
            tree[node].max_value = base[left];
            return;
        }
        int mid = (left + right) >> 1;
        build(node << 1, left, mid, base);
        build(node << 1 | 1, mid + 1, right, base);
        pull(node);
    }

    void pull(int node) {
        tree[node].max_value = max(tree[node << 1].max_value, tree[node << 1 | 1].max_value);
    }

    void apply_add(int node, long long delta) {
        tree[node].max_value += delta;
        tree[node].add_lazy += delta;
    }

    void push(int node) {
        long long lazy = tree[node].add_lazy;
        if (lazy != 0) {
            apply_add(node << 1, lazy);
            apply_add(node << 1 | 1, lazy);
            tree[node].add_lazy = 0;
        }
    }

    void range_add(int ql, int qr, long long delta) { range_add(1, 0, n, ql, qr, delta); }

    void range_add(int node, int left, int right, int ql, int qr, long long delta) {
        if (ql > qr) return;
        if (ql <= left && right <= qr) { apply_add(node, delta); return; }
        push(node);
        int mid = (left + right) >> 1;
        if (ql <= mid) range_add(node << 1, left, mid, ql, qr, delta);
        if (qr > mid) range_add(node << 1 | 1, mid + 1, right, ql, qr, delta);
        pull(node);
    }

    long long range_max(int ql, int qr) { return range_max(1, 0, n, ql, qr); }

    long long range_max(int node, int left, int right, int ql, int qr) {
        if (ql > qr) return LLONG_MIN / 4;
        if (ql <= left && right <= qr) return tree[node].max_value;
        push(node);
        int mid = (left + right) >> 1;
        long long res = LLONG_MIN / 4;
        if (ql <= mid) res = max(res, range_max(node << 1, left, mid, ql, qr));
        if (qr > mid) res = max(res, range_max(node << 1 | 1, mid + 1, right, ql, qr));
        return res;
    }

    long long point_get(int pos) { return range_max(pos, pos); }

    void point_chmax(int pos, long long value) {
        long long current = point_get(pos);
        if (value > current) {
            range_add(pos, pos, value - current);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_tests;
    if (!(cin >> num_tests)) return 0;
    while (num_tests--) {
        int n;
        cin >> n;
        vector<long long> left_bounds(n), right_bounds(n);
        vector<long long> unique_lefts;
        unique_lefts.reserve(n);
        for (int i = 0; i < n; i++) {
            cin >> left_bounds[i] >> right_bounds[i];
            unique_lefts.push_back(left_bounds[i]);
        }

        sort(unique_lefts.begin(), unique_lefts.end());
        unique_lefts.erase(unique(unique_lefts.begin(), unique_lefts.end()), unique_lefts.end());
        const int m = static_cast<int>(unique_lefts.size());

        // Indexing: 0 = sentinel T0; 1..m correspond to unique_lefts[0..m-1].
        SegmentTree seg(m);
        const long long NEG_INF = LLONG_MIN / 4;
        vector<long long> base(m + 1, NEG_INF);
        base[0] = 0; // empty subsequence
        seg.build_from_array(base);

        vector<int> answers(n, 0);

        auto left_index = [&](long long value) -> int {
            // return 1-based index in seg for l == value
            int idx = int(lower_bound(unique_lefts.begin(), unique_lefts.end(), value) - unique_lefts.begin());
            return idx + 1; // 1..m
        };

        auto first_index_ge = [&](long long value) -> int {
            // first index j (1..m) with unique_lefts[j-1] >= value, or m+1 if none
            int idx = int(lower_bound(unique_lefts.begin(), unique_lefts.end(), value) - unique_lefts.begin());
            return idx + 1;
        };

        auto last_index_le = [&](long long value) -> int {
            // last index j (1..m) with unique_lefts[j-1] <= value, or 0 if none
            int idx = int(upper_bound(unique_lefts.begin(), unique_lefts.end(), value) - unique_lefts.begin());
            return idx; // because seg indices are +1, this already matches 0..m
        };

        for (int i = 0; i < n; i++) {
            long long l = left_bounds[i];
            long long r = right_bounds[i];

            long long x = min(r, l - 1);
            int pref_last = last_index_le(x); // in [0..m]
            long long best_prefix = seg.range_max(0, pref_last); // include sentinel 0

            int L = first_index_ge(l);       // in [1..m+1]
            int R = last_index_le(r);        // in [0..m]
            if (L <= R) {
                seg.range_add(L, R, 1);      // dp[T]+=1 for all T in [l, r]
            }

            int pos_l = left_index(l);
            seg.point_chmax(pos_l, best_prefix + 1); // dp[l] = max(dp[l], best_prefix + 1)

            long long current_best = seg.range_max(1, m);
            answers[i] = int(current_best);
        }

        for (int i = 0; i < n; i++) {
            if (i) cout << ' ';
            cout << answers[i];
        }
        cout << '\n';
    }
    return 0;
}