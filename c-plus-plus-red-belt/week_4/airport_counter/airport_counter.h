#pragma once
#include <array>

template <typename TAirport>
class AirportCounter {
public:
    AirportCounter() = default;

    template <typename TIterator>
    AirportCounter(TIterator begin, TIterator end) {
        for (size_t i = 0; i < SIZE; ++i) {
            storage_[i].first = static_cast<TAirport>(i);
            storage_[i].second = 0;
        }
        for (auto it = begin; it != end; ++it) {
            ++storage_[static_cast<uint32_t>(*it)].second;
        }
    }

    size_t Get(TAirport airport) const {
        return storage_[static_cast<uint32_t>(airport)].second;
    }
    void Insert(TAirport airport) {
        ++storage_[static_cast<uint32_t>(airport)].second;
    }
    void EraseOne(TAirport airport) {
        --storage_[static_cast<uint32_t>(airport)].second;
    }
    void EraseAll(TAirport airport) {
        storage_[static_cast<uint32_t>(airport)].second = 0;
    }

    using Item = std::pair<TAirport, size_t>;
    using Items = std::array<Item, static_cast<uint32_t>(TAirport::Last_)>;
    static const size_t SIZE = static_cast<uint32_t>(TAirport::Last_);

    Items GetItems() const {
        return storage_;
    }
private:
    std::array<std::pair<TAirport, size_t>, static_cast<uint32_t>(TAirport::Last_)> storage_;
};
