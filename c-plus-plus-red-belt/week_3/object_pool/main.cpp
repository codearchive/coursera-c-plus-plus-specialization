#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
    ObjectPool() {
        allocated_objects_ = new set<T*>;
        deallocated_objects_ = new queue<T*>;
    }
    T* Allocate() {
        if (deallocated_objects_->empty()) {
            T* new_object_ptr = new T;
            allocated_objects_->insert(new_object_ptr);
            return new_object_ptr;
        }
        else {
            T* renew_object_ptr = deallocated_objects_->front();
            allocated_objects_->insert(renew_object_ptr);
            deallocated_objects_->pop();
            return renew_object_ptr;
        }
    }

    T* TryAllocate() {
        if (deallocated_objects_->empty()) {
            return nullptr;
        }
        else {
            T* renew_object_ptr = deallocated_objects_->front();
            allocated_objects_->insert(renew_object_ptr);
            deallocated_objects_->pop();
            return renew_object_ptr;
        }
    }

    void Deallocate(T* object) {
        if (allocated_objects_->empty() || allocated_objects_->count(object) == 0) {
            throw invalid_argument("invalid_argument");
        }
        deallocated_objects_->push(*allocated_objects_->find(object));
        allocated_objects_->erase(object);
    }

    ~ObjectPool() {
        for (auto obj = allocated_objects_->begin(); obj != allocated_objects_->end(); ++obj) {
            delete *obj;
        }
        allocated_objects_->clear();
        while (!deallocated_objects_->empty()) {
            delete deallocated_objects_->front();
            deallocated_objects_->pop();
        }
        delete deallocated_objects_;
        deallocated_objects_ = nullptr;
        delete allocated_objects_;
        allocated_objects_ = nullptr;
    }


private:
    set<T*>* allocated_objects_;
    queue<T*>* deallocated_objects_;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
