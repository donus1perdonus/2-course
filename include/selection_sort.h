#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <sort.h>

template <typename T>
class SelectionSort :
    public Sort<T>
{

public:

    void sort(std::vector<T>& data, std::function<bool(const T&, const T&)> comparator) override
    {
        for (size_t i = 1; i < data.size(); ++i) {
            T key = data[i];
            size_t j = i;

            // Сдвигаем элементы data[0..i-1], которые больше key, на одну позицию вперед
            while (j > 0 && comparator(key, data[j - 1])) {
                data[j] = data[j - 1];
                --j;
            }
            data[j] = key;
        }
    }

};

#endif //SELECTION_SORT_H