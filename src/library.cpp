#include <library.hpp>

Library::Library(): book_database(), user_database(book_database) {}

void Library::changeState(State* state) {
        if (current_state_ != list_of_books_.end()) current_state_->exit(this);
        current_state_ = state;
        current_state_->enter(this);
}

std::vector<std::string> getSplitStrings(std::string full_string) {
    size_t position = 0;
    std::vector<std::string> string_list;

    while ((position = full_string.find(" ")) != std::string::npos) {
        string_list.push_back(full_string.substr(0, position));
        full_string.erase(0, position + 1);
    }

    string_list.push_back(full_string);

    return string_list;
}