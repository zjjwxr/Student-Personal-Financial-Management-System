#include "FileManager.h"
#include <windows.h>
#include <fstream>
#include <sstream>

FileManager::FileManager() {}

std::wstring FileManager::getUsersFilePath() {
    return L"./data/Users.dat";
}

std::wstring FileManager::getUserAccountsFilePath(const std::wstring& username) {
    return L"./data/" + username + L"/Accounts.dat";
}

std::wstring FileManager::getUserTransactionsFilePath(const std::wstring& username) {
    return L"./data/" + username + L"/Transactions.dat";
}



// 判断文件是否存在
bool FileManager::fileExists(const std::wstring& filename) {
    std::wifstream file(filename);
    return file.good();
}

// 创建文件夹
bool FileManager::createDirectory(const std::wstring& path) {
    return CreateDirectoryW(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
}

// 写文件（覆盖）
bool FileManager::writeTextToFile(const std::wstring& filename, const std::wstring& content) {
    std::wofstream ofs(filename);
    if (!ofs.is_open()) return false;
    ofs << content;
    ofs.close();
    return true;
}

// 读文件
std::wstring FileManager::readTextFromFile(const std::wstring& filename) {
    std::wifstream inFile(filename);
    if (!inFile.is_open()) return L"";
    std::wstringstream buffer;
    buffer << inFile.rdbuf();
    inFile.close();
    return buffer.str();
}

// 追加写文件
bool FileManager::appendTextToFile(const std::wstring& filename, const std::wstring& content) {
    std::wofstream ofs(filename, std::ios::app);
    if (!ofs.is_open()) return false;
    ofs << content;
    ofs .close();
    return true;
}

// 删除文件
bool FileManager::deleteFile(const std::wstring& filename) {
    return DeleteFileW(filename.c_str()) != 0;
}

// 获取数据文件夹路径
std::wstring FileManager::getDataDirectory() {
    return L"./data/";
}

