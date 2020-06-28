#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
class Deque {
public:
    Deque() { size_ = 0; }
    bool Empty() const {
        if (pushBack_.size() || pushFront_.size()) return false;
        return true;
    }
    size_t Size() const { return size_; }
    T& operator[](size_t index) {
        if (index >= pushFront_.size()) {
            return pushBack_[index - pushFront_.size()];
        }
        return pushFront_[pushFront_.size() - 1 - index];
    }
    const T& operator[](size_t index) const {
        if (index >= pushFront_.size()) {
            return pushBack_[index - pushFront_.size()];
        }
        return pushFront_[pushFront_.size() - 1 - index];
    };
    T& At(size_t index) {
        if (index >= size_) throw std::out_of_range("out_of_range");
        if (index >= pushFront_.size()) {
            return pushBack_[index - pushFront_.size()];
        }
        return pushFront_[pushFront_.size() - 1 - index];
    }
    const T& At(size_t index) const {
        if (index >= size_) throw std::out_of_range("out_of_range");
        if (index >= pushFront_.size()) {
            return pushBack_[index - pushFront_.size()];
        }
        return pushFront_[pushFront_.size() - 1 - index];
    }
    T& Front() {
        if (pushFront_.size() == 0) {
            return pushBack_[0];
        }
        return pushFront_[pushFront_.size() - 1];
    }
    const T& Front() const {
        if (pushFront_.size() == 0) {
            return pushBack_[0];
        }
        return pushFront_[pushFront_.size() - 1];
    }

    T& Back() {
        if (pushBack_.size() == 0) {
            return pushFront_[0];
        }
        return pushBack_[pushBack_.size() - 1];
    }
    const T& Back() const {
        if (pushBack_.size() == 0) {
            return pushFront_[0];
        }
        return pushBack_[pushBack_.size() - 1];
    }
    void PushBack(const T& value) {
        pushBack_.push_back(value);
        ++size_;
    }
    void PushFront(const T& value) {
        pushFront_.push_back(value);
        ++size_;
    }
private:
    std::vector<T> pushBack_;
    std::vector<T> pushFront_;
    size_t size_;
};

int main()
{
    Deque<int> d;
    std::cout << "Empty = " << d.Empty() << std::endl;
    d.PushFront(4);
    d.PushFront(3);
    d.PushFront(2);
    d.PushBack(5);
    d.PushBack(6);
    d.PushFront(1);
    d.PushFront(0);
    d.PushBack(7);
    d.PushBack(8);
    d.PushBack(9);
    std::cout << "Empty = " << d.Empty() << std::endl;
    std::cout << "Size = " << d.Size() << std::endl;
    std::cout << "Front = " << d.Front() << std::endl;
    std::cout << "Back = " << d.Back() << std::endl;
    d[4] = 8;
    int a = d.At(3);
    std::cout << "A = " << a << std::endl;

    return 0;
}
