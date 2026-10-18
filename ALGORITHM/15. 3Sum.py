class Solution:
    def threeSum(self, nums: list[int]) -> list[list[int]]:
        """找出数组中所有和为 0 的不重复三元组。

        先将 ``nums`` 原地升序排序。随后依次固定一个元素 ``nums[index]``，
        并用左右指针在其右侧区间查找和为其相反数的两个元素。若三数之和
        大于 0，则右指针左移以减小总和；若小于 0，则左指针右移以增大总和。
        找到解后记录三元组并同时移动两指针。

        为避免重复结果，固定元素与前一个相同时跳过；每次命中后，也跳过
        左右两侧连续的重复值。数组已经排序，当固定值大于 0 时，后续元素
        也都大于 0，不可能再组成和为 0 的三元组，因此可以提前结束。

        Args:
            nums: 整数列表。方法会对该列表原地排序。

        Returns:
            所有和为 0 的不重复三元组；每个三元组按非递减顺序排列。

        Complexity:
            时间复杂度 O(n^2)；排序通常需要 O(n log n)，除返回结果外，
            双指针搜索额外空间为 O(1)。
        """
        # 排序使双指针能根据总和的大小决定移动方向，也便于跳过重复值。
        result=[]
        nums.sort()
        # 依次将每个元素作为三元组中的第一个数。
        for index in range(len(nums)):
            # 固定值已大于 0 时，后续数也都大于 0，无法得到和为 0 的组合。
            if nums[index]>0:
                break
            # 相同的固定值只需搜索一次，避免生成重复三元组。
            if index>0 and nums[index]==nums[index-1]:
                continue
            # 在固定值右侧设置双指针，寻找另外两个数。
            left_index,right_index=index+1,len(nums)-1
            while left_index<right_index:
                Sum=nums[index]+nums[left_index]+nums[right_index]
                if Sum>0:
                    # 总和过大，减小右侧数值。
                    right_index-=1
                elif Sum<0:
                    # 总和过小，增大左侧数值。
                    left_index+=1
                else:
                    # 找到一组解；排序保证三元组内部为非递减顺序。
                    result.append([nums[index],nums[left_index],nums[right_index]])
                    right_index-=1
                    left_index+=1
                    # 跳过重复的左侧数值，防止同一三元组再次出现。
                    while left_index<right_index and nums[left_index]==nums[left_index-1]:
                            left_index+=1
                    # 跳过重复的右侧数值，防止同一三元组再次出现。
                    while left_index<right_index and nums[right_index]==nums[right_index+1]:
                        right_index-=1
        return result