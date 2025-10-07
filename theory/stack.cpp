#include <iostream>
#include <string>

struct Node
{
public:
    std::string _data;
    Node* _next;

    Node(std::string data) : _data(data), _next(nullptr) {}
    Node(std::string data, Node* next) : _data(data), _next(next) {}
};

class Stack
{
private:
    Node* _top;

public:
    Stack() : _top(nullptr) {}

    ~Stack()
    {
        while (_top != nullptr)
        {
            Node* temp = _top;
            _top = _top->_next;
            delete temp;
        }
    }

    Stack& push(std::string data)
    {
        Node* node = new Node(data, _top);
        _top = node;
        return *this;
    }

    std::string pop() // Изменено на возврат std::string по значению
    {
        if (_top == nullptr) // Проверка на пустой стек
        {
            throw std::runtime_error("Stack is empty");
        }

        Node* temp = _top;
        _top = _top->_next;

        std::string str = temp->_data; // Копируем данные
        delete temp;

        return str; // Возвращаем строку по значению
    }
};

int main()
{
    Stack stack;

    stack.push("hui").push("hui1").push("hui2");

    std::string top = stack.pop();

    std::cout << top << std::endl; // Вывод: hui2

    return 0;
} 