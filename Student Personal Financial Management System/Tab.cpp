#include "Tab.h"
#include "Button.h"

Tab::Tab(int x, int y, int w, int h)
    : BasicWidget(x, y, w, h), m_activeIndex(0) {
}

Tab::~Tab() {
    for (auto btn : m_tabButtons) {
        delete btn;
    }
    m_tabButtons.clear();
}

void Tab::show() {
    // 更新Tab按钮
    updateTabButtons();

    // 显示所有Tab按钮
    for (auto btn : m_tabButtons) {
        btn->show();
    }
}

void Tab::eventLoop(const ExMessage& msg) {
    for (size_t i = 0; i < m_tabButtons.size(); i++) {
        m_tabButtons[i]->eventLoop(msg);

        // 检查Tab按钮是否被点击
        if (m_tabButtons[i]->isClicked()) {
            m_activeIndex = i;
            updateTabButtons();
            break;
        }
    }
}

void Tab::addTab(const std::wstring& label) {
    m_tabLabels.push_back(label);
    updateTabButtons();
}

void Tab::clearTabs() {
    m_tabLabels.clear();
    for (auto btn : m_tabButtons) {
        delete btn;
    }
    m_tabButtons.clear();
    m_activeIndex = 0;
}

void Tab::setActiveIndex(int index) {
    if (index >= 0 && index < m_tabLabels.size()) {
        m_activeIndex = index;
        updateTabButtons();
    }
}

int Tab::getActiveIndex() const {
    return m_activeIndex;
}

void Tab::setActiveColor(COLORREF color) {
    m_activeColor = color;
    updateTabButtons();
}

void Tab::setInactiveColor(COLORREF color) {
    m_inactiveColor = color;
    updateTabButtons();
}

void Tab::setActiveTextColor(COLORREF color) {
    m_activeTextColor = color;
    updateTabButtons();
}

void Tab::setInactiveTextColor(COLORREF color) {
    m_inactiveTextColor = color;
    updateTabButtons();
}

void Tab::updateTabButtons() {
    // 清除现有按钮
    for (auto btn : m_tabButtons) {
        delete btn;
    }
    m_tabButtons.clear();

    if (m_tabLabels.empty()) return;

    // 计算每个Tab的宽度
    int tabWidth = m_w /(int) m_tabLabels.size();

    // 创建新的Tab按钮
    for (size_t i = 0; i < m_tabLabels.size(); i++) {
        if (i == (int)m_activeIndex) {
        int tabX = m_x + (int)i * tabWidth;
        Button* btn = new Button(m_tabLabels[i], tabX, m_y, tabWidth, m_h);
        btn->setTextSize(16);

        if (i == (int)m_activeIndex) {
            btn->setDefaultColor(m_activeColor);
            btn->setHoverColor(m_activeColor);
            btn->setTextColor(m_activeTextColor);
        } else {
            btn->setDefaultColor(m_inactiveColor);
            btn->setHoverColor(m_inactiveColor);
            btn->setTextColor(m_inactiveTextColor);
        }

        m_tabButtons.push_back(btn);
    }
}