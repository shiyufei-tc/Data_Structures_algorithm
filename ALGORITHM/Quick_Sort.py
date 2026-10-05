


def Quick_Sort(my_list,start=0,end=None):
    """对列表按快速排序思想进行原地升序排序。

    该算法使用“分治法”：
    1. 选取一个基准值（这里使用最左端元素）
    2. 把比基准值小的元素放到左边，比基准值大的元素放到右边
    3. 递归处理左右两个子区间，直到区间长度不超过 1

    Args:
        my_list: 待排序列表。该函数会直接修改原列表。
        start: 当前区间的左边界，默认从 0 开始。
        end: 当前区间的右边界，默认是列表最后一个索引。

    Returns:
        None: 该函数原地排序列表，不返回新列表。

    Complexity:
        平均时间复杂度：O(n log n)
        最坏时间复杂度：O(n^2)
        空间复杂度：O(log n)（递归栈）
    """

    if end is None:
        end=len(my_list)-1

    if start>=end:
        return

    left,right=start,end

    # 把分界值从列表中提取出来，作为当前区间的基准值。
    # 这里选择第一个元素作为 middle，后续按它进行左右分区。
    middle=my_list[start]

    while left<right:
        # 从右边开始往左扫描，寻找第一个小于 middle 的元素。
        # 使用 while 是因为如果遇到右侧元素大于等于 middle，就继续往左移动；
        # 只有找到更小的元素，才停下来进行交换。
        # 这里不能写成 if，因为需要多次移动 right 才能找到合适的元素
        # 如果写成if会导致只判断一次，并不会继续移动right，即最大right只可能移动一次
        while left<right and my_list[right]>=middle:
            right-=1 
        my_list[left]=my_list[right]

        # 从左边开始往右扫描，寻找第一个大于等于 middle 的元素，小于middle的元素就跳过
        while left<right and my_list[left]<middle:
            left+=1
        my_list[right]=my_list[left]

    # 当 left 和 right 相遇时，说明当前区间已经按 middle 分成两部分。
    # 将基准值写回最终位置 middle 应该落在的位置。
    my_list[left]=middle

    # 递归处理左半区和右半区，继续进行快速排序。
    Quick_Sort(my_list,start,right-1)
    Quick_Sort(my_list,left+1,end)
        

