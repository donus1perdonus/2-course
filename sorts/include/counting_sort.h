#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

#include <sort.h>

template <typename T>
class CountingSort : public Sort<T> 
{
    
public:

    void sort(std::vector<T>& data, std::function<bool(const T&, const T&)> comparator) override
    {
        T minVal = *std::min_element(data.begin(), data.end(), comparator);
        T maxVal = *std::max_element(data.begin(), data.end(), comparator);

        std::vector<int> count(maxVal - minVal + 1, 0);
        for (const auto& value : data) 
        {
           ++count[value - minVal];
        }

        for (size_t i = 1; i < count.size(); ++i) 
        {
        count[i] += count[i - 1];
        }

        std::vector<T> output(data.size());
        for (auto it = data.rbegin(); it != data.rend(); ++it) 
        {
            output[count[*it - minVal] - 1] = *it;
            --count[*it - minVal];
        }

        data = output;
    }

};

#endif //COUNTING_SORT_H