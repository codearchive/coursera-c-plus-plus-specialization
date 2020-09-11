#include "editor.h"

Editor::Editor() {
    cursor = data_.end();
}

void Editor::Left() {
    if (cursor == data_.begin()) return;
    --cursor;
}

void Editor::Right() {
    if (cursor == data_.end()) return;
    ++cursor;
}

void Editor::Insert(char token) {
    data_.insert(cursor, token);
}

void Editor::Cut(size_t tokens) {
    if (!buffer_.empty()) buffer_.clear();
    auto next_it = cursor;
    for (size_t i = 0; i <= tokens; ++i) {
        if (next_it == data_.end()) {
            break;
        }
        next_it = std::next(cursor, i);
    }
    buffer_.splice(buffer_.begin(), data_, cursor, next_it);
    cursor = next_it;
}

void Editor::Copy(size_t tokens) {
    if (!buffer_.empty()) buffer_.clear();
    auto next_it = cursor;
    for (size_t i = 0; i <= tokens; ++i) {
        if (next_it == data_.end()) {
            break;
        }
        next_it = std::next(cursor, i);
    }
    for (auto it = cursor; it != next_it; ++it) {
        buffer_.push_back(*it);
    }
}

void Editor::Paste() {
    data_.insert(cursor, buffer_.begin(), buffer_.end());
}

std::string Editor::GetText() const {
    std::string str;
    for (const char& c : data_) {
        str += c;
    }
    return str;
}

