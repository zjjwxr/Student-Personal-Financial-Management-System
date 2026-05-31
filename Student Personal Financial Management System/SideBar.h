#pragma once
#include "BasicWidget.h"
#include "Button.h"
#include "Text.h"
#include "User.h"
#include <vector>

class SideBar :
    public BasicWidget {
private:
    User* m_user;
    std::vector<Button*> m_buttons;
    Text* m_realnameText;
public:
    SideBar(User* user, int x = 0, int y = 0, int w = 180, int h = 640);
    void eventLoop(const ExMessage& msg);
    void show() override;

    ~SideBar();
};

