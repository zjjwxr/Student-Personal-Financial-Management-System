#pragma once
#include "Configure.h"
#include "Button.h"
#include "TextBox.h"
#include "Window.h"
#include "User.h"
#include "SideBar.h"
#include "TopBar.h"
#include "Login_Register.h"
#include <vector>
class Management {
	enum State {
		LOGIN,
		REGISTERUSER,
		MENU,
		ACCOUNT,
		TRANSACTION,
		TABLE,
		SETTING,
		EXIT
	};
public:
	Management();
	void run();// 运行系统
	void login(); // 登录系统
	void registerUser();// 注册账号
	void menu(); //首页
	void account();
	void transaction();
	void table();
	void setting();
private:
	State currentState=LOGIN;
	IMAGE m_background;
	inline static ExMessage m_msg;

	

	//用于用户登录
	LoginRegister m_loginRegister;

	User m_user;
	

	SideBar* m_sideBar;
	TopBar* m_topBar;
};

