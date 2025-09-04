#include <iostream>
#include <algorithm>
using namespace std;

static inline bool valid_half(int x, int y) {
    int big = max(x, y);
    int small = min(x, y);
    // Without 3 consecutive from same team in a half:
    // Larger count must not exceed 2*(small+1)
    return big <= 2 * (small + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    if (!(cin >> t)) return 0; 
    while (t--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int x1 = a, y1 = b;           // first half totals
        int x2 = c - a, y2 = d - b;   // second half increments
        bool ok = valid_half(x1, y1) && valid_half(x2, y2);
        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}
