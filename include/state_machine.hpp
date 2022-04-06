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
};

class LibrarianAccessState : public State {
    public:
    // LibrarianAccessState(Event* event, std::string username);
    void run(Library* library) override;
    static State& getInstance();
    void enter(Library* library);
    void exit(Library* library);

    private:
    void addUser(Library* library);
    void modifyUser(Library* library);
    void addBook(Library* library);
    void modifyBook(Library* library);
    Librarian* librarian_;
};

