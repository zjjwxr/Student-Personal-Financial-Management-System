#pragma once
#pragma once
#include <string>
#include <vector>

class User {
private:
    std::wstring username;
    std::wstring password;
    bool isLoggedIn;

public:
    User();
    User(const std::wstring& uname, const std::wstring& pwd);

    // 注册：把新用户追加写入文件（不加载到内存）
    static bool registerUser(const std::wstring& uname, const std::wstring& pwd);

    // 加载：从文件读取所有用户
    static std::vector<std::pair<std::wstring, std::wstring>> loadAllUsers();

    // 登录：在所有用户中查找匹配的
    bool login(const std::wstring& uname, const std::wstring& pwd);

    void logout();
    bool changePassword(const std::wstring& oldPwd, const std::wstring& newPwd);

    std::wstring getUsername() const;
    bool isUserLoggedIn() const;
};

