#pragma once
#include "BasicWidget.h"
#include "Text.h"
#include "Configure.h"
#include <vector>

// 折线图类 - 用于显示数据随时间变化的趋势
// 继承自BasicWidget，支持自定义位置和大小
class LineChart : public BasicWidget {
private:
    std::vector<double> m_values;          // 数据值数组（Y轴）
    std::vector<std::wstring> m_labels;    // 数据标签数组（X轴）
    Text* m_title;                         // 图表标题
    COLORREF m_lineColor;                  // 折线颜色
    COLORREF m_pointColor;                 // 数据点颜色

    // 绘制网格线（水平和垂直）
    void drawGrid();
    // 绘制折线连接各数据点
    void drawLine();
    // 绘制数据点（带空心效果）
    void drawPoints();
    // 绘制X轴标签
    void drawXLabels();

public:
    // 构造函数：初始化折线图位置和大小
    // @param x, y: 左上角坐标
    // @param w, h: 宽度和高度
    LineChart(int x = 0, int y = 0, int w = 350, int h = 250);

    // 析构函数：释放动态创建的Text对象
    ~LineChart();

    // 设置图表标题
    // @param title: 标题文本
    void setTitle(const std::wstring& title);

    // 设置图表数据
    // @param values: 数据值数组（如每日支出金额）
    // @param labels: 数据标签数组（如日期或星期）
    void setData(const std::vector<double>& values, const std::vector<std::wstring>& labels);

    // 清空所有数据
    void clearData();

    // 显示折线图（绘制背景、标题、网格、折线、数据点、标签）
    void show() override;
};