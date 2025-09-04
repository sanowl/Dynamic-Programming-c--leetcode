import sys

def solve():
    n = int(input())
    
    # Track which original box is at each position
    at_pos = list(range(n + 1))  # at_pos[i] = original box number at position i
    powers = [0] * (n + 1)  # powers of original boxes
    determined = [False] * (n + 1)
    queries = 0
    
    # Simple strategy: test each position individually
    for pos in range(1, n + 1):
        if queries >= (3 * n + 1) // 2:
            break
            
        # Throw from current position
        print(f"throw {pos}")
        sys.stdout.flush()
        queries += 1
        
        jumps = int(input())
        
        # Determine power based on the number of jumps
        if pos + 1 > n:
            # Last position - if 1 jump, power is 1
            powers[at_pos[pos]] = 1
        elif pos + 2 > n:
            # Second to last - if 1 jump power is 2, if more jumps power is 1
            if jumps == 1:
                powers[at_pos[pos]] = 2
            else:
                powers[at_pos[pos]] = 1
        else:
            # For earlier positions, use a different strategy
            # Move the box to the end and test in isolation
            original_box = at_pos[pos]
            
            # Move this box to position n
            current_pos = pos
            while current_pos < n and queries < (3 * n + 1) // 2:
                print(f"swap {current_pos}")
                sys.stdout.flush()
                queries += 1
                
                # Update tracking
                at_pos[current_pos], at_pos[current_pos + 1] = at_pos[current_pos + 1], at_pos[current_pos]
                current_pos += 1
            
            # Now test the box at position n
            if queries < (3 * n + 1) // 2:
                print(f"throw {n}")
                sys.stdout.flush()
                queries += 1
                
                isolated_jumps = int(input())
                if isolated_jumps == 1:
                    powers[original_box] = 1
                else:
                    powers[original_box] = 2
            
            determined[original_box] = True
            
            # Move the box back (optional, but helps maintain order)
            while current_pos > pos and queries < (3 * n + 1) // 2:
                print(f"swap {current_pos - 1}")
                sys.stdout.flush()
                queries += 1
                
                at_pos[current_pos], at_pos[current_pos - 1] = at_pos[current_pos - 1], at_pos[current_pos]
                current_pos -= 1
        
        if not determined[at_pos[pos]]:
            determined[at_pos[pos]] = True
    
    # Fill in any undetermined boxes with educated guesses
    for i in range(1, n + 1):
        if powers[i] == 0:
            powers[i] = 1  # Default guess
    
    # Output answer
    print("!", end="")
    for i in range(1, n + 1):
        print(f" {powers[i]}", end="")
    print()
    sys.stdout.flush()

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == "__main__":
    main()