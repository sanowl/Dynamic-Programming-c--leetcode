#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> power(n + 1); // power[i] = power of box originally at position i
        vector<int> pos(n + 1);   // pos[i] = current position of box originally at position i
        vector<int> at_pos(n + 1); // at_pos[i] = which original box is currently at position i
        
        // Initialize positions
        for (int i = 1; i <= n; i++) {
            pos[i] = i;
            at_pos[i] = i;
        }
        
        vector<bool> determined(n + 1, false);
        int queries = 0;
        
        // Strategy: Start from position 1 and work our way through
        for (int start = 1; start <= n && queries < (3 * n + 1) / 2; start++) {
            if (determined[at_pos[start]]) continue;
            
            // Throw from position start to see the chain reaction
            cout << "throw " << start << endl;
            cout.flush();
            queries++;
            
            int jumps;
            cin >> jumps;
            
            if (jumps == 1) {
                // Only one jump means the box at position start has power that takes us out of bounds
                // So this box has power = n + 1 - start, but since powers are 1 or 2...
                // If start == n, then power = 1 (goes to n+1, out of bounds)
                // If start == n-1, then power could be 1 (goes to n) or 2 (goes to n+1)
                if (start == n) {
                    power[at_pos[start]] = 1;
                    determined[at_pos[start]] = true;
                } else {
                    // Need more info, try to isolate this box
                    if (start < n && queries < (3 * n + 1) / 2) {
                        // Swap with next position and test again
                        cout << "swap " << start << endl;
                        cout.flush();
                        queries++;
                        
                        // Update positions after swap
                        swap(at_pos[start], at_pos[start + 1]);
                        pos[at_pos[start]] = start;
                        pos[at_pos[start + 1]] = start + 1;
                        
                        cout << "throw " << start << endl;
                        cout.flush();
                        queries++;
                        
                        int jumps2;
                        cin >> jumps2;
                        
                        if (jumps2 == 1) {
                            power[at_pos[start]] = n + 1 - start;
                            if (power[at_pos[start]] > 2) power[at_pos[start]] = 2;
                        } else {
                            power[at_pos[start]] = 1;
                        }
                        determined[at_pos[start]] = true;
                        
                        // Swap back
                        cout << "swap " << start << endl;
                        cout.flush();
                        queries++;
                        
                        swap(at_pos[start], at_pos[start + 1]);
                        pos[at_pos[start]] = start;
                        pos[at_pos[start + 1]] = start + 1;
                    }
                }
            } else {
                // Multiple jumps - we can deduce something about the chain
                // Work backwards: if we made jumps, what could the powers be?
                
                // Simple heuristic: assume first box has power 1, see if it's consistent
                int current_pos = start;
                int remaining_jumps = jumps;
                bool valid_with_power1 = true;
                
                while (remaining_jumps > 0 && current_pos <= n && valid_with_power1) {
                    if (remaining_jumps == jumps - (current_pos - start)) {
                        // This is our first box
                        current_pos += 1; // Assume power 1
                    } else {
                        current_pos += (current_pos > n ? 0 : 2); // Assume power 2 for others
                    }
                    remaining_jumps--;
                    if (current_pos > n + 1) valid_with_power1 = false;
                }
                
                if (valid_with_power1) {
                    power[at_pos[start]] = 1;
                } else {
                    power[at_pos[start]] = 2;
                }
                determined[at_pos[start]] = true;
            }
        }
        
        // For any remaining undetermined boxes, use binary search approach
        for (int i = 1; i <= n; i++) {
            if (!determined[i] && queries < (3 * n + 1) / 2) {
                // Move box i to position 1 and test
                int curr_pos = pos[i];
                
                // Bubble sort to position 1
                while (curr_pos > 1 && queries < (3 * n + 1) / 2) {
                    cout << "swap " << (curr_pos - 1) << endl;
                    cout.flush();
                    queries++;
                    
                    // Update tracking
                    swap(at_pos[curr_pos], at_pos[curr_pos - 1]);
                    pos[at_pos[curr_pos]] = curr_pos;
                    pos[at_pos[curr_pos - 1]] = curr_pos - 1;
                    curr_pos--;
                }
                
                // Now box i is at position 1, test it
                cout << "throw 1" << endl;
                cout.flush();
                queries++;
                
                int jumps;
                cin >> jumps;
                
                // Determine power based on jumps
                if (jumps == n) {
                    power[i] = 1; // All boxes have power 1, ball goes 1->2->3->...->n->n+1
                } else {
                    // More complex logic based on the actual jump pattern
                    power[i] = (jumps < n) ? 2 : 1;
                }
                determined[i] = true;
            }
        }
        
        // Fill in any remaining with default value
        for (int i = 1; i <= n; i++) {
            if (!determined[i]) {
                power[i] = 1; // Default guess
            }
        }
        
        // Output answer
        cout << "!";
        for (int i = 1; i <= n; i++) {
            cout << " " << power[i];
        }
        cout << endl;
        cout.flush();
    }
    
    return 0;
}