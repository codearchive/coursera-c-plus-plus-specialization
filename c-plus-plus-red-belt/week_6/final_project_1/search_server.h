#pragma once

#include "parse.h"
#include "profile.h"

#include <istream>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>
#include <deque>

using namespace std;

class InvertedIndex {
public:
    struct Entry {
        size_t quantity;
        size_t doc_id;
    };
    InvertedIndex() = default;
    explicit InvertedIndex(istream& document_input);
    InvertedIndex(const InvertedIndex&) = delete;
    void operator=(const InvertedIndex&) = delete;
    void operator=(InvertedIndex&& other);

    const vector<Entry>& Lookup(string_view word) const;
    const string& GetDocument(size_t id) const {
        return docs[id];
    }
    size_t GetDocsSize() const { return docs.size(); }
private:
    map<string_view, vector<Entry>> index;
    deque<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input)
        : index(InvertedIndex(document_input))
    {}
    SearchServer(const SearchServer&) = delete;
    void operator=(const SearchServer&) = delete;

    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);
private:
    InvertedIndex index;
};
