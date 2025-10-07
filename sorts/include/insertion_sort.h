#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <sort.h>

template <typename T>
class InsertionSort :
    public Sort<T>
{

public:

    void sort(std::vector<T>& data, std::function<bool(const T&, const T&)> comparator) override
    {
        int n = data.size();
        for (int i = 0; i < n - 1; ++i)
        {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j)
            {
                if (comparator(data[j], data[minIndex]))
                {
                    minIndex = j;
                }
            }
            if (minIndex != i)
            {
                std::swap(data[i], data[minIndex]);
            }
        }
    }

};

#endif //INSERTION_SORT_H