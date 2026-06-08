#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include "Text.h"
#include "Button.h"
#include <vector>

class TableCell {
public:
    Text m_text;
    COLORREF m_textColor;

    TableCell(const std::wstring& text = L"", COLORREF color = BLACK) : m_text(text), m_textColor(color) {
        m_text.setColor(color);
    }

    void setText(const std::wstring& text) {
        m_text.setText(text);
    }

    void setColor(COLORREF color) {
        m_textColor = color;
        m_text.setColor(color);
    }
};
class Table :
    public BasicWidget {
private:
    int m_totalRows = 0;                    // 总行数（不含表头）
    int m_totalCols = 0;                      // 总列数
    std::vector<int> m_colWidths;         // 各列宽度
    int m_rowHeight = 25;                   // 行高
    int m_headerHeight = 30;                 // 表头高度
    int m_paginationHeight = 50;            //翻页栏高度
    int m_visibleRows = 0;              // 可视区域最多显示行数（不含表头）
    int m_currentPage = 1;                // 当前页码
    int m_totalPages = 1;                // 总页数

    std::vector<std::vector<TableCell>> m_data;  // 表格数据 [行][列]
    std::vector<Text> m_headers;          // 表头文字
    std::vector<Button>m_buttons;       //翻页按钮
    Text m_showPage;  //当前页面显示

    bool m_showHeader = true;                    // 是否显示表头

    COLORREF m_borderColor = BLACK;                    // 边框颜色
    COLORREF m_headerBgColor = RGB(248, 249, 250);         // 表头背景色
    COLORREF m_headerTextColor = RGB(102, 102, 102);              // 表头文字颜色
    COLORREF m_cellBgColor = WHITE;                    // 单元格背景色
    COLORREF m_cellTextColor = BLACK;            // 单元格文字颜色

public:
    Table(int x = 0, int y = 0);
    void SetRowCol(int rows, int cols);// 设置表格总行数和总列数
    void SetColumnWidths(const std::vector<int>& widths); // 设置各列宽度（传入宽度数组）
    void SetColumnWidth(int col, int width);// 设置某列宽度
    void SetRowHeight(int height);// 设置行高
    void SetHeaderHeight(int height);// 设置表头高度
    void SetPaginationHeight(int height); //设置翻页栏高度
    void SetHeader(int col, const std::wstring& text);// 设置表头文本
    void SetHeaders(const std::vector<std::wstring>& headerTexts);// 批量设置表头
    void SetCellText(int row, int col, const std::wstring& text, COLORREF color = BLACK);// 设置单元格文本
    
    std::wstring GetCellText(int row, int col);// 获取单元格文本

    void UpdateVisibleRows(int availableHeight);// 根据窗口高度计算可视行数（需要传入表格可用高度）

    void UpdatePages();// 更新总页数和当前页
    void PrevPage();// 翻页：上一页
    void NextPage();// 翻页：下一页
    void GotoPage(int page);// 跳转到指定页（从0开始）
    int GetCurrentPage() const;// 获取当前页码
    int GetTotalPages() const;// 获取总页数

    void SetColorTheme(COLORREF borderColor, COLORREF headerBgColor, COLORREF headerTextColor,
        COLORREF cellBgColor,COLORREF cellTextColor);// 设置颜色主题

    int GetTotalWidth() const;// 获取表格总宽度
    int GetTotalHeight() const;// 获取表格总高度（含表头，不含翻页区域）

    void UpdatePagination();//更新加载翻页栏

    void show() override;
    void eventLoop(const ExMessage& msg);
};

