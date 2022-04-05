#pragma once
#include <vector>
#include <string>
#include <book_database.hpp>
#include <user_database.hpp>

class Library;

class State {
    public:
    virtual void run(Library* library) = 0;
    virtual void enter(Library* library) = 0;
    virtual void exit(Library* library) = 0;
};

class Library {
    public:
    State* current_state_ = NULL;
    std::string username;
    void changeState(State* state);

    BookDatabase book_database;
    UserDatabase user_database;
};

std::vector<std::string> getSplitStrings(std::string full_string);