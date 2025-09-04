class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (s.empty() || words.empty()) return result;
        
        int wordLen = words[0].length();
        int wordCount = words.size();
        int totalLen = wordLen * wordCount;
        int sLen = s.length();
        
        if (sLen < totalLen) return result;
        
        // Create frequency map of words
        unordered_map<string, int> wordFreq;
        for (const string& word : words) {
            wordFreq[word]++;
        }
        
        // Try each possible starting offset (0 to wordLen-1)
        for (int offset = 0; offset < wordLen; offset++) {
            unordered_map<string, int> windowMap;
            int validWords = 0;
            int left = offset;
            
            // Sliding window approach
            for (int right = offset; right <= sLen - wordLen; right += wordLen) {
                string rightWord = s.substr(right, wordLen);
                
                // Add word to window
                windowMap[rightWord]++;
                if (wordFreq.count(rightWord) && windowMap[rightWord] <= wordFreq[rightWord]) {
                    validWords++;
                }
                
                // If window is larger than needed, shrink from left
                while (right - left + wordLen > totalLen) {
                    string leftWord = s.substr(left, wordLen);
                    if (wordFreq.count(leftWord) && windowMap[leftWord] <= wordFreq[leftWord]) {
                        validWords--;
                    }
                    windowMap[leftWord]--;
                    if (windowMap[leftWord] == 0) {
                        windowMap.erase(leftWord);
                    }
                    left += wordLen;
                }
                
                // Check if current window is valid
                if (validWords == wordCount && right - left + wordLen == totalLen) {
                    result.push_back(left);
                }
            }
        }
        
        return result;
    }
};