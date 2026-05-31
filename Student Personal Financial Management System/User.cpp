#include "User.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

User::User(std::wstring realname, std::wstring username, std::wstring password)
	: m_realname(realname), m_username(username), m_password(password) {
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
		int partitionPos1 = singleUserMessage.find(L'|');
		int partitionPos2 = singleUserMessage.find(L'|', partitionPos1 + 1);
		std::wstring temp_username = singleUserMessage.substr(partitionPos1 + 1,partitionPos2-partitionPos1-1);
		std::wstring temp_password = singleUserMessage.substr(partitionPos2 + 1);
		if (temp_username == m_username) {
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
	std::wstring content = m_realname+L'|'+m_username + L'|' + m_password + L'\n';
	return FileManager::appendTextToFile(FileManager::getUsersFilePath(), content);
}
