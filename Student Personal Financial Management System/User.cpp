#include "User.h"
#include "FileManager.h"
#include <fstream>
#include <sstream>

User::User() : username(L""), password(L""), isLoggedIn(false) {}

User::User(const std::wstring& uname, const std::wstring& pwd)
    : username(uname), password(pwd), isLoggedIn(false) {
}

// ==================== 注册：追加写入文件 ====================
bool User::registerUser(const std::wstring& uname, const std::wstring& pwd) {
    // 校验格式
    if (uname.empty() || pwd.empty()) return false;
    if (uname.length() < 3 || uname.length() > 20) return false;
    if (pwd.length() < 6) return false;

    // 检查是否重名
    auto allUsers = loadAllUsers();
    for (auto& u : allUsers) {
        if (u.first == uname) return false;  // 用户名已存在
    }

    // 追加写入文件
    std::wstring filepath = FileManager::getDataDirectory() + L"user.dat";
    std::wstring content = uname + L"|" + pwd + L"\n";
    return FileManager::appendTextToFile(filepath, content);
}

// ==================== 加载：读取文件中所有用户 ====================
std::vector<std::pair<std::wstring, std::wstring>> User::loadAllUsers() {
    std::vector<std::pair<std::wstring, std::wstring>> users;

    std::wstring filepath = FileManager::getDataDirectory() + L"user.dat";
    if (!FileManager::fileExists(filepath)) return users;

    std::wstring content = FileManager::readTextFromFile(filepath);
    std::wstringstream ss(content);
    std::wstring line;

    while (std::getline(ss, line)) {
        if (line.empty()) continue;

        size_t pos = line.find(L'|');
        if (pos == std::wstring::npos) continue;

        std::wstring name = line.substr(0, pos);
        std::wstring pwd = line.substr(pos + 1);
        users.push_back({ name, pwd });
    }

    return users;
}

// ==================== 登录：在所有用户中查找 ====================
bool User::login(const std::wstring& uname, const std::wstring& pwd) {
    auto allUsers = loadAllUsers();  // 每次登录时重新读取文件

    for (auto& u : allUsers) {
        if (u.first == uname && u.second == pwd) {
            username = uname;
            password = pwd;
            isLoggedIn = true;
            return true;
        }
    }
    return false;
}

void User::logout() {
    isLoggedIn = false;
}

bool User::changePassword(const std::wstring& oldPwd, const std::wstring& newPwd) {
    if (password != oldPwd) return false;
    if (newPwd.length() < 6) return false;

    // 更新文件中的密码
    auto allUsers = loadAllUsers();
    std::wstring filepath = FileManager::getDataDirectory() + L"user.dat";
    std::wstring newContent;

    for (auto& u : allUsers) {
        if (u.first == username) {
            newContent += u.first + L"|" + newPwd + L"\n";  // 改密码
        }
        else {
            newContent += u.first + L"|" + u.second + L"\n"; // 不改
        }
    }

    FileManager::writeTextToFile(filepath, newContent);
    password = newPwd;
    return true;
}

std::wstring User::getUsername() const {
    return username;
}

bool User::isUserLoggedIn() const {
    return isLoggedIn;
}