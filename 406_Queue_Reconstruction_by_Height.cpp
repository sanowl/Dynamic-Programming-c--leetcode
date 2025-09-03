class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0];
        });
        
        vector<vector<int>> result;
        for (const auto& person : people) {
            result.insert(result.begin() + person[1], person);
        }
        
        return result;
    }
};