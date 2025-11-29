#include "webserver.h"
#include "bloom_filter.h"
#include <iostream>

int main() 
{
    // Тест Bloom фильтра
    std::vector<std::function<size_t(const std::string&)>> hash_funcs = {hash1, hash2, hash3};
    BloomFilter<std::string> filter(100, hash_funcs);
    
    filter.add("test");
    std::cout << "Test exists: " << filter.possibly_contains("test") << std::endl;
    
    // Запуск сервера
    return run_server();
}