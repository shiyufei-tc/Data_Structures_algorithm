def insert_sort(my_list):
    """对列表进行原地插入排序。

    插入排序的核心思想是：
    把列表分成“已排序区”和“待排序区”。
    每次从待排序区拿出一个元素，把它插入到前面已排序区的正确位置上，
    直到整个列表有序。

    Args:
        my_list: 待排序的列表。函数会直接在原列表上修改。

    Returns:
        None

    Complexity:
        时间复杂度：O(n^2)
        空间复杂度：O(1)
    """
    # 从第 1 个元素开始，默认第 0 个元素可视为已排序区。
    for i in range(1, len(my_list)):
        # 当前要插入的元素。
        current = my_list[i]

        # j 指向已排序区的最后一个位置，向前依次比较。
        j = i - 1

        # 当前元素比前一个元素小，就把前面的元素整体后移，
        # 让出位置给 current，直到找到合适的插入位置。
        while j >= 0 and my_list[j] > current:
            my_list[j + 1] = my_list[j]
            j -= 1

        # 将 current 插入到正确位置。
        my_list[j + 1] = current


def bubble_sort(my_list):
    for left_index in range(len(my_list)):
        swapped=False
        for unsorted_end in range(len(my_list)-left_index-1):
            if my_list[unsorted_end]>my_list[unsorted_end+1]:
                my_list[unsorted_end],my_list[unsorted_end+1]=my_list[unsorted_end+1],my_list[unsorted_end]
                swapped=True
        if not swapped:
            break
    return None


def selection_sort(my_list):
    for start_index in range(len(my_list)):
        min_index=start_index
        for scan_index in range(start_index+1,len(my_list)):
            if my_list[min_index]>my_list[scan_index]:
                min_index=scan_index
        my_list[start_index],my_list[min_index]=my_list[min_index],my_list[start_index]
    return None

