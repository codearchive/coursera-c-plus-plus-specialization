#pragma once
#include <list>
#include <string>

class Editor {
public:
    Editor();
    void Left();
    void Right();
    void Insert(char token);
    void Cut(size_t tokens = 1);
    void Copy(size_t tokens = 1);
    void Paste();
    std::string GetText() const;
private:
    std::list<char> data_;
    std::list<char> buffer_;
    std::list<char>::iterator cursor;
};
