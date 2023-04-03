#!/usr/bin/env python
#-*-coding:utf-8-*-

class Solution:
    def reverseString(self, s):
        """
        Do not return anything, modify s in-place instead.
        """
        i =0
        j =len(s)-1
        print(j)
        while i>j:
            s[i],s[j]=s[j],s[i]
            i+=1
            j-=1
        for item in s:
            print(item)
if __name__=="__main__":
    s = ["H","a","n","n","a","h"]
    su =Solution()
    su.reverseString(s)
    