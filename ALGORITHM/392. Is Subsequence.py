class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        """判断字符串 s 是否为字符串 t 的子序列。

        子序列要求：在 t 中按原顺序出现，且可以不连续地保留字符。
        例如 s = "abc"，t = "aebdc"，因为 a、b、c 在 t 中按顺序出现，
        所以返回 True。

        Args:
            s: 需要判断是否为子序列的字符串。
            t: 目标字符串，搜索源串。

        Returns:
            若 s 是 t 的子序列，则返回 True；否则返回 False。

        Complexity:
            时间复杂度：O(len(t))
            空间复杂度：O(1)
        """
        # i 指向 s 中当前匹配到的位置，j 指向 t 中当前扫描的位置。
        i = 0
        j = 0

        # 双指针同时前进：
        # - 若当前字符相同，说明 s 的一个字符已在 t 中匹配成功，
        #   两个指针都向后移动一位；
        # - 若不同，只让 j 向后扫 t，继续寻找后面的字符。
        while i < len(s) and j < len(t):
            if s[i] == t[j]:
                i +=1
                j +=1

            else:
                j +=1

        # 如果 s 的所有字符都被成功匹配完，则说明 s 是 t 的子序列。
        if i == len(s):
            return True
        else:
            return False