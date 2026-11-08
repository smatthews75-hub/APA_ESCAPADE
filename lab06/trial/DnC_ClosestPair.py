import math

def distance(p1, p2):
    """Calculates the Euclidean distance between two points."""
    return math.hypot(p1[0] - p2[0], p1[1] - p2[1])

def exhaustive_search(L):
    """Base case: exhaustive search for n <= 3."""
    min_d = float('inf')
    n = len(L)
    for i in range(n):
        for j in range(i + 1, n):
            d = distance(L[i], L[j])
            if d < min_d:
                min_d = d
    return min_d

def HandleTrickyCase(L1, L2, d):
    """Evaluates the straddling points within the boundary strip."""
    # The dividing line is the x-coordinate of the last point in the left half
    mid_x = L1[-1][0]
    
    # Build the strip of points within distance 'd' of the dividing line
    strip = []
    for point in L1 + L2:
        if abs(point[0] - mid_x) < d:
            strip.append(point)
            
    # Sort the strip by y-coordinate
    strip.sort(key=lambda p: p[1])
    
    # Check points in the strip
    d_min = d
    n = len(strip)
    for i in range(n):
        # We only need to check at most the next 7 points
        for j in range(i + 1, min(i + 8, n)):
            strip_d = distance(strip[i], strip[j])
            if strip_d < d_min:
                d_min = strip_d
                
    return d_min

def ClosestPairDnC(L):
    """Recursive Divide and Conquer function."""
    n = len(L)
    
    if n <= 3:
        return exhaustive_search(L)
    else:
        # Python slicing uses half-open intervals [left, right)
        mid = n // 2
        L1 = L[0:mid]
        L2 = L[mid:n]
        
        d1 = ClosestPairDnC(L1)
        d2 = ClosestPairDnC(L2)
        d = min(d1, d2)
        
        d_min = HandleTrickyCase(L1, L2, d)
        
        return d_min

def ClosestPair(L):
    """Wrapper function to handle the initial sorting."""
    # Input(L)
    # Sort L by the x coordinate
    L.sort(key=lambda p: p[0]) 
    return ClosestPairDnC(L)

# --- Example Usage ---
if __name__ == "__main__":
    dataset = [(2, 3), (12, 30), (40, 50), (5, 1), (12, 10), (3, 4)]
    
    shortest_distance = ClosestPair(dataset)
    print(f"Shortest distance: {shortest_distance:.4f}")