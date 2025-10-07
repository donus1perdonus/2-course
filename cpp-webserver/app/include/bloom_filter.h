#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <functional>
#include <bitset>

template <typename T>
class BloomFilter 
{

private:
    
    std::vector<std::function<size_t(const T&)>> hash_functions;
    std::vector<bool> bits;
    size_t size;

public:
    
    BloomFilter(size_t size, const std::vector<std::function<size_t(const T&)>>& hash_funcs)
        : size(size), hash_functions(hash_funcs) 
    {
        bits.resize(size, false);
    }

    void add(const T& item) 
    {
        for (const auto& hash_fn : hash_functions) 
        {
            size_t index = hash_fn(item) % size;
            bits[index] = true;
        }
    }

    bool possibly_contains(const T& item) const 
    {
        for (const auto& hash_fn : hash_functions) 
        {
            size_t index = hash_fn(item) % size;
            if (!bits[index]) 
            {
                return false;
            }
        }
        return true;
    }

    void clear() 
    {
        std::fill(bits.begin(), bits.end(), false);
    }
};

#endif //BLOOM_FILTER_H