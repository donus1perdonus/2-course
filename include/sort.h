#ifndef SORT_H
#define SORT_H

#include <vector>
#include <functional>
#include <algorithm>

template <typename T>
class Sort
{
public:
    
    virtual void sort(std::vector<T>& data, std::function<bool(const T&, const T&)> comparator) = 0;
    
    virtual ~Sort() = default;

};

#endif //SORT_H