#pragma once
#include "User.h"
#include <string>

class FileManager {
public:
    FileManager();

    static std::wstring getUsersFilePath();
    static std::wstring getUserAccountsFilePath(const std::wstring& username);
    static std::wstring getUserTransactionsFilePath(const std::wstring& username);

    static bool fileExists(const std::wstring& filename);
    static bool createDirectory(const std::wstring& path);
    static bool writeTextToFile(const std::wstring& filename, const std::wstring& content);
    static std::wstring readTextFromFile(const std::wstring& filename);
    static bool appendTextToFile(const std::wstring& filename, const std::wstring& content);
    static bool deleteFile(const std::wstring& filename);

    static std::wstring getDataDirectory();

};