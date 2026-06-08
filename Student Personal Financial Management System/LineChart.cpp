#include "LineChart.h"

LineChart::LineChart(int x, int y, int w, int h)
    : BasicWidget(x, y, w, h), m_title(nullptr),
    m_lineColor(RGB(46, 125, 255)), m_pointColor(RGB(46, 125, 255)) {
    m_title = new Text(L"支出趋势");
    m_title->setPosition(m_x + 20, m_y + 20);
    m_title->setFixedSize(16);
    m_title->setColor(RGB(51, 51, 51));
}

LineChart::~LineChart() {
    delete m_title;
}

void LineChart::setTitle(const std::wstring& title) {
    m_title->setText(title);
}

void LineChart::setData(const std::vector<double>& values, const std::vector<std::wstring>& labels) {
    m_values = values;
    m_labels = labels;
}

void LineChart::clearData() {
    m_values.clear();
    m_labels.clear();
}

void LineChart::drawGrid() {
    int paddingLeft = 40;
    int paddingRight = 40;
    int paddingTop = 50;
    int paddingBottom = 30;

    int chartWidth = m_w - paddingLeft - paddingRight;
    int chartHeight = m_h - paddingTop - paddingBottom;

    setlinecolor(RGB(230, 230, 230));

    for (int i = 0; i <= 4; i++) {
        int y = m_y + paddingTop + (chartHeight / 4) * i;
        line(m_x + paddingLeft, y, m_x + paddingLeft + chartWidth, y);
    }

    for (int i = 0; i <= 6; i++) {
        int x = m_x + paddingLeft + (chartWidth / 6) * i;
        line(x, m_y + paddingTop, x, m_y + paddingTop + chartHeight);
    }
}

void LineChart::drawLine() {
    if (m_values.size() < 2) return;

    int paddingLeft = 40;
    int paddingRight = 40;
    int paddingTop = 50;
    int paddingBottom = 30;

    int chartWidth = m_w - paddingLeft - paddingRight;
    int chartHeight = m_h - paddingTop - paddingBottom;

    double maxValue = 0;
    for (double v : m_values) {
        if (v > maxValue) maxValue = v;
    }
    if (maxValue == 0) maxValue = 1;

    setlinecolor(m_lineColor);
    setlinestyle(PS_SOLID, 2);

    int prevX = 0, prevY = 0;
    for (size_t i = 0; i < m_values.size(); i++) {
        int x = m_x + paddingLeft + (chartWidth / (m_values.size() - 1)) * i;
        int y = m_y + paddingTop + chartHeight - (m_values[i] / maxValue) * chartHeight;

        if (i > 0) {
            line(prevX, prevY, x, y);
        }

        prevX = x;
        prevY = y;
    }

    setlinestyle(PS_SOLID, 1);
}

void LineChart::drawPoints() {
    if (m_values.empty()) return;

    int paddingLeft = 40;
    int paddingRight = 40;
    int paddingTop = 50;
    int paddingBottom = 30;

    int chartWidth = m_w - paddingLeft - paddingRight;
    int chartHeight = m_h - paddingTop - paddingBottom;

    double maxValue = 0;
    for (double v : m_values) {
        if (v > maxValue) maxValue = v;
    }
    if (maxValue == 0) maxValue = 1;

    setfillcolor(m_pointColor);

    for (size_t i = 0; i < m_values.size(); i++) {
        int x = m_x + paddingLeft + (chartWidth / (m_values.size() - 1)) * i;
        int y = m_y + paddingTop + chartHeight - (m_values[i] / maxValue) * chartHeight;

        solidcircle(x, y, 4);
        setfillcolor(WHITE);
        solidcircle(x, y, 2);
        setfillcolor(m_pointColor);
    }
}

void LineChart::drawXLabels() {
    int paddingLeft = 40;
    int paddingRight = 40;
    int paddingTop = 50;
    int paddingBottom = 30;

    int chartWidth = m_w - paddingLeft - paddingRight;
    int chartHeight = m_h - paddingTop - paddingBottom;

    for (size_t i = 0; i < m_labels.size(); i++) {
        int x = m_x + paddingLeft + (chartWidth / (m_labels.size() - 1)) * i;
        int y = m_y + paddingTop + chartHeight + 10;

        std::wstring label = m_labels[i];
        int textWidth = textwidth(label.c_str());

        Text* labelText = new Text(label);
        labelText->setPosition(x - textWidth / 2, y);
        labelText->setFixedSize(12);
        labelText->setColor(RGB(102, 102, 102));
        labelText->show();

        delete labelText;
    }
}

void LineChart::show() {
    setfillcolor(WHITE);
    setlinecolor(RGB(224, 224, 224));
    solidroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 12, 12);
    roundrect(m_x, m_y, m_x + m_w, m_y + m_h, 12, 12);

    if (m_title) {
        m_title->show();
    }

    drawGrid();
    drawLine();
    drawPoints();
    drawXLabels();
}