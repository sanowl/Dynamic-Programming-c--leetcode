class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        int n = count.size(); // 256
        long long totalCount = 0;
        long long totalSum = 0;
        
        int minimum = -1, maximum = -1, mode = 0;
        int maxFreq = 0;
        
        // Single pass to calculate most statistics
        for (int i = 0; i < n; i++) {
            if (count[i] > 0) {
                // Update min/max
                if (minimum == -1) minimum = i;
                maximum = i;
                
                // Update total count and sum
                totalCount += count[i];
                totalSum += (long long)i * count[i];
                
                // Update mode
                if (count[i] > maxFreq) {
                    maxFreq = count[i];
                    mode = i;
                }
            }
        }
        
        // Calculate mean
        double mean = (double)totalSum / totalCount;
        
        // Calculate median
        double median = calculateMedian(count, totalCount);
        
        return {(double)minimum, (double)maximum, mean, median, (double)mode};
    }
    
private:
    double calculateMedian(vector<int>& count, long long totalCount) {
        long long mid1 = (totalCount + 1) / 2; // 1-indexed middle position
        long long mid2 = (totalCount + 2) / 2; // 1-indexed second middle position
        
        long long runningCount = 0;
        double median1 = -1, median2 = -1;
        
        for (int i = 0; i < count.size(); i++) {
            if (count[i] > 0) {
                runningCount += count[i];
                
                // Find first middle element
                if (median1 == -1 && runningCount >= mid1) {
                    median1 = i;
                }
                
                // Find second middle element
                if (median2 == -1 && runningCount >= mid2) {
                    median2 = i;
                    break; // Found both, can exit
                }
            }
        }
        
        // For odd count: mid1 == mid2, so average is just that value
        // For even count: average of two middle elements
        return (median1 + median2) / 2.0;
    }
};