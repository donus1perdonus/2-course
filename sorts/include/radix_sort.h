#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <sort.h>

template <typename T>
class RadixSort :
    public Sort<T>
{

public:

    void sort(std::vector<T>& data, std::function<bool(const T&, const T&)> comparator = NULL) override
    {
        // Проверяем, что T является целым числом
        static_assert(std::is_integral<T>::value, "RadixSort requires an integral type.");

        // Находим максимальное число, чтобы определить количество разрядов
        T maxElement = *std::max_element(data.begin(), data.end());

        // Выполняем сортировку по разрядам
        for (T exp = 1; maxElement / exp > 0; exp *= 10)
        {
            countingSort(data, exp);
        }
    }

private:

    void countingSort(std::vector<T>& data, T exp)
    {
        int n = data.size();
        std::vector<T> output(n); // Выходной массив
        int count[10] = {0}; // Массив для подсчета количества

        // Подсчитываем количество элементов для текущего разряда
        for (int i = 0; i < n; i++)
        {
            count[(data[i] / exp) % 10]++;
        }

        // Изменяем count[i] так, чтобы count[i] содержал позицию этого разряда в выходном массиве
        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        // Строим выходной массив
        for (int i = n - 1; i >= 0; i--)
        {
            output[count[(data[i] / exp) % 10] - 1] = data[i];
            count[(data[i] / exp) % 10]--;
        }

        // Копируем выходной массив обратно в data
        for (int i = 0; i < n; i++)
        {
            data[i] = output[i];
        }
    }
};

#endif //RADIX_SORT_H