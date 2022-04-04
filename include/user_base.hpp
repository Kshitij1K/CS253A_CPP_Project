#pragma once
#include <string>
#include <list>

class User {
    private:
    std::string name_;
    std::string id_;
    std::string password_;
};

class UserDatabase {
    UserDatabase();
    void addUser();
    void updateUser();
    void deleteUser();
    User searchUserByName(std::string name);

    private:
    std::list<User> list_of_students_;
    std::list<User> list_of_professor_;
    std::list<User> list_of_librarians_;
};