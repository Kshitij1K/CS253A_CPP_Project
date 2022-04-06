#pragma once
#include <user.hpp>
#include <string>
#include <vector>

class UserDatabase {
    public:
    UserDatabase(BookDatabase book_database);
    
    void addUser(User user);
    void updateUser(std::string old_username,
                    std::string new_username,
                    std::string new_password,
                    std::string new_name);  
    void deleteUser(std::string username);
    
    std::shared_ptr<std::list<User>> searchUserByName(std::string name);
    std::list<User>::iterator searchUserByUsername(std::string username);
    bool doesUserExist(std::string username);
    void checkIssuedUsers (std::string isbn);

    private:
    std::list<User> list_of_users_;
};