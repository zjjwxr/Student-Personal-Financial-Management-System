#pragma once
#include <string>

class User {
private:
    std::wstring m_nickname;
    std::wstring m_username;
    std::wstring m_password;

public:
    User(std::wstring nickname=L"",std::wstring username = L"", std::wstring password = L"");
    bool loginUser(); //登录逻辑
    bool addUser(); //注册逻辑
    std::wstring getNickname() const { return m_nickname; }
};