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
    void addUser();
    void updateUser();
    void deleteUser();
    User searchUser(std::string name);

    private:
    std::list<User> list_of_users_;
};