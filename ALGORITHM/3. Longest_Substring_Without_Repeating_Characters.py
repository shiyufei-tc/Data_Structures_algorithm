class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        """返回字符串中不含重复字符的最长子串长度。

        使用滑动窗口从左到右遍历字符串，并通过哈希表记录每个字符最近一次
        出现的位置。当发现重复字符时，将窗口左边界移动到该字符上次出现
        位置的右侧，从而保证窗口内始终没有重复字符。

        Args:
            s: 待查找的字符串。

        Returns:
            不含重复字符的最长连续子串的长度。空字符串返回 0。

        Complexity:
            时间复杂度为 O(n)，空间复杂度为 O(min(n, 字符集大小))，其中 n
            是字符串长度。
        """
        # 使用滑动窗口维护当前的无重复字符子串。
        # 窗口范围为 [left + 1, right]，其中 left 指向窗口左边界的前一位。
        # hash_map 保存每个字符最近一次出现的下标，便于重复时直接移动左边界。
        hash_map={}
        left=-1
        right=0
        max_len=0

        while right<len(s):
            # 如果当前字符已经在窗口中出现过，窗口左边界必须越过它上一次出现的位置。
            # max 的作用是防止 left 向左移动：只允许窗口缩小或向右滑动。
            if s[right] in hash_map:
                left=max(left,hash_map[s[right]])

            # 当前窗口长度为 right - left。
            # 因为 left 是窗口左边界的前一位，所以这里不需要额外加 1。
            # 记录遍历过程中遇到的最大窗口长度；当窗口覆盖整个字符串时，第二个条件也会确保结果更新为字符串长度。
            if (right-left)>max_len or (right-left)==len(s):
                max_len=(right-left)

            # 更新当前字符的最近位置，供后续遇到相同字符时使用。
            hash_map[s[right]]=right
            right+=1

        # 每个字符最多被 right 和 hash_map 各处理一次，时间复杂度为 O(n)，
        # hash_map 最多保存 n 个字符，空间复杂度为 O(min(n, 字符集大小))。
        return max_len

