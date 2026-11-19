#include<vector>
#include<algorithm>

void bubble_sort(std::vector<int> list)
{
    size_t length = list.size();
    for (size_t i = 0; i < length;++i)
    {
        bool is_swap = false;
        for (size_t j = 0; j < length - i - 1;++j)
        {
            if(list[i]>list[j])
            {
                std::swap(list[i], list[j]);
                is_swap = true;
            }
        }
        if(!is_swap)
            continue;
    }
    return;
}

void select_sort(std::vector<int> list)
{
    size_t length = list.size();
    for (size_t i = 0; i < length;++i)
    {
        size_t min = i;
        for (size_t j = i+1; j < length; ++j)
        {
            if(list[i]>list[j])
            {
                min = j;
            }
        }
        std::swap(list[i], list[min]);
    }
    return;
}