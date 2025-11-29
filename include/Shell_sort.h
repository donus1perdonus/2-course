#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include <sort.h>

template <typename T>
class ShellSort :
    public Sort<T>
{

public:

    void sort(std::vector<T>& data, std::function<bool(const T&, const T&)> comparator) override
    {
        int n = data.size();
        
        // Начинаем с большого интервала и уменьшаем его
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // Выполняем сортировку вставками для данного интервала
            for (int i = gap; i < n; i++) {
                T temp = data[i];
                int j;

                // Сдвигаем элементы data[0..i-gap] вверх, чтобы найти позицию для temp
                for (j = i; j >= gap && comparator(temp, data[j - gap]); j -= gap) {
                    data[j] = data[j - gap];
                }
                data[j] = temp;
            }
        }
    }

};

#endif //SHELL_SORT_H