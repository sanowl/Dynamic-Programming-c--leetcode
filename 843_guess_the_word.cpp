/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    void findSecretWord(vector<string>& words, Master& master) {
        vector<string> candidates = words;
        
        for (int attempt = 0; attempt < 10 && !candidates.empty(); attempt++) {
            // Choose word with maximum diversity (minimum expected remaining candidates)
            string guess = chooseOptimalWord(candidates);
            
            int matches = master.guess(guess);
            
            // If we found the secret word
            if (matches == 6) {
                return;
            }
            
            // Filter candidates based on the number of matches
            vector<string> newCandidates;
            for (const string& word : candidates) {
                if (countMatches(guess, word) == matches) {
                    newCandidates.push_back(word);
                }
            }
            candidates = newCandidates;
        }
    }
    
private:
    // Count exact matches between two words
    int countMatches(const string& word1, const string& word2) {
        int matches = 0;
        for (int i = 0; i < 6; i++) {
            if (word1[i] == word2[i]) {
                matches++;
            }
        }
        return matches;
    }
    
    // Enhanced strategy with random selection for similar words
    string chooseOptimalWord(const vector<string>& candidates) {
        if (candidates.size() <= 2) {
            return candidates[0];
        }
        
        // Check if words are very similar (high average similarity)
        int totalSimilarity = 0;
        int comparisons = 0;
        
        for (int i = 0; i < min(10, (int)candidates.size()); i++) {
            for (int j = i + 1; j < min(10, (int)candidates.size()); j++) {
                totalSimilarity += countMatches(candidates[i], candidates[j]);
                comparisons++;
            }
        }
        
        double avgSimilarity = comparisons > 0 ? (double)totalSimilarity / comparisons : 0;
        
        // If words are very similar (avg > 4 matches), use random strategy
        if (avgSimilarity > 4.0 && candidates.size() > 10) {
            // Pick a word that has 0 matches with many others (maximize elimination)
            string bestGuess = candidates[0];
            int maxZeroMatches = 0;
            
            for (const string& guess : candidates) {
                int zeroMatches = 0;
                for (const string& word : candidates) {
                    if (countMatches(guess, word) == 0) {
                        zeroMatches++;
                    }
                }
                if (zeroMatches > maxZeroMatches) {
                    maxZeroMatches = zeroMatches;
                    bestGuess = guess;
                }
            }
            return bestGuess;
        }
        
        // Use minimax strategy for normal cases
        string bestGuess = candidates[0];
        int minMaxGroupSize = candidates.size();
        
        for (const string& guess : candidates) {
            unordered_map<int, int> groups;
            for (const string& word : candidates) {
                int matches = countMatches(guess, word);
                groups[matches]++;
            }
            
            int maxGroupSize = 0;
            for (auto& pair : groups) {
                maxGroupSize = max(maxGroupSize, pair.second);
            }
            
            if (maxGroupSize < minMaxGroupSize) {
                minMaxGroupSize = maxGroupSize;
                bestGuess = guess;
            }
        }
        
        return bestGuess;
    }
};