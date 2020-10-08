#pragma once

#include <functional>
#include <shared_mutex>

using namespace std;

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) : value(move(initial)) {};

    struct AccessRead {
        shared_lock<shared_mutex> g;
        T& ref_to_value;
    };

    struct AccessWrite {
        unique_lock<shared_mutex> g;
        T& ref_to_value;
    };

    AccessRead GetAccessToRead() {
        return {shared_lock(m), ref(value)};
    }

    AccessWrite GetAccessToWrite() {
        return {unique_lock(m), ref(value)};
    }
private:
    T value;
    shared_mutex m;
};
