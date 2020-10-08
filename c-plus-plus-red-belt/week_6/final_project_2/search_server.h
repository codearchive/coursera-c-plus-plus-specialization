#pragma once

#include "parse.h"
#include "profile.h"
#include "synchronized.h"

#include <istream>
#include <future>
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

    const vector<Entry>& Lookup(string_view word) const;
    const string& GetDocument(size_t id) const {
        return docs[id];
    }
    size_t GetDocsSize() const { return docs.size(); }
    void Swap(InvertedIndex& other) {
        swap(index, other.index);
        swap(docs, other.docs);
    }
private:
    map<string_view, vector<Entry>> index;
    deque<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);

    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);
private:
    void UpdateDocumentBaseSingleThread(istream& document_input);
    void AddQueriesStreamSingleThread(istream& query_input, ostream& search_results_output);
    Synchronized<InvertedIndex> index;
    vector<future<void>> async_tasks;
    bool is_index_empty_ = true;
};
