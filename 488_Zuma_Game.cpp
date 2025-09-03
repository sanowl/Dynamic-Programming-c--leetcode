class Solution {
public:
    int findMinStep(string board, string hand) {
        unordered_map<string, int> memo;
        
        function<string(string)> remove = [](string s) -> string {
            bool changed = true;
            while (changed) {
                changed = false;
                for (int i = 0; i < s.length(); ) {
                    int j = i;
                    while (j < s.length() && s[j] == s[i]) j++;
                    if (j - i >= 3) {
                        s = s.substr(0, i) + s.substr(j);
                        changed = true;
                        break;
                    }
                    i = j;
                }
            }
            return s;
        };
        
        function<int(string, string)> dfs = [&](string board, string hand) -> int {
            if (board.empty()) return 0;
            if (hand.empty()) return -1;
            
            string key = board + "#" + hand;
            if (memo.count(key)) return memo[key];
            
            int result = -1;
            
            for (int i = 0; i < hand.length(); i++) {
                if (i > 0 && hand[i] == hand[i-1]) continue;
                
                string newHand = hand.substr(0, i) + hand.substr(i + 1);
                
                for (int j = 0; j <= board.length(); j++) {
                    if (j > 0 && board[j-1] == hand[i]) continue;
                    
                    string newBoard = board.substr(0, j) + hand[i] + board.substr(j);
                    newBoard = remove(newBoard);
                    
                    int steps = dfs(newBoard, newHand);
                    if (steps != -1) {
                        if (result == -1 || steps + 1 < result) {
                            result = steps + 1;
                        }
                    }
                }
            }
            
            return memo[key] = result;
        };
        
        return dfs(board, hand);
    }
};