#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include "Text.h"
#include <vector>
#include <string>
#include <map>

struct PieSlice {
    std::wstring label;
    double value;
    COLORREF color;
};

struct DataPoint {
    std::wstring label;
    double value;
};

enum class ChartType {
    PIE,
    LINE
};

class Chart : public BasicWidget {
private:
    ChartType m_chartType;
    std::vector<PieSlice> m_pieSlices;
    std::vector<DataPoint> m_lineData;
    std::wstring m_title;

    COLORREF m_titleColor = RGB(51, 51, 51);
    COLORREF m_axisColor = RGB(200, 200, 200);
    COLORREF m_lineColor = RGB(46, 125, 255);
    COLORREF m_textColor = RGB(102, 102, 102);

public:
    Chart(ChartType type, const std::wstring& title = L"", int x = 0, int y = 0, int w = 350, int h = 250);
    void show() override;
    void eventLoop(const ExMessage& msg);

    void addPieSlice(const std::wstring& label, double value, COLORREF color);
    void clearPieSlices();
    void addLineDataPoint(const std::wstring& label, double value);
    void clearLineData();

    void setTitle(const std::wstring& title);
    void setTitleColor(COLORREF color);
    void setAxisColor(COLORREF color);
    void setLineColor(COLORREF color);
    void setTextColor(COLORREF color);

private:
    void drawPieChart();
    void drawLineChart();
    void drawTitle();
    void drawLegend();
    double getTotalPieValue() const;
};