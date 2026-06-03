#pragma once
#include "BasicWidget.h"
#include "Text.h"
#include "Configure.h"
#include <ctime>
#include <string>

class TopBar :
    public BasicWidget {
private:
    Text* m_title;
    Text* m_time;
public:
    TopBar(const std::wstring& title = L"", int x = 180, int y = 0, int w = 780, int h = 55);
    void show() override;

    void setTitle(const std::wstring& title);
    void updateTime();
    ~TopBar();
};

