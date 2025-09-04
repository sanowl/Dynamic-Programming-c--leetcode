def solve():
    n = int(input())
    intervals = []
    
    for i in range(n):
        l, r = map(int, input().split())
        intervals.append((l, r, i))  # (start, end, original_index)
    
    # Sort intervals by start time, then by end time
    intervals.sort()
    
    # Track colors assigned to each original interval
    colors = [0] * n
    
    # Track active intervals and their colors
    active_intervals = []  # List of (end_time, color)
    next_color = 1
    
    for start, end, original_idx in intervals:
        # Remove intervals that have ended (end < start, not end <= start for this problem)
        active_intervals = [(e, c) for e, c in active_intervals if e >= start]
        
        # Find the smallest color not currently in use
        used_colors = set(color for _, color in active_intervals)
        color = 1
        while color in used_colors:
            color += 1
        
        colors[original_idx] = color
        next_color = max(next_color, color + 1)
        
        # Add current interval to active list
        active_intervals.append((end, color))
    
    # Output results  
    max_color = max(colors) if colors else 0
    print(max_color)
    print(*colors)

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == "__main__":
    main()