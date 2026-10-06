#include<iostream>
#include<vector>

/**
 * @brief 在有序数组中递归查找目标值的位置。
 *
 * 二分查找的核心思想是：每次比较中间元素后，将搜索区间缩小到前半段或后半段。
 * 因为数组是有序的，所以每次比较都能排除掉一半元素，避免线性扫描的 O(n)
 * 时间复杂度。递归版本非常适合梳理“边界收缩”和“终止条件”的思路。
 *
 * @param my_list 待查找的有序整数数组。
 * @param target 需要查找的目标值。
 * @param left 搜索区间左边界，默认从 0 开始。
 * @param right 搜索区间右边界，若不传入则在函数内设为数组最后一个元素下标。
 * @return 若找到目标值，返回其索引；否则返回 -1。
 *
 * @complexity 时间复杂度 O(log n)，空间复杂度 O(log n)（递归调用栈）。
 */
int binary_search(const std::vector<int>& my_list, int target, int left = 0, int right = -1)
{
    // 若未传入右边界，则默认将右边界设为整个数组的最后一个元素。
    if (right == -1)
    {
        right = static_cast<int>(my_list.size()) - 1;
    }

    // 当前区间为空时，说明搜索范围已被排除完，查找失败。
    if (left > right)
    {
        return -1;
    }

    // 计算中间位置，避免直接相加导致溢出。
    int middle = left + (right - left) / 2;

    // 若中间元素正好等于目标值，则直接返回其索引。
    if (my_list[middle] == target)
    {
        return middle;
    }
    // 若中间元素大于目标值，说明目标位于左半区间。
    else if (my_list[middle] > target)
    {
        return binary_search(my_list, target, left, middle - 1);
    }
    // 若中间元素小于目标值，说明目标位于右半区间。
    else
    {
        return binary_search(my_list, target, middle + 1, right);
    }
}

/**
 * @brief 在有序数组中使用循环实现二分查找。
 *
 * 这是一种非递归版本的二分查找，思路与递归版本一致：
 * 每轮都在当前区间 [left, right] 中找出中间位置，并根据中间值与 target
 * 的大小关系更新左右边界，直到区间为空或命中目标值。
 *
 * 相比递归写法，这种实现不需要额外的函数调用栈，通常更适合在工程中使用。
 *
 * @param my_list 待查找的有序整数数组。
 * @param target 需要查找的目标值。
 * @param left 搜索区间起点，默认值为 0。
 * @param right 搜索区间终点，若不传入则默认设为最后一个元素下标。
 * @return 若找到目标值，返回其索引；否则返回 -1。
 *
 * @complexity 时间复杂度 O(log n)，空间复杂度 O(1)。
 */
int binary_search_function(const std::vector<int>& my_list, int target, int left = 0, int right = -1)
{
    // 若未显式传入右边界，则默认使用数组最后一个位置。
    if (right == -1)
    {
        right = static_cast<int>(my_list.size()) - 1;
    }

    // 只要区间仍有效，就继续查找。
    while (left <= right)
    {
        // 计算中间位置，保证不会因为相加超出整数范围而失真。
        int middle = left + (right - left) / 2;

        // 若命中中间元素，直接返回索引。
        if (my_list[middle] == target)
        {
            return middle;
        }
        // 若中间值更大，则目标落在左半区间。
        else if (my_list[middle] > target)
        {
            right = middle - 1;
        }
        // 若中间值更小，则目标落在右半区间。
        else
        {
            left = middle + 1;
        }
    }

    // 循环结束仍未找到目标，说明不存在。
    return -1;
}