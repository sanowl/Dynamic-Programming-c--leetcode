defmodule DistinctSubsequences do
  @doc """
  Counts the number of distinct subsequences of s which equals t.
  Uses 2D dynamic programming approach.
  
  ## Examples
      
      iex> DistinctSubsequences.num_distinct("rabbbit", "rabbit")
      3
      
      iex> DistinctSubsequences.num_distinct("babgbag", "bag") 
      5
  """
  def num_distinct(s, t) do
    s_chars = String.to_charlist(s)
    t_chars = String.to_charlist(t)
    m = length(s_chars)
    n = length(t_chars)
    
    # Initialize DP table with 0s
    dp = for _ <- 0..m, do: for _ <- 0..n, do: 0
    
    # Base case: empty string t can be formed in 1 way from any string s
    dp = for i <- 0..m, reduce: dp do
      acc -> List.replace_at(acc, i, List.replace_at(Enum.at(acc, i), 0, 1))
    end
    
    # Fill the DP table
    fill_dp(dp, s_chars, t_chars, 1, 1, m, n)
  end
  
  # Space optimized version using 1D array
  def num_distinct_optimized(s, t) do
    s_chars = String.to_charlist(s)
    t_chars = String.to_charlist(t)
    m = length(s_chars)
    n = length(t_chars)
    
    # Initialize 1D DP array
    dp = [1] ++ for _ <- 1..n, do: 0
    
    # Process each character in s
    Enum.with_index(s_chars)
    |> Enum.reduce(dp, fn {s_char, i}, acc ->
      # Process from right to left to avoid overwriting values we need
      Enum.reduce(n..1, acc, fn j, dp_acc ->
        t_char = Enum.at(t_chars, j - 1)
        if s_char == t_char do
          current_val = Enum.at(dp_acc, j)
          prev_val = Enum.at(dp_acc, j - 1)
          List.replace_at(dp_acc, j, current_val + prev_val)
        else
          dp_acc
        end
      end)
    end)
    |> Enum.at(n)
  end
  
  # Recursive solution with memoization
  def num_distinct_recursive(s, t) do
    s_chars = String.to_charlist(s)
    t_chars = String.to_charlist(t)
    memo = %{}
    
    {result, _} = helper(s_chars, t_chars, 0, 0, memo)
    result
  end
  
  # Helper function for filling DP table
  defp fill_dp(dp, s_chars, t_chars, i, j, m, n) when i > m do
    # Return the final result
    Enum.at(Enum.at(dp, m), n)
  end
  
  defp fill_dp(dp, s_chars, t_chars, i, j, m, n) when j > n do
    # Move to next row
    fill_dp(dp, s_chars, t_chars, i + 1, 1, m, n)
  end
  
  defp fill_dp(dp, s_chars, t_chars, i, j, m, n) do
    s_char = Enum.at(s_chars, i - 1)
    t_char = Enum.at(t_chars, j - 1)
    
    # Always have the option to skip current character in s
    skip_val = Enum.at(Enum.at(dp, i - 1), j)
    
    new_val = if s_char == t_char do
      # If characters match, we can also use the current character
      use_val = Enum.at(Enum.at(dp, i - 1), j - 1)
      skip_val + use_val
    else
      skip_val
    end
    
    # Update DP table
    new_row = List.replace_at(Enum.at(dp, i), j, new_val)
    new_dp = List.replace_at(dp, i, new_row)
    
    # Continue to next column
    fill_dp(new_dp, s_chars, t_chars, i, j + 1, m, n)
  end
  
  # Helper function for recursive solution
  defp helper(s_chars, t_chars, i, j, memo) do
    cond do
      # Base cases
      j == length(t_chars) -> {1, memo}  # Found a valid subsequence
      i == length(s_chars) -> {0, memo}  # No more characters in s
      
      # Check memoization
      Map.has_key?(memo, {i, j}) -> {Map.get(memo, {i, j}), memo}
      
      true ->
        # Always have the option to skip current character in s
        {skip_result, memo1} = helper(s_chars, t_chars, i + 1, j, memo)
        
        result = if Enum.at(s_chars, i) == Enum.at(t_chars, j) do
          # If characters match, we can also use the current character
          {use_result, memo2} = helper(s_chars, t_chars, i + 1, j + 1, memo1)
          skip_result + use_result
        else
          skip_result
        end
        
        new_memo = Map.put(memo1, {i, j}, result)
        {result, new_memo}
    end
  end
  
  # Test function
  def run_tests do
    IO.puts("Testing Distinct Subsequences Solutions:")
    IO.puts("")
    
    # Test case 1
    s1 = "rabbbit"
    t1 = "rabbit"
    IO.puts("Test 1:")
    IO.puts("s = \"#{s1}\", t = \"#{t1}\"")
    IO.puts("2D DP: #{num_distinct(s1, t1)}")
    IO.puts("1D DP: #{num_distinct_optimized(s1, t1)}")
    IO.puts("Recursive: #{num_distinct_recursive(s1, t1)}")
    IO.puts("Expected: 3")
    IO.puts("")
    
    # Test case 2
    s2 = "babgbag"
    t2 = "bag"
    IO.puts("Test 2:")
    IO.puts("s = \"#{s2}\", t = \"#{t2}\"")
    IO.puts("2D DP: #{num_distinct(s2, t2)}")
    IO.puts("1D DP: #{num_distinct_optimized(s2, t2)}")
    IO.puts("Recursive: #{num_distinct_recursive(s2, t2)}")
    IO.puts("Expected: 5")
    IO.puts("")
    
    # Test case 3
    s3 = "aaa"
    t3 = "aa"
    IO.puts("Test 3:")
    IO.puts("s = \"#{s3}\", t = \"#{t3}\"")
    IO.puts("2D DP: #{num_distinct(s3, t3)}")
    IO.puts("1D DP: #{num_distinct_optimized(s3, t3)}")
    IO.puts("Recursive: #{num_distinct_recursive(s3, t3)}")
    IO.puts("Expected: 3")
    IO.puts("")
    
    # Edge case: empty t
    s4 = "abc"
    t4 = ""
    IO.puts("Test 4:")
    IO.puts("s = \"#{s4}\", t = \"#{t4}\"")
    IO.puts("2D DP: #{num_distinct(s4, t4)}")
    IO.puts("1D DP: #{num_distinct_optimized(s4, t4)}")
    IO.puts("Recursive: #{num_distinct_recursive(s4, t4)}")
    IO.puts("Expected: 1")
  end
end

# Run the tests
DistinctSubsequences.run_tests()