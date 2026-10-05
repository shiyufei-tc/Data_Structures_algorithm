"""
二分查找算法模块。

说明:
    该模块提供二分查找的递归与非递归实现，
    适用于已排序序列中的目标值查询。
"""

def binary_search_recursion(my_list, target, left=0, right=None):
    """
    二分查找算法的递归实现。

    参数:
        my_list: 已排序的列表，存放待查找元素
        target: 需要查找的目标值
        left: 当前查找范围的左边界，默认为 0
        right: 当前查找范围的右边界，默认为列表末尾

    返回:
        如果找到目标值，返回其索引；否则返回 None。

    说明:
        由于每次都只在一半的数据区间中继续查找，时间复杂度为 O(log n)，
        递归栈空间复杂度为 O(log n)。
    """
    # 初始化右边界，避免每次都重复计算列表长度
    if right is None:
        right = len(my_list) - 1

    # 查找范围为空时，说明目标值不存在
    if left > right:
        return None

    # 计算中间位置，避免越界，并保持稳定的划分逻辑
    middle = (left + right) // 2

    # 命中目标值，返回当前位置
    if my_list[middle] == target:
        return middle

    # 目标值较小，继续在左半区间查找
    if my_list[middle] > target:
        return binary_search_recursion(my_list, target, left, middle - 1)

    # 目标值较大，继续在右半区间查找
    return binary_search_recursion(my_list, target, middle + 1, right)


def binary_search_function(my_list, target, left=0, right=None):
    """
    二分查找算法的非递归实现。

    参数:
        my_list: 已排序的列表，存放待查找元素
        target: 需要查找的目标值
        left: 当前查找范围的左边界，默认为 0
        right: 当前查找范围的右边界，默认为列表末尾

    返回:
        如果找到目标值，返回其索引；否则返回 None。

    说明:
        该方法通过循环不断缩小查找区间，避免递归调用，
        适合在不希望使用递归栈的场景中使用。
    """

    # 初始化右边界，避免每次都重复计算列表长度
    if right is None:
        right = len(my_list) - 1

    # 当左边界大于右边界时，说明查找区间已空，目标值不存在
    while left <= right:
        # 计算中间位置，确定当前比较基准
        middle = (left + right) // 2

        # 命中目标值，返回当前位置
        if my_list[middle] == target:
            return middle

        # 目标值较小，继续在左半区间查找
        elif my_list[middle] > target:
            right = middle - 1

        # 目标值较大，继续在右半区间查找
        else:
            left = middle + 1

    # 遍历完整个查找区间后仍未找到目标值，返回 None
    return None

