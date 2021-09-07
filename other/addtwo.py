# problem:https://leetcode.com/problems/add-two-numbers/


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def addTwoNumbers(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        
        a = l1
        b = l2
        ans = None
        
        carry = 0
        
        while a or b:
            a_val = a.val if a else 0
            b_val = b.val if b else 0
            sum_ab = a_val + b_val + carry
            dig = sum_ab % 10
            carry = sum_ab // 10
            
            if ans:
                c.next = ListNode(dig)
                c = c.next
            else:
                ans = ListNode(dig)
                c = ans
                
            
            a = a.next if a else None
            b = b.next if b else None
            
        if carry:
            c.next = ListNode(carry)
        
        return ans
