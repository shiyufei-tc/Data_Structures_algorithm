class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:
        """将字符串列表中的异位词分组。

        异位词由相同的字符组成，字符出现次数也相同，但字符顺序可以不同。
        例如 ``eat``、``tea`` 和 ``ate`` 排序后都会变成 ``aet``，因此可以
        使用排序后的字符串作为哈希表的键，把它们放入同一个分组中。

        Args:
            strs: 待分组的字符串列表。

        Returns:
            一个二维列表，每个子列表包含一组互为异位词的字符串。

        Complexity:
            设共有 n 个字符串，每个字符串的平均长度为 k，
            时间复杂度为 O(n * k log k)，空间复杂度为 O(n * k)。
        """
        # 哈希表的键是字符串排序后的结果，值是拥有相同键的原字符串列表。
        hash_map={}

        # 逐个处理输入字符串，确保每个字符串都被放入对应分组。
        for str_e in strs:
            # 将当前字符串的字符排序并重新拼接，生成唯一的分组标识。
            # 异位词的字符及其出现次数相同，所以排序结果一定相同。
            str_e_sort=''.join(sorted(str_e))

            # 第一次遇到某个排序键时，先创建一个空列表。
            if str_e_sort not in hash_map:
                hash_map[str_e_sort]=[]

            # 将原字符串追加到对应的异位词分组中，保留其原始形式。
            hash_map[str_e_sort].append(str_e)

        # 只保留哈希表中的分组内容，不再需要返回排序键。
        all_list=list(hash_map.values())
        return all_list
                

