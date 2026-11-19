#include<algorithm>
#include<iostream>
int main()
{
    int max = 5, min = 3, count = 0;
    while (min != 0)
    {
        if (max < min)
        {
            std::swap(max, min);
        }
        max -= min;
        count++;
    }
    std::cout << count-1 << '\n';
    return 0;
}