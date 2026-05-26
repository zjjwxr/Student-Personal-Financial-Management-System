#include "User.h"
#include "FileManager.h"
#include <fstream>
#include <sstream>

User::User() : isLoggedIn(false) {}

bool User::registerUser(const std::wstring& uname, const std::wstring& pwd) {
    if (uname.empty() || pwd.empty()) return false;
    if (uname.length() < 3 || uname.length() > 20) return false;
    if (pwd.length() < 6) return false;

    // 检查是否已存在
    if (m_users.find(uname) != m_users.end()) {
        return false;  // 用户已存在
    }

    m_users[uname] = pwd;
    return true;
}

bool User::login(const std::wstring& uname, const std::wstring& pwd) {
    auto it = m_users.find(uname);
    if (it != m_users.end() && it->second == pwd) {
        m_currentUser = uname;
        isLoggedIn = true;
        return true;
    }
    return false;
}

void User::logout() {
    isLoggedIn = false;
    m_currentUser.clear();
}

std::wstring User::getCurrentUsername() const {
    return m_currentUser;
}

bool User::isUserLoggedIn() const {
    return isLoggedIn;
}

bool User::saveToFile() const {
    std::wstring filepath = FileManager::getDataDirectory() + L"user.dat";
    std::wstring content;

    // 把所有用户写入文件
    for (const auto& pair : m_users) {
        content += pair.first + L"|" + pair.second + L"\n";
    }

    return FileManager::writeTextToFile(filepath, content);  // 用覆盖写入
}

bool User::loadFromFile() {
    std::wstring filepath = FileManager::getDataDirectory() + L"user.dat";
    if (!FileManager::fileExists(filepath)) return false;

    std::wstring content = FileManager::readTextFromFile(filepath);
    std::wstringstream ss(content);
    std::wstring line;

    m_users.clear();
    while (std::getline(ss, line)) {
        if (line.empty()) continue;

        size_t pos = line.find(L'|');
        if (pos != std::wstring::npos) {
            std::wstring uname = line.substr(0, pos);
            std::wstring pwd = line.substr(pos + 1);
            m_users[uname] = pwd;
        }
    }

    return !m_users.empty();
}