def contains_value(values,target):
    """
    在线性序列中查找指定值。

    参数:
        values: 待检查的序列。
        target: 需要查找的目标值。
    返回:
        bool；找到目标值时返回 True，否则返回 False。
    说明:
        按顺序比较元素，命中后立即结束遍历。

    输入规模：n 表示 values 中的元素数量。
    基本操作：比较 current_value 与 target 是否相等。
    分析前提：一次相等比较的成本为 O(1)。
    最好时间复杂度：O(1)，原因是第一个元素就与 target 相等。
    最坏时间复杂度：O(n)，原因是 target 位于末尾或不存在，需要检查全部元素。
    额外空间复杂度：O(1)，原因是只使用固定数量的局部变量。
    """
    # 命中目标后无需继续检查后面的元素
    for current_value in values:
        if current_value==target:
            return True
    return False

def has_duplicate(values):
    """
    检查序列中是否存在重复元素。

    参数:
        values: 待检查的序列。
    返回:
        bool；发现任意重复元素时返回 True，否则返回 False。
    说明:
        通过两层循环比较每一对不同位置的元素。

    输入规模：n 表示 values 中的元素数量。
    基本操作：比较两个不同下标位置的元素是否相等。
    分析前提：len()、按下标取值和一次相等比较的成本均为 O(1)。
    最好时间复杂度：O(1)，原因是比较第一对元素时就发现重复值。
    最坏时间复杂度：O(n²)，最多比较 n(n-1)/2 对元素。
    额外空间复杂度：O(1)，原因是只使用固定数量的下标变量。
    """
    # 从左侧元素的下一位开始，避免与自身及已经比较过的组合重复比较
    for left_index in range(len(values)):
        for right_index in range(left_index+1,len(values)):
            if values[left_index]==values[right_index]:
                return True
    return False


def factorial(number):
    """计算非负整数的阶乘。

    参数:
        number: 需要计算阶乘的非负整数。
    返回:
        int；返回从 1 乘到 number 的乘积。
    说明:
        负数会抛出 ValueError，0 和 1 是递归出口。

    输入规模：n 表示 number 的大小。
    基本操作：每层进行一次递归调用和一次乘法。
    分析前提：一次比较、减法和乘法的成本均按 O(1) 计算。
    时间复杂度：O(n)，参数每次减一，直到到达递归出口。
    额外空间复杂度：O(n)，调用栈会保留与 n 成正比的栈帧。
    负数行为：抛出 ValueError。
    """
    if number<0:
        raise ValueError
    # 递归出口：0! 和 1! 都等于 1，确保调用链能够结束
    elif number==0 or number==1:
        return 1
    # 缩小一层问题规模，返回时再完成当前层的乘法
    return number*factorial(number-1)
