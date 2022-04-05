#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <book_database.hpp>
#include <user_database.hpp>

#include <library.hpp>

enum class Event {
    kLogout,
    kExit,
    kProfessorLogin,
    kLibrarianLogin,
    kStudentLogin,
    kNone
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
    Professor* professor_;
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
    Student* student_;
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
    Librarian* librarian_;
    // Librarian librarian_;
};

