#include "Window.h"
#include "Management.h"

int main() {
	Window w(960, 640, EX_SHOWCONSOLE );
	w.setWindowTitle(_T("学生个人财务管理系统"));

	Management m;
	m.run();

	return w.exec();
}


//测试user

//#include <iostream>
//#include "User.h"
//#include "FileManager.h"
//#include <string>
//using namespace std;
//
//int main() {
//	wstring nickname,username, password;
//	while (wcin >> nickname>>username >> password) {
//		User tempUser(nickname,username, password);
//		if (tempUser.loginUser()) {
//			wcout << L"success login" << endl;
//		}
//		else {
//			if (tempUser.addUser()) {
//				wcout << L"successfully add" << endl;
//			}
//			else {
//				wcout << L"failed to add" << endl;
//			}
//		}
//	}
//}

