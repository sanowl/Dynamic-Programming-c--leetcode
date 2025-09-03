import sys

def solve():
    t = int(input())
    
    for _ in range(t):
        W = -1
        
        # First query: test with word of length 1
        print("? 1 1")
        sys.stdout.flush()
        
        response = int(input())
        
        if response == 0:
            # W < 1, impossible since W >= 1
            W = 1
        else:
            # W >= 1, now find exact value using binary search
            left = 1
            right = 100000
            
            while left <= right:
                mid = left + (right - left) // 2
                
                print(f"? 1 {mid}")
                sys.stdout.flush()
                
                response = int(input())
                
                if response == 0:
                    right = mid - 1
                else:
                    left = mid + 1
                    W = mid
        
        print(f"! {W}")
        sys.stdout.flush()

if __name__ == "__main__":
    solve()