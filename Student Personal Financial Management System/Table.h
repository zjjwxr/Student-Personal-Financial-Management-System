#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include "Text.h"
#include <vector>
#include <string>

struct TableHeader {
    std::wstring title;
    int width;
};

struct TableCell {
    std::wstring text;
    COLORREF textColor;
    bool isIncome;
};

struct TableRow {
    std::vector<TableCell> cells;
};

class Table : public BasicWidget {
private:
    std::vector<TableHeader> m_headers;
    std::vector<TableRow> m_rows;
    int m_headerHeight;
    int m_rowHeight;
    int m_currentPage;
    int m_rowsPerPage;
    int m_totalPages;

    COLORREF m_headerBgColor = RGB(248, 249, 250);
    COLORREF m_headerTextColor = RGB(102, 102, 102);
    COLORREF m_rowBgColor = WHITE;
    COLORREF m_rowAltBgColor = RGB(250, 250, 250);
    COLORREF m_borderColor = RGB(240, 240, 240);
    COLORREF m_incomeColor = RGB(124, 179, 66);
    COLORREF m_expenseColor = RGB(255, 107, 107);

public:
    Table(int x = 0, int y = 0, int w = 700, int h = 400);
    void show() override;
    void eventLoop(const ExMessage& msg);

    void addHeader(const std::wstring& title, int width);
    void clearHeaders();
    void addRow(const TableRow& row);
    void clearRows();

    void setCurrentPage(int page);
    int getCurrentPage() const;
    int getTotalPages() const;
    void setRowsPerPage(int rows);

    void setHeaderBgColor(COLORREF color);
    void setHeaderTextColor(COLORREF color);
    void setRowBgColor(COLORREF color);
    void setRowAltBgColor(COLORREF color);
    void setBorderColor(COLORREF color);

private:
    void drawHeaders();
    void drawRows();
    void drawPagination();
    int getVisibleRowCount() const;
    int getStartRowIndex() const;
    void updateTotalPages();
};