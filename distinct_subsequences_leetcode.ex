defmodule Solution do
  @spec num_distinct(s :: String.t, t :: String.t) :: integer
  def num_distinct(s, t) do
    s_chars = String.to_charlist(s)
    t_chars = String.to_charlist(t)
    m = length(s_chars)
    n = length(t_chars)
    
    # Use 1D DP array for space optimization
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
end