# problem: https://leetcode.com/problems/two-sum/

class Solution:
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        
        sum_minus_x = {target - x: i for i, x in enumerate(nums)}
        
        for i, n in enumerate(nums):
            if n in sum_minus_x and sum_minus_x[n] != i:
                return i, sum_minus_x[n]
            
    
if __name__ == '__main__':
    nums = [3, 2, 4]
    target = 6
    
    s = Solution()
    
    print(s.twoSum(nums, target))
