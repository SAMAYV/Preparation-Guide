# ❯ Second problem:                                                                                                                                                                                                 
                                                                                                                                                                                                                  
#     Score ofa sequence in defined as the result of the bitwise OR operation on its elements.                                                                                                                      
                                                                                                                                                                                                                  
#     Given an arr, identfy all possible distinct scores that can be obtained by selecting any strictly increasing subsequence from teh arr. Return the results sorted in ascending order                           
                                                                                                                                                                                                                  
#   n <= 10**4                                                                                                                                                                                                      
#   1 <= arr[i] <= 1024

def distinct_increasing_or_scores(arr):
    V = 1024
    end = [0] * (V + 1)          # end[v] = bitmask of scores for subseqs ending at value v

    for a in arr:
        # union of all score-sets ending with a strictly smaller value
        prefix = 0
        for w in range(1, a):
            prefix |= end[w]
        # extend each of those scores with a, plus the singleton {a}
        new_mask = 1 << a
        m = prefix
        while m:
            low = m & -m
            new_mask |= 1 << ((low.bit_length() - 1) | a)
            m ^= low
        end[a] |= new_mask

    # union everything, then read out set bits low->high (already ascending)
    all_scores = 0
    for v in range(1, V + 1):
        all_scores |= end[v]

    result = []
    m = all_scores
    while m:
        low = m & -m
        result.append(low.bit_length() - 1)
        m ^= low
    return result

# ❯ A pair od integers (x, y) is perfect if both the following conditions are met:                                                                                                                                  
#   min(abs(x-y), (x + y)) <= min(abs(x), abs(y))                                                                                                                                                                   
#   max(same) >= max(same)                                                                                                                                                                                          
                                                                                                                                                                                                                  
#   given an array, find the NUMBER of perfect pairs                                                                                                                                                                
  
# ⏺ Nice — this is the classic "Perfect Pairs" problem, and the key is to simplify the conditions first.

#   Math simplification: For any integers, there's an identity:
#   - max(|x−y|, |x+y|) = |x| + |y|
#   - min(|x−y|, |x+y|) = ||x| − |y||
  
#   Let a = min(|x|,|y|), b = max(|x|,|y|). The two conditions become:
#   - b − a <= a  →  b <= 2a
#   - a + b >= b  →  always true
  
#   So a pair is perfect iff max(|x|,|y|) <= 2 * min(|x|,|y|).

def count_perfect_pairs(nums):
    # Work on absolute values; sign never matters after the simplification.
    b = sorted(abs(x) for x in nums)

    res = 0
    left = 0
    # b is ascending, so for index `right`: min = b[left..], max = b[right]
    for right in range(len(b)):
        # Shrink window from the left until max <= 2*min holds.
        while b[right] > 2 * b[left]:
            left += 1
        # All indices in [left, right-1] pair validly with `right`.
        res += right - left
    return res