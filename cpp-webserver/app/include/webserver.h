#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>

size_t hash1(const std::string& key);
size_t hash2(const std::string& key); 
size_t hash3(const std::string& key);

std::string handle_bloom_request(const std::string& path, const std::string& body);

std::string handle_request(const std::string& method, const std::string& path, const std::string& body);

int run_server();

#endif //WEBSERVER_H