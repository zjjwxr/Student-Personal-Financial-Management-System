
#pragma once
#include <string>
#include <map>

class User {
private:
    std::map<std::wstring, std::wstring> m_users;  // 用户名 -> 密码
    std::wstring m_currentUser;
    bool isLoggedIn;

public:
    User();
    bool registerUser(const std::wstring& uname, const std::wstring& pwd);
    bool login(const std::wstring& uname, const std::wstring& pwd);
    void logout();
    bool saveToFile() const;
    bool loadFromFile();
    std::wstring getCurrentUsername() const;
    bool isUserLoggedIn() const;
};