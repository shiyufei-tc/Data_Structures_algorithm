class Solution:
    def firstUniqChar(self, s: str) -> int:
        """返回字符串中第一个只出现一次的字符下标。

        这个问题的核心思路分为两步：
        1. 先遍历字符串统计每个字符出现次数；
        2. 再从左到右扫描原字符串，找到第一个出现次数为 1 的字符并返回它的下标。

        Args:
            s: 输入字符串。

        Returns:
            第一个只出现一次字符的下标；如果不存在，则返回 -1。

        Complexity:
            时间复杂度：O(n)
            空间复杂度：O(k)，其中 k 是字符集大小。
        """
        # 使用哈希表记录每个字符出现的次数。
        hash_map={}

        # 第一次遍历：初始化hash_map的数据并且统计每个字符的频次。
        for word in s:
            hash_map[word]=hash_map.get(word,0)+1

        # 第二次遍历：从左到右扫描字符串，找到第一个出现次数为 1 的字符。
        for i,word in enumerate(s):
            if hash_map[word]==1:
                return i

        # 若所有字符都出现了至少两次，则返回 -1。
        return -1