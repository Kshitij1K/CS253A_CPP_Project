#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <book.hpp>
#include <user.hpp>

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

