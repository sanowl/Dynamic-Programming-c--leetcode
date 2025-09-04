# @param {Integer} num_rows
# @return {Integer[][]}
def generate(num_rows)
    return [] if num_rows == 0
    
    triangle = []
    
    # Generate each row
    (0...num_rows).each do |i|
        row = Array.new(i + 1, 1)  # Initialize row with 1s
        
        # Fill middle elements (if any)
        (1...i).each do |j|
            row[j] = triangle[i-1][j-1] + triangle[i-1][j]
        end
        
        triangle << row
    end
    
    triangle
end