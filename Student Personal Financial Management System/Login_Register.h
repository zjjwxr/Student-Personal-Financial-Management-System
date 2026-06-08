#pragma once
#include "Window.h"
#include "Button.h"
#include "TextBox.h"
#include "User.h"
#include <vector>
class LoginRegister {
private:
    std::vector<TextBox*> m_textBoxes;
    std::vector<Button*> m_buttons;
    int m_loginError;
    ExMessage m_msg;
    User* m_currentUser;
public:
    LoginRegister();  
     ~LoginRegister();
     User* getCurrentUser() { return m_currentUser; } // 获取当前登录用户
    void drawLogin();
    void drawRegister();
    void handleLogin(int& currentState);
    void handleRegister(int& currentState);
    void resetError() { m_loginError = 0; }
    void setMessage(const ExMessage& msg) { m_msg = msg; }

    void reset();
};
