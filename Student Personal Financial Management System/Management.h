#pragma once
#include "Configure.h"
#include "Button.h"
#include "TextBox.h"
#include "Window.h"
#include "User.h"
#include <vector>
class Management {
	enum State {
		LOGIN,
		MENU
	};
public:
	Management();
	void run();// 运行系统
	void login(); // 登录系统
	void menu(); //目录界面
private:
	State currentState;
	IMAGE m_background;
	inline static ExMessage m_msg;

	std::vector<Button*> login_Buttons;
	std::vector<TextBox*>login_TextBoxes;

	//用于用户登录
	User m_user;
	int m_loginError = 0;
};

