#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        // Find the maximum path length by querying each node with all nodes
        int maxLength = 0;
        int bestStart = 1;
        
        for (int start = 1; start <= n; start++) {
            cout << "? " << start << " " << n;
            for (int i = 1; i <= n; i++) {
                cout << " " << i;
            }
            cout << endl;
            cout.flush();
            
            int length;
            cin >> length;
            
            if (length > maxLength) {
                maxLength = length;
                bestStart = start;
            }
        }
        
        // Now find the actual path by testing each possible next node
        vector<int> path = {bestStart};
        vector<bool> used(n + 1, false);
        used[bestStart] = true;
        
        for (int step = 1; step < maxLength; step++) {
            // Try each unused node as the next node
            for (int next = 1; next <= n; next++) {
                if (used[next]) continue;
                
                // Test if this node can be the next in the path
                vector<int> testSet = path;
                testSet.push_back(next);
                
                cout << "? " << bestStart << " " << testSet.size();
                for (int node : testSet) {
                    cout << " " << node;
                }
                cout << endl;
                cout.flush();
                
                int length;
                cin >> length;
                
                if (length == step + 1) {
                    path.push_back(next);
                    used[next] = true;
                    break;
                }
            }
        }
        
        // Output the result
        cout << "! " << path.size();
        for (int node : path) {
            cout << " " << node;
        }
        cout << endl;
        cout.flush();
    }
    
    return 0;
}