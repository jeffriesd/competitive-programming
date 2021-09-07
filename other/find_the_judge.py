# problem: https://leetcode.com/problems/find-the-town-judge/

from collections import defaultdict

class Solution:
    def findJudge(self, N: int, trust: List[List[int]]) -> int:
        sums = defaultdict(int) 
        itrust = defaultdict(int) 
        
        if trust == []:
            return 1
        
        for x, y in trust:
            sums[y] += 1
            itrust[x] += 1
        
        for k in sums:
            if sums[k] == N - 1 and itrust[k] == 0:
                return k
        return -1
        
