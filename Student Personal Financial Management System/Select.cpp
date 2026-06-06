#include "Select.h"
#include <algorithm>

Select::Select(int x, int y, int w, int h)
    : BasicWidget(x, y, w, h), m_selectedIndex(-1), m_isOpen(false) {
    m_displayText = Text(L"", x + 10, y + 5, w - 40, h - 10);
    m_displayText.setTextSize(18);
    m_displayText.setTextColor(m_textColor);
}

void Select::show() {
    // 绘制下拉框主体
    setfillcolor(m_currentColor);
    solidrectangle(m_x, m_y, m_x + m_w, m_y + m_h);

    // 绘制边框
    setlinestyle(PS_SOLID, 1);
    setlinecolor(m_borderColor);
    rectangle(m_x, m_y, m_x + m_w, m_y + m_h);

    // 绘制选中的文本
    if (m_selectedIndex >= 0 && m_selectedIndex < m_options.size()) {
        m_displayText.setText(m_options[m_selectedIndex]);
    } else if (!m_options.empty()) {
        m_displayText.setText(m_options[0]);
        m_selectedIndex = 0;
    }
    m_displayText.show();

    // 绘制下拉箭头
    drawArrow();

    // 如果下拉框打开，绘制选项列表
    if (m_isOpen) {
        drawDropdown();
    }
}

void Select::eventLoop(const ExMessage& msg) {
    if (msg.message == WM_LBUTTONDOWN) {
        // 检查是否点击了下拉框
        if (msg.x >= m_x && msg.x <= m_x + m_w && msg.y >= m_y && msg.y <= m_y + m_h) {
            m_isOpen = !m_isOpen;
        }
        // 如果下拉框打开，检查是否点击了选项
        else if (m_isOpen) {
            int dropdownY = m_y + m_h;
            int dropdownHeight = getDropdownHeight();
            if (msg.x >= m_x && msg.x <= m_x + m_w && msg.y >= dropdownY && msg.y <= dropdownY + dropdownHeight) {
                int clickedIndex = (msg.y - dropdownY) / getOptionHeight();
                if (clickedIndex >= 0 && clickedIndex < m_options.size()) {
                    m_selectedIndex = clickedIndex;
                    m_isOpen = false;
                }
            } else {
                m_isOpen = false;
            }
        }
    }

    // 悬停效果
    if (isHover() && !m_isOpen) {
        m_currentColor = m_hoverColor;
    } else if (!m_isOpen) {
        m_currentColor = m_defaultColor;
    }
}

void Select::addOption(const std::wstring& option) {
    m_options.push_back(option);
    if (m_selectedIndex == -1) {
        m_selectedIndex = 0;
    }
}

void Select::clearOptions() {
    m_options.clear();
    m_selectedIndex = -1;
}

void Select::setSelectedIndex(int index) {
    if (index >= 0 && index < m_options.size()) {
        m_selectedIndex = index;
    }
}

int Select::getSelectedIndex() const {
    return m_selectedIndex;
}

std::wstring Select::getSelectedText() const {
    if (m_selectedIndex >= 0 && m_selectedIndex < m_options.size()) {
        return m_options[m_selectedIndex];
    }
    return L"";
}

void Select::setTextColor(COLORREF color) {
    m_textColor = color;
    m_displayText.setTextColor(color);
}

void Select::setBorderColor(COLORREF color) {
    m_borderColor = color;
}

void Select::setTextFont(const std::wstring& fontName) {
    m_displayText.setFont(fontName);
}

void Select::setTextSize(int height, int width) {
    m_displayText.setTextSize(height, width);
}

void Select::drawDropdown() {
    int dropdownY = m_y + m_h;
    int dropdownHeight = getDropdownHeight();

    // 绘制下拉框背景
    setfillcolor(WHITE);
    solidrectangle(m_x, dropdownY, m_x + m_w, dropdownY + dropdownHeight);

    // 绘制边框
    setlinestyle(PS_SOLID, 1);
    setlinecolor(m_borderColor);
    rectangle(m_x, dropdownY, m_x + m_w, dropdownY + dropdownHeight);

    // 绘制每个选项
    int optionHeight = getOptionHeight();
    for (size_t i = 0; i < m_options.size(); i++) {
        int optionY = dropdownY + i * optionHeight;

        // 绘制选项背景
        if (i == m_selectedIndex) {
            setfillcolor(RGB(230, 240, 255));
        } else {
            setfillcolor(WHITE);
        }
        solidrectangle(m_x, optionY, m_x + m_w, optionY + optionHeight);

        // 绘制选项文本
        setbkmode(TRANSPARENT);
        settextcolor(m_textColor);
        settextstyle(18, 0, L"微软雅黑");
        outtextxy(m_x + 10, optionY + (optionHeight - 18) / 2, m_options[i].c_str());

        // 绘制分隔线
        if (i < m_options.size() - 1) {
            setlinecolor(RGB(240, 240, 240));
            line(m_x, optionY + optionHeight, m_x + m_w, optionY + optionHeight);
        }
    }
}

void Select::drawArrow() {
    int arrowX = m_x + m_w - 25;
    int arrowY = m_y + m_h / 2;

    setlinecolor(m_textColor);
    setlinestyle(PS_SOLID, 2);

    // 绘制向下箭头
    POINT points[3];
    if (m_isOpen) {
        // 向上箭头
        points[0].x = arrowX;
        points[0].y = arrowY - 5;
        points[1].x = arrowX - 5;
        points[1].y = arrowY + 5;
        points[2].x = arrowX + 5;
        points[2].y = arrowY + 5;
    } else {
        // 向下箭头
        points[0].x = arrowX;
        points[0].y = arrowY + 5;
        points[1].x = arrowX - 5;
        points[1].y = arrowY - 5;
        points[2].x = arrowX + 5;
        points[2].y = arrowY - 5;
    }
    polygon(points, 3);
}

int Select::getOptionHeight() const {
    return 35;
}

int Select::getDropdownHeight() const {
    int visibleOptions = std::min((int)m_options.size(), 5);
    return visibleOptions * getOptionHeight();
}