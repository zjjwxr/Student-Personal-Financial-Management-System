#include "Login_Register.h"
LoginRegister::LoginRegister() : m_loginError(0) {
    ::settextstyle(60, 0, _T("微软雅黑"));

    for (int i = 0; i < 6; i++) {
        m_textBoxes.push_back(new TextBox);
    }
                                 //文本位置
    m_textBoxes[0]->setFixedSize(400, 50);
    m_textBoxes[0]->setPosition((Window::width() - m_textBoxes[0]->getWidth()) / 2, Window::height() / 2 - 100);
    m_textBoxes[1]->setFixedSize(400, 50);
    m_textBoxes[1]->setPosition((Window::width() - m_textBoxes[1]->getWidth()) / 2, Window::height() / 2 - 20);
    m_textBoxes[2]->setFixedSize(400, 50);
    m_textBoxes[2]->setPosition((Window::width() - m_textBoxes[2]->getWidth()) / 2, Window::height() / 2 - 140);
    m_textBoxes[3]->setFixedSize(400, 50);
    m_textBoxes[3]->setPosition((Window::width() - m_textBoxes[3]->getWidth()) / 2, Window::height() / 2 - 60);
    m_textBoxes[4]->setFixedSize(400, 50);
    m_textBoxes[4]->setPosition((Window::width() - m_textBoxes[4]->getWidth()) / 2, Window::height() / 2 + 20);
    m_textBoxes[5]->setFixedSize(400, 50);
    m_textBoxes[5]->setPosition((Window::width() - m_textBoxes[5]->getWidth()) / 2, Window::height() / 2 + 100);

                                   //登录按钮
    int lbtnW = 500, lbtnH = 60;
    int lbtnY = m_textBoxes[1]->getY() + m_textBoxes[1]->getHeight() + 40;
    int lcx = Window::width() / 2;
    Button* loginBtn = new Button(_T("立即登录"), lcx - lbtnW / 2, lbtnY, lbtnW, lbtnH);
    loginBtn->setTextColor(RGB(255, 255, 255));
    loginBtn->setDefaultColor(RGB(100, 150, 255));
    loginBtn->setHoverColor(RGB(0, 180, 0));
    m_buttons.push_back(loginBtn);

                                      //退出按钮
    Button* exitBtn = new Button(_T("退出"), 50, Window::height() - 150, 70, 30, 0);
    exitBtn->setHoverColor(RGB(255, 0, 0));
    m_buttons.push_back(exitBtn);

                                        //去注册按钮
    Button* gotoregiBtn = new Button(_T("去注册"), (Window::width() - 40) / 2, m_textBoxes[1]->getY() + m_textBoxes[1]->getHeight() + 120, 70, 28, 0);
    gotoregiBtn->setHoverColor(RGB(255, 0, 0));
    m_buttons.push_back(gotoregiBtn);

                                    //注册按钮
    int rbtnW = 500, rbtnH = 60;
    int rbtnY = m_textBoxes[5]->getY() + m_textBoxes[5]->getHeight() + 40;
    int rcx = Window::width() / 2;
    Button* regiBtn = new Button(_T("立即注册"), rcx - rbtnW / 2, rbtnY, rbtnW, rbtnH);
    regiBtn->setTextColor(RGB(255, 255, 255));
    regiBtn->setDefaultColor(RGB(100, 150, 255));
    regiBtn->setHoverColor(RGB(0, 180, 0));
    m_buttons.push_back(regiBtn);

                                          //去登录
    Button* gotologinBtn = new Button(_T("去登录"), (Window::width() - 40) / 2, m_textBoxes[5]->getY() + m_textBoxes[5]->getHeight() + 120, 70, 28, 0);
    gotologinBtn->setHoverColor(RGB(255, 0, 0));
    m_buttons.push_back(gotologinBtn);
}

LoginRegister::~LoginRegister() {
    for (auto box : m_textBoxes) delete box;
    for (auto btn : m_buttons) delete btn;
}
                                            //绘制
void LoginRegister::drawLogin() {
    settextstyle(60, 0, _T("黑体"));
    settextcolor(RGB(51, 51, 51));
    int titleW = textwidth(_T("用户登录"));
    outtextxy((Window::width() - titleW) / 2, 120, _T("用户登录"));

    settextstyle(20, 0, _T("宋体"));
    settextcolor(RGB(51, 51, 51));
    int W1 = textwidth(_T("宋体"));
    outtextxy((Window::width() - W1) / 2 - 100, m_textBoxes[1]->getY() + m_textBoxes[1]->getHeight() + 120, _T("没有账户？"));

    std::wstring text1 = _T("用户名");
    std::wstring text2 = _T("密码");
    ::settextstyle(30, 0, _T("微软雅黑"));
    settextcolor(RGB(80, 80, 80));
    ::outtextxy((Window::width() - m_textBoxes[0]->getWidth()) / 2 - 80, Window::height() / 2 - 100, text1.c_str());
    ::outtextxy((Window::width() - m_textBoxes[0]->getWidth()) / 2 - 80, Window::height() / 2 - 20, text2.c_str());

    for (int i = 0; i < 3; i++) {
        m_buttons[i]->show();
        m_buttons[i]->eventLoop(m_msg);
    }
    for (int i = 0; i < 2; i++) {
        m_textBoxes[i]->eventLoop(m_msg);
        m_textBoxes[i]->show();
    }

    settextstyle(18, 0, _T("微软雅黑"));
    std::wstring pa1 = L"请输入用户名";
    std::wstring acc1 = L"请输入密码";
    if (m_textBoxes[0]->getText().empty()) {
        settextcolor(RGB(150, 150, 150));
        int x = m_textBoxes[0]->getX() + 10;
        int y = m_textBoxes[0]->getY() + (m_textBoxes[0]->getHeight() - textheight(pa1.c_str())) / 2;
        outtextxy(x, y, pa1.c_str());
    }

    if (m_textBoxes[1]->getText().empty()) {
        settextcolor(RGB(150, 150, 150));
        int x = m_textBoxes[1]->getX() + 10;
        int y = m_textBoxes[1]->getY() + (m_textBoxes[1]->getHeight() - textheight(pa1.c_str())) / 2;
        outtextxy(x, y, acc1.c_str());
    }

    ::settextstyle(26, 0, _T("微软雅黑"));
    int msgY = m_textBoxes[1]->getY() + m_textBoxes[1]->getHeight() + 10;
    if (m_loginError == 1) {
        settextcolor(RGB(255, 100, 100));
        int titleW = textwidth(_T("用户名为空！"));
        ::outtextxy((Window::width() - titleW) / 2, msgY, _T("用户名为空！"));
    }
    else if (m_loginError == 2) {
        settextcolor(RGB(255, 100, 100));
         int titleW = textwidth(_T("密码为空！"));
        ::outtextxy((Window::width() - titleW) / 2, msgY, _T("密码为空！"));
    }
    else if (m_loginError == 3) {
        settextcolor(RGB(255, 100, 100));
        int titleW = textwidth(_T("登录失败！"));
        ::outtextxy((Window::width() - titleW) / 2, msgY, _T("登录失败！"));
    }
}
                                    //绘制
void LoginRegister::drawRegister() {
    settextstyle(60, 0, _T("黑体"));
    settextcolor(RGB(51, 51, 51));
    int titleW = textwidth(_T("用户注册"));
    outtextxy((Window::width() - titleW) / 2, 80, _T("用户注册"));

    settextstyle(20, 0, _T("宋体"));
    settextcolor(RGB(51, 51, 51));
    int W1 = textwidth(_T("宋体"));
    outtextxy((Window::width() - W1) / 2 - 100, m_textBoxes[5]->getY() + m_textBoxes[5]->getHeight() + 120, _T("已有账号？"));

    std::wstring text3 = _T("姓名");
    std::wstring text4 = _T("用户名");
    std::wstring text5 = _T("密码");
    std::wstring text6 = _T("确认密码");
    ::settextstyle(30, 0, _T("微软雅黑"));
    settextcolor(RGB(80, 80, 80));
    ::outtextxy((Window::width() - m_textBoxes[2]->getWidth()) / 2 - 100, Window::height() / 2 - 140, text3.c_str());
    ::outtextxy((Window::width() - m_textBoxes[3]->getWidth()) / 2 - 100, Window::height() / 2 - 60, text4.c_str());
    ::outtextxy((Window::width() - m_textBoxes[4]->getWidth()) / 2 - 100, Window::height() / 2 + 20, text5.c_str());
    ::outtextxy((Window::width() - m_textBoxes[5]->getWidth()) / 2 - 100, Window::height() / 2 + 100, text6.c_str());

    for (int i = 2; i < 6; i++) {
        m_textBoxes[i]->eventLoop(m_msg);
        m_textBoxes[i]->show();
    }
    for (int i = 3; i < 5; i++) {
        m_buttons[i]->show();
        m_buttons[i]->eventLoop(m_msg);
    }

    settextstyle(18, 0, _T("微软雅黑"));
    std::wstring r1 = L"请输入姓名";
    std::wstring r2 = L"请输入用户名";
    std::wstring r3 = L"请输入密码";
    std::wstring r4 = L"请再次输入密码";
    if (m_textBoxes[2]->getText().empty()) {
        settextcolor(RGB(150, 150, 150));
        int x = m_textBoxes[2]->getX() + 10;
        int y = m_textBoxes[2]->getY() + (m_textBoxes[2]->getHeight() - textheight(r1.c_str())) / 2;
        outtextxy(x, y, r1.c_str());
    }
    if (m_textBoxes[3]->getText().empty()) {
        settextcolor(RGB(150, 150, 150));
        int x = m_textBoxes[3]->getX() + 10;
        int y = m_textBoxes[3]->getY() + (m_textBoxes[3]->getHeight() - textheight(r2.c_str())) / 2;
        outtextxy(x, y, r2.c_str());
    }
    if (m_textBoxes[4]->getText().empty()) {
        settextcolor(RGB(150, 150, 150));
        int x = m_textBoxes[4]->getX() + 10;
        int y = m_textBoxes[4]->getY() + (m_textBoxes[4]->getHeight() - textheight(r3.c_str())) / 2;
        outtextxy(x, y, r3.c_str());
    }
    if (m_textBoxes[5]->getText().empty()) {
        settextcolor(RGB(150, 150, 150));
        int x = m_textBoxes[5]->getX() + 10;
        int y = m_textBoxes[5]->getY() + (m_textBoxes[5]->getHeight() - textheight(r4.c_str())) / 2;
        outtextxy(x, y, r4.c_str());
    }

    ::settextstyle(26, 0, _T("微软雅黑"));
    int msgY = m_textBoxes[5]->getY() + m_textBoxes[5]->getHeight() + 10;
    if (m_loginError == 7) {
        settextcolor(RGB(255, 100, 100));
        int titleW = textwidth(_T("注册失败，密码不相同！"));
        ::outtextxy((Window::width() - titleW) / 2, msgY, _T("注册失败，密码不相同！"));
    }
    else if (m_loginError == 8) {
        settextcolor(RGB(255, 100, 100));
        int titleW = textwidth(_T("注册失败，该用户已经存在！"));
        ::outtextxy((Window::width() - titleW) / 2, msgY, _T("注册失败，该用户已经存在！"));
    }
    else if (m_loginError == 4) {
        settextcolor(RGB(255, 100, 100));
        int titleW = textwidth(_T("注册失败，姓名不能为空！"));
        ::outtextxy((Window::width() - titleW) / 2, msgY, _T("注册失败，姓名不能为空！"));
    }
    else if (m_loginError == 5) {
        settextcolor(RGB(255, 100, 100));
        int titleW = textwidth(_T("注册失败，用户名不能为空！"));
        ::outtextxy((Window::width() - titleW) / 2, msgY, _T("注册失败，用户名不能为空！"));
    }
    else if (m_loginError == 6) {
        settextcolor(RGB(255, 100, 100));
        int titleW = textwidth(_T("注册失败，密码不能为空！"));
        ::outtextxy((Window::width() - titleW) / 2, msgY, _T("注册失败，密码不能为空！"));
    }
}
                                 //功能实现
void LoginRegister::handleLogin(int& currentState) {
    if (m_buttons[0]->isClicked()) {
        std::wstring uname = m_textBoxes[0]->getText();
        std::wstring pwd = m_textBoxes[1]->getText();
        if (uname.empty()) {
            m_loginError = 1;
        }
        else if (pwd.empty()) {
            m_loginError = 2;
        }
        else {
            User user(L"", uname, pwd);
            if (user.loginUser()) {
                m_loginError = 0;
                currentState = 2;
            }
            else {
                m_loginError = 3;
            }
        }
    }
    if (m_buttons[1]->isClicked()) {
        currentState = 7;
    }
    if (m_buttons[2]->isClicked()) {
        currentState = 1;
    }
}

void LoginRegister::handleRegister(int& currentState) {
    if (m_buttons[3]->isClicked()) {
        std::wstring name = m_textBoxes[2]->getText();
        std::wstring uname = m_textBoxes[3]->getText();
        std::wstring pwd = m_textBoxes[4]->getText();
        std::wstring confirmPwd = m_textBoxes[5]->getText();

        // 检查姓名是否为空
        if (name.empty()) {
            m_loginError = 4;  // 姓名为空
        }
        // 检查用户名是否为空
        else if (uname.empty()) {
            m_loginError = 5;  // 用户名为空
        }
        // 检查密码是否为空
        else if (pwd.empty()|| confirmPwd.empty()) {
            m_loginError = 6;  // 密码为空
        }
        // 检查两次密码是否一致
        else if (pwd != confirmPwd) {
            m_loginError = 7;  // 密码不相同
        }
        else {
            m_loginError = 0;
            User user(name, uname, pwd);
            if (user.addUser()) {
                currentState = 2;  // MENU
            }
            else {
                m_loginError = 8;  // 用户已存在
            }
        }
    }
    if (m_buttons[4]->isClicked()) {
        currentState = 0;
    }
}