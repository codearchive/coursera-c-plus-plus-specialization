#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

InvertedIndex::InvertedIndex(istream& document_input) {
    for (string current_document; getline(document_input, current_document); ) {
        docs.push_back(move(current_document));
        const size_t docid = docs.size() - 1;
        for (const auto word : SplitIntoWordsView(docs[docid])) {
            auto& entries = index[word];
            if (entries.empty() || entries.back().doc_id != docid) {
                entries.push_back({1, docid});
            }
            else {
                ++entries.back().quantity;
            }
        }
    }
}

void InvertedIndex::operator=(InvertedIndex&& other) {
    index.clear();
    docs.clear();
    index = move(other.index);
    docs = move(other.docs);
}


void SearchServer::UpdateDocumentBase(istream& document_input) {
    index = InvertedIndex(document_input);
}

void SearchServer::AddQueriesStream(istream& query_input,
                                    ostream& search_results_output) {
    size_t index_size = index.GetDocsSize();
    vector<pair<size_t, int64_t>> docid_count(index_size);
    for (string current_query; getline(query_input, current_query); ) {
        docid_count.assign(index_size, { 0, 0 });
        const auto words = SplitIntoWordsView(current_query);

        for (const auto word : words) {
            for (const auto& doc : index.Lookup(word)) {
                docid_count[doc.doc_id].first = doc.doc_id;
                docid_count[doc.doc_id].second += doc.quantity;
            }
        }

        auto middle = index_size <= 5 ? end(docid_count) : begin(docid_count) + 5;
        partial_sort(begin(docid_count), middle, end(docid_count),
                     [](const pair<size_t, int64_t>& lhs, const pair<size_t, int64_t>& rhs) {
            int64_t lhs_docid = lhs.first;
            auto lhs_hit_count = lhs.second;
            int64_t rhs_docid = rhs.first;
            auto rhs_hit_count = rhs.second;
            return make_pair(lhs_hit_count, -lhs_docid) >
                    make_pair(rhs_hit_count, -rhs_docid);
        }
        );

        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(docid_count, 5)) {
            if (hitcount == 0) break;
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
    }
}

const vector<InvertedIndex::Entry>& InvertedIndex::Lookup(string_view word) const {
    if (index.count(word)) {
        return index.at(word);
    }
    static const vector<Entry> empty_result;
    return empty_result;
}
