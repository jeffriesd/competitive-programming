# problem: https://leetcode.com/problems/palindrome-linked-list/

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def isPalindrome(self, head):
        """
        :type head: ListNode
        :rtype: bool
        """
        cur = head
        count = 0
        while cur:
            cur = cur.next
            count += 1

        prev = head
        prevprev = None
        cur = head
        for _ in range((count+1)//2):
          prev = cur
          cur = cur.next
          prev.next = prevprev
          prevprev = prev

        # if odd, prev is on middle element
        if count % 2 != 0:
          prev = prev.next

        while prev and cur:
          if prev.val != cur.val:
            return False
          prev = prev.next
          cur = cur.next
        return True

        
