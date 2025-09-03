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
        int W = -1;
        
        // First query: test with word of length 1
        cout << "? 1 1" << endl;
        cout.flush();
        
        int response;
        cin >> response;
        
        if (response == 0) {
            // W < 1, impossible since W >= 1
            W = 1;
        } else {
            // W >= 1, now find exact value using binary search
            int left = 1, right = 100000;
            
            while (left <= right) {
                int mid = left + (right - left) / 2;
                
                cout << "? 1 " << mid << endl;
                cout.flush();
                
                cin >> response;
                
                if (response == 0) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                    W = mid;
                }
            }
        }
        
        cout << "! " << W << endl;
        cout.flush();
    }
    
    return 0;
}