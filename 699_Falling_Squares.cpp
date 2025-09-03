class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        set<int> coords;
        for (auto& pos : positions) {
            coords.insert(pos[0]);
            coords.insert(pos[0] + pos[1]);
        }
        
        vector<int> sortedCoords(coords.begin(), coords.end());
        unordered_map<int, int> coordToIndex;
        for (int i = 0; i < sortedCoords.size(); i++) {
            coordToIndex[sortedCoords[i]] = i;
        }
        
        int n = sortedCoords.size();
        vector<int> heights(n, 0);
        vector<int> result;
        
        for (auto& pos : positions) {
            int left = coordToIndex[pos[0]];
            int right = coordToIndex[pos[0] + pos[1]];
            
            int maxHeight = 0;
            for (int i = left; i < right; i++) {
                maxHeight = max(maxHeight, heights[i]);
            }
            
            int newHeight = maxHeight + pos[1];
            for (int i = left; i < right; i++) {
                heights[i] = newHeight;
            }
            
            int currentMax = *max_element(heights.begin(), heights.end());
            result.push_back(currentMax);
        }
        
        return result;
    }
};