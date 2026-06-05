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

public:
    LoginRegister();  
     ~LoginRegister();

    void drawLogin();
    void drawRegister();
    void handleLogin(int& currentState);
    void handleRegister(int& currentState);
    void resetError() { m_loginError = 0; }
    void setMessage(const ExMessage& msg) { m_msg = msg; }

};
