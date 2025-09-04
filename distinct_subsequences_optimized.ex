defmodule Solution do
  @spec num_distinct(s :: String.t, t :: String.t) :: integer
  def num_distinct(s, t) do
    m = String.length(s)
    n = String.length(t)
    
    # Early optimization: if t is longer than s, impossible
    if n > m, do: 0, else: solve_with_map(s, t, m, n)
  end
  
  # Use map for better performance than list operations
  defp solve_with_map(s, t, m, n) do
    # Initialize DP map
    dp = for j <- 0..n, into: %{}, do: {j, if(j == 0, do: 1, else: 0)}
    
    # Process each character in s
    for i <- 1..m, reduce: dp do
      acc ->
        s_char = String.at(s, i - 1)
        
        # Process from right to left using map operations
        for j <- n..1, reduce: acc do
          dp_acc ->
            if String.at(t, j - 1) == s_char do
              current_val = Map.get(dp_acc, j, 0)
              prev_val = Map.get(dp_acc, j - 1, 0)
              Map.put(dp_acc, j, current_val + prev_val)
            else
              dp_acc
            end
        end
    end
    |> Map.get(n, 0)
  end
end