#include "test_runner.h"

#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = size_t;
    using Priority = int;

    Id Add(T object) {
        element_by_id_[next_id_] = move(object);
        elements_by_priority_[0].insert(next_id_);
        priority_by_id_[next_id_] = 0;
        return next_id_++;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
        for (auto it = range_begin; it != range_end; ++it) {
            *ids_begin++ = Add(move(*it));
        }
    }

    bool IsValid(Id id) const {
        const bool is_in = element_by_id_.find(id) != element_by_id_.end();
        return is_in;
    }

    const T& Get(Id id) const {
        return element_by_id_.at(id);
    }

    void Promote(Id id) {
        if (!IsValid(id)) return;
        Priority& priority = GetPriority(id);
        elements_by_priority_[priority].erase(id);
        if (elements_by_priority_[priority].empty()) {
            elements_by_priority_.erase(priority);
        }
        ++priority;
        elements_by_priority_[priority].insert(id);
        priority_by_id_[id] = priority;
    }

    pair<const T&, int> GetMax() const {
        Priority higest_priority = GetHighestPriority();
        const Id higest_priority_element_id = GetIdWithHighestPriority();
        return pair<const T&, int>(element_by_id_.at(higest_priority_element_id), higest_priority);
    }

    pair<T, int> PopMax() {
        Priority higest_priority = GetHighestPriority();
        Id higest_priority_element_id = GetIdWithHighestPriority();
        pair<T, int> result = make_pair(move(element_by_id_[higest_priority_element_id]), higest_priority);

        element_by_id_.erase(higest_priority_element_id);
        priority_by_id_.erase(higest_priority_element_id);
        GetIdsWithHighestPriority().erase(higest_priority_element_id);
        if (GetIdsWithHighestPriority().empty()) {
            elements_by_priority_.erase(higest_priority);
        }
        return result;
    }
private:
    Priority& GetPriority(const Priority& priority) {
        return priority_by_id_[priority];
    }

    Priority GetHighestPriority() const {
        return elements_by_priority_.rbegin()->first;
    }

    set<Id>& GetIdsWithHighestPriority() {
        return elements_by_priority_.rbegin()->second;
    }

    Id GetIdWithHighestPriority() const {
        return *elements_by_priority_.rbegin()->second.rbegin();
    }

    map<Id, T> element_by_id_;
    map<Id, Priority> priority_by_id_;
    map<Priority, set<Id>> elements_by_priority_;
    size_t next_id_ = 0;
};


class StringNonCopyable : public string {
public:
    using string::string;
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");
    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto& item = strings.Get(white_id);
        ASSERT_EQUAL(item, "white");
    }
    {
        const auto item = strings.GetMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
