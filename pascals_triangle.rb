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

# Alternative more Ruby-like solution
def generate_functional(num_rows)
    return [] if num_rows == 0
    
    (0...num_rows).reduce([]) do |triangle, i|
        row = if i == 0
                [1]
              else
                prev_row = triangle.last
                new_row = [1]  # Start with 1
                
                # Add middle elements
                (1...i).each do |j|
                    new_row << prev_row[j-1] + prev_row[j]
                end
                
                new_row << 1  # End with 1
                new_row
              end
        
        triangle << row
    end
end

# One-liner approach using map
def generate_oneliner(num_rows)
    return [] if num_rows == 0
    
    triangle = [[1]]
    
    (1...num_rows).each do |i|
        prev_row = triangle.last
        new_row = [1] + (1...i).map { |j| prev_row[j-1] + prev_row[j] } + [1]
        triangle << new_row
    end
    
    triangle
end

# Mathematical approach using combinations
def generate_math(num_rows)
    return [] if num_rows == 0
    
    (0...num_rows).map do |row|
        (0..row).map do |col|
            combination(row, col)
        end
    end
end

# Helper method to calculate combination C(n, k) = n! / (k! * (n-k)!)
def combination(n, k)
    return 1 if k == 0 || k == n
    
    # Optimize by using smaller k
    k = n - k if k > n - k
    
    result = 1
    (1..k).each do |i|
        result = result * (n - i + 1) / i
    end
    
    result
end

# Test the solutions
def run_tests
    puts "Testing Pascal's Triangle Solutions:"
    puts
    
    # Test case 1
    num_rows1 = 5
    puts "Test 1: numRows = #{num_rows1}"
    puts "Basic approach: #{generate(num_rows1)}"
    puts "Functional approach: #{generate_functional(num_rows1)}"
    puts "One-liner approach: #{generate_oneliner(num_rows1)}"
    puts "Mathematical approach: #{generate_math(num_rows1)}"
    puts "Expected: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]"
    puts
    
    # Test case 2
    num_rows2 = 1
    puts "Test 2: numRows = #{num_rows2}"
    puts "Basic approach: #{generate(num_rows2)}"
    puts "Functional approach: #{generate_functional(num_rows2)}"
    puts "One-liner approach: #{generate_oneliner(num_rows2)}"
    puts "Mathematical approach: #{generate_math(num_rows2)}"
    puts "Expected: [[1]]"
    puts
    
    # Test case 3 - Edge case
    num_rows3 = 3
    puts "Test 3: numRows = #{num_rows3}"
    puts "Basic approach: #{generate(num_rows3)}"
    puts "Expected: [[1],[1,1],[1,2,1]]"
    puts
    
    # Performance comparison for larger input
    num_rows4 = 10
    puts "Test 4: numRows = #{num_rows4}"
    
    require 'benchmark'
    
    Benchmark.bm(20) do |x|
        x.report("Basic approach:") { generate(num_rows4) }
        x.report("Functional approach:") { generate_functional(num_rows4) }
        x.report("One-liner approach:") { generate_oneliner(num_rows4) }
        x.report("Mathematical approach:") { generate_math(num_rows4) }
    end
end

# Run the tests
run_tests if __FILE__ == $0