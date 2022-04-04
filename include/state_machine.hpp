#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// #include <book.hpp>
// #include <user.hpp>

enum class Event {
    kLogout,
    kExit,
    kProfessorLogin,
    kLibrarianLogin,
    kStudentLogin,
    kNone
};

class Library;

class State {
    public:
    virtual void run(Library* library) = 0;
    virtual void enter(Library* library) = 0;
    virtual void exit(Library* library) = 0;

    protected:
    std::vector<std::string> getSplitStrings(std::string full_string);
};

class Library {
    public:
    State* current_state_ = NULL;
    std::string username;
    void changeState(State* state) {
        if (current_state_ != NULL) current_state_->exit(this);
        current_state_ = state;
        current_state_->enter(this);
    }
};

class LoginState : public State {
    public:
    // LoginState(Event* event);
    void run(Library* library) override;
    static State& getInstance();
    void enter(Library* library);
    void exit(Library* library);

    private:
    LoginState(){}
        
    std::vector<std::string> usernames;
    std::vector<std::string> passwords;
    std::vector<std::string> types;

    std::string entered_username;
};

class ProfessorAccessState : public State {
    public:
    // ProfessorAccessState(Event* event, std::string username);
    void run(Library* library) override;
    static State& getInstance();
    void enter(Library* library);
    void exit(Library* library);

    private:
    ProfessorAccessState(){}
    // Professor professor_;
};

class StudentAccessState : public State {
    public:
    // StudentAccessState(Event* event, std::string username);
    void run(Library* library) override;
    static State& getInstance();
    void enter(Library* library);
    void exit(Library* library);

    private:
    StudentAccessState(){}
    // Student student_;
};

class LibrarianAccessState : public State {
    public:
    // LibrarianAccessState(Event* event, std::string username);
    void run(Library* library) override;
    static State& getInstance();
    void enter(Library* library);
    void exit(Library* library);

    private:
    LibrarianAccessState(){}
    // Librarian librarian_;
};

