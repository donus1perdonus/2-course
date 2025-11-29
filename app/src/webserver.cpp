#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "bloom_filter.h"
#include "webserver.h"

const int PORT = 8080;
const int BUFFER_SIZE = 4096;
const int DEFAULT_BLOOM_SIZE = 1024;

std::unordered_map<std::string, std::unique_ptr<BloomFilter<std::string>>> bloom_filters;

// Хеш-функции для строк
size_t hash1(const std::string& key) 
{
    return std::hash<std::string>{}(key);
}

size_t hash2(const std::string& key) 
{
    size_t hash = 5381;
    for (char c : key) 
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

size_t hash3(const std::string& key) 
{
    size_t hash = 0;
    for (char c : key) 
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

std::string handle_bloom_request(const std::string& path, const std::string& body) 
{
    std::istringstream iss(path);
    std::string token;
    std::vector<std::string> parts;
    
    while (std::getline(iss, token, '/')) 
    {
        if (!token.empty()) 
        {
            parts.push_back(token);
        }
    }

    if (parts.size() < 2)
    {
        return "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request";
    }

    const std::string& action = parts[1];
    const std::string& filter_name = parts.size() > 2 ? parts[2] : "";

    if (action == "create") 
    {
        if (filter_name.empty()) 
        {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nFilter name required";
        }
        bloom_filters[filter_name] = std::make_unique<BloomFilter<std::string>>(
            DEFAULT_BLOOM_SIZE, 
            std::vector<std::function<size_t(const std::string&)>>{hash1, hash2, hash3}
        );
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nBloom filter created";
    }
    else if (action == "add") 
    {
        if (filter_name.empty() || body.empty()) 
        {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nFilter name and key required";
        }
        if (bloom_filters.find(filter_name) == bloom_filters.end()) 
        {
            return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFilter not found";
        }
        bloom_filters[filter_name]->add(body);
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nKey added";
    }
    else if (action == "check") 
    {
        if (filter_name.empty() || body.empty()) 
        {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nFilter name and key required";
        }
        if (bloom_filters.find(filter_name) == bloom_filters.end()) 
        {
            return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFilter not found";
        }
        bool exists = bloom_filters[filter_name]->possibly_contains(body);
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n" + std::string(exists ? "Key possibly exists" : "Key definitely does not exist");
    }
    else if (action == "clear") 
    {
        if (filter_name.empty()) 
        {
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nFilter name required";
        }
        if (bloom_filters.find(filter_name) == bloom_filters.end()) 
        {
            return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFilter not found";
        }
        bloom_filters[filter_name]->clear();
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFilter cleared";
    }

    return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nInvalid action";
}

std::string handle_request(const std::string& method, const std::string& path, const std::string& body) 
{
    if (path.find("/bloom/") == 0) 
    {
        return handle_bloom_request(path, body);
    }
    else if (path == "/ping") 
    {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\npong";
    }
    else if (path == "/hello") 
    {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
    }
    return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found";
}

int run_server() 
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) 
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) 
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) 
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        ssize_t bytes_read = read(new_socket, buffer, BUFFER_SIZE);
        std::string request(buffer, bytes_read);

        std::istringstream iss(request);
        std::string method, path, version;
        iss >> method >> path >> version;

        std::string body;
        size_t body_pos = request.find("\r\n\r\n");
        if (body_pos != std::string::npos && body_pos + 4 < request.size()) 
        {
            body = request.substr(body_pos + 4);
        }

        std::string response = handle_request(method, path, body);
        send(new_socket, response.c_str(), response.length(), 0);

        memset(buffer, 0, BUFFER_SIZE);
        close(new_socket);
    }

    return 0;
}