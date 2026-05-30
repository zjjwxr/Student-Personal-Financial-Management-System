#include "User.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

User::User(std::wstring username, std::wstring password): m_username(username),m_password(password){
}

bool User::loginUser() {
	std::wifstream ifs;
	ifs.open(FileManager::getUsersFilePath());
	if (!ifs.is_open()) {
		std::wcout << L"Users.dat could't be opened!\n";
		return false;
	}
	std::wstring singleUserMessage;
	while (std::getline(ifs, singleUserMessage)) {
		int partitionPos = singleUserMessage.find(L'|');
		std::wstring temp_userName = singleUserMessage.substr(0, partitionPos);
		std::wstring temp_password = singleUserMessage.substr(partitionPos + 1);
		if (temp_userName == m_username) {
			if (temp_password == m_password) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

bool User::addUser() {
	std::wstring content = m_username + L'|' + m_password + L'\n';
	return FileManager::appendTextToFile(FileManager::getUsersFilePath(), content);
}
