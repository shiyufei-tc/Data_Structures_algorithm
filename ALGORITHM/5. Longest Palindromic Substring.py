class Solution:
    def longestPalindrome(self, s: str) -> str:
        """返回字符串中最长回文子串。

        该实现采用“中心扩展”的思想：遍历每个中心位置，分别尝试扩展奇数长度
        和偶数长度回文，并利用左右指针持续更新当前能找到的最大回文长度。
        代码中通过多个边界判断来处理字符串开头、结尾以及重复字符场景。

        Args:
            s: 输入字符串。

        Returns:
            字符串中最长回文子串。如果不存在回文，则返回空字符串。

        Complexity:
            时间复杂度约为 O(n^2)，空间复杂度为 O(1)。
        """
        # current 表示当前正在检查的中心字符位置。
        current=0
        # Max 记录当前找到的最大回文长度。
        Max=0
        # real_left / real_right 保存当前最大回文的左右边界索引。
        real_left=-1
        real_right=-1

        while current<len(s):
            # v_left / v_right ，处理类似"cbbd"情况，表示把current当作虚假的 left/right
            # t_left / t_right 处理类似"cbbd"情况时，用于在current前后扩展
            # 帮助处理奇偶回文交织的情况
            v_left,v_right=current,current
            left,right=current-1,current+1
            t_left,t_right=left,right

            # 处理当前字符后面存在连续相同字符的情况，例如 "aab"。
            # 这类情况可形成一个以 current 为中心的扩展回文。
            if left<0:
                while right<len(s) and s[current]==s[right] :
                    right+=1
                start_max=right-current
                if Max<start_max:
                    Max=start_max
                    real_left=0
                    real_right=right

            # 处理当前字符前面存在连续相同字符的情况，例如 "baa"。
            # 这里从 left 开始向左扩展，相当于对称地处理前缀重复。
            if right>=len(s):
                while left>=0 and s[current]==s[left]:
                    left-=1
                end_max=current-left
                if Max<end_max:
                    Max=end_max
                    real_left=left
                    real_right=0

            # 核心中心扩展循环：在当前中心附近不断比较左右字符是否相等。
            # 若相等，则左右指针同时向外扩展；若不等，则尝试别的候选边界继续推进。
            while left>=0 and right<len(s):
                if s[left]==s[right]:
                    # 正常回文扩展：左右同时向外扩展。
                    left-=1
                    right+=1
                elif t_right<len(s) and v_left>=0  and s[t_right]==s[v_left]:
                    # 向左扩展：左边界继续向左移动，右边界也更新为更靠左的候选位置。
                    v_left-=1
                    t_right+=1
                elif t_left>=0 and v_right<len(s)  and s[t_left]==s[v_right]:
                    # 向右扩展：右边界继续向右移动，左边界也更新为更靠右的候选位置。
                    v_right+=1
                    t_left-=1
                else:
                    break

            # 记录不同候选扩展结果中的最大回文长度。
            t_max=t_right-v_left
            if Max<t_max:
                Max=t_max
                real_left=v_left
                real_right=t_right

            v_max=v_right-t_left
            if Max<v_max:
                Max=v_max
                real_left=t_left
                real_right=v_right

            normal_max=right-left
            if Max<normal_max:
                Max=normal_max
                real_left=left
                real_right=right

            current+=1

        # 由于使用了左闭右开区间，切片时需要加 1 才能得到正确的起点索引。
        return s[real_left+1:real_right:]


class Solution:
    def longestPalindrome(self, s: str) -> str:
        """返回字符串中最长回文子串的另一种常见实现。

        这个版本采用“中心扩展 + 跳过无效中心”的优化思路：
        先找到每一段相同字符的连续区间，再在这些中心附近扩展回文。
        若 current 已经无法再形成更长回文，提前退出，减少无意义比较。

        Args:
            s: 输入字符串。

        Returns:
            最长回文子串。

        Complexity:
            时间复杂度：O(n^2)
            空间复杂度：O(1)
        """
        # 如果长度小于等于 1，或者本身就是回文，直接返回原串。
        n = len(s)
        if n <= 1 or s == s[::-1]:
            return s

        # start 表示当前最长回文的起始位置，max_len 表示最大长度。
        start, max_len = 0, 1
        i = 0

        # 遍历每一个中心位置，尝试寻找以该位置为起点的最长回文。
        while i < n:
            # 如果剩余字符长度不足以更新当前最大长度的一半，直接结束循环。
            # 这是剪枝优化：当前最多只可能形成更短的回文，不值得继续搜索。
            if (n - i) <= max_len // 2:
                break

            # 先把 l 和 r 置为当前中心位置，准备处理偶数/奇数回文。
            l = r = i

            # 处理重复字符的连续块，例如 "aaa"，先把相同字符都归并到一起。
            while r < n - 1 and s[r] == s[r + 1]:
                r += 1

            # 从最右端的重复字符后一个位置继续向后搜索，避免重复扫描。
            i = r + 1

            # 在当前重复块左右两侧继续扩展，寻找更长回文。
            while r < n - 1 and l > 0 and s[r + 1] == s[l - 1]:
                r += 1
                l -= 1

            # 计算当前候选回文长度，并更新全局最大值。
            length = r - l + 1
            if length > max_len:
                start = l
                max_len = length

        return s[start:start + max_len]