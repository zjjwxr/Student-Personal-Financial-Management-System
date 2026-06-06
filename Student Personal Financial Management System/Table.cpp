#include "Table.h"
#include <sstream>
#include <iomanip>

Table::Table(int x, int y, int w, int h)
    : BasicWidget(x, y, w, h), m_headerHeight(40), m_rowHeight(40),
      m_currentPage(1), m_rowsPerPage(10), m_totalPages(1) {
}

void Table::show() {
    // 绘制表格背景
    setfillcolor(WHITE);
    solidrectangle(m_x, m_y, m_x + m_w, m_y + m_h);

    // 绘制表头
    drawHeaders();

    // 绘制数据行
    drawRows();

    // 绘制分页
    drawPagination();

    // 绘制边框
    setlinestyle(PS_SOLID, 1);
    setlinecolor(m_borderColor);
    rectangle(m_x, m_y, m_x + m_w, m_y + m_h);
}

void Table::eventLoop(const ExMessage& msg) {
    // 处理分页按钮点击
    if (msg.message == WM_LBUTTONDOWN) {
        int paginationY = m_y + m_headerHeight + getVisibleRowCount() * m_rowHeight;
        int paginationHeight = 40;

        if (msg.y >= paginationY && msg.y <= paginationY + paginationHeight) {
            int centerX = m_x + m_w / 2;
            int btnWidth = 60;
            int btnHeight = 30;

            // 上一页按钮
            if (msg.x >= centerX - btnWidth - 10 && msg.x <= centerX - 10 &&
                msg.y >= paginationY + 5 && msg.y <= paginationY + 5 + btnHeight) {
                if (m_currentPage > 1) {
                    m_currentPage--;
                }
            }
            // 下一页按钮
            else if (msg.x >= centerX + 10 && msg.x <= centerX + 10 + btnWidth &&
                     msg.y >= paginationY + 5 && msg.y <= paginationY + 5 + btnHeight) {
                if (m_currentPage < m_totalPages) {
                    m_currentPage++;
                }
            }
        }
    }
}

void Table::addHeader(const std::wstring& title, int width) {
    TableHeader header;
    header.title = title;
    header.width = width;
    m_headers.push_back(header);
}

void Table::clearHeaders() {
    m_headers.clear();
}

void Table::addRow(const TableRow& row) {
    m_rows.push_back(row);
    updateTotalPages();
}

void Table::clearRows() {
    m_rows.clear();
    m_currentPage = 1;
    m_totalPages = 1;
}

void Table::setCurrentPage(int page) {
    if (page >= 1 && page <= m_totalPages) {
        m_currentPage = page;
    }
}

int Table::getCurrentPage() const {
    return m_currentPage;
}

int Table::getTotalPages() const {
    return m_totalPages;
}

void Table::setRowsPerPage(int rows) {
    m_rowsPerPage = rows;
    updateTotalPages();
}

void Table::setHeaderBgColor(COLORREF color) {
    m_headerBgColor = color;
}

void Table::setHeaderTextColor(COLORREF color) {
    m_headerTextColor = color;
}

void Table::setRowBgColor(COLORREF color) {
    m_rowBgColor = color;
}

void Table::setRowAltBgColor(COLORREF color) {
    m_rowAltBgColor = color;
}

void Table::setBorderColor(COLORREF color) {
    m_borderColor = color;
}

void Table::drawHeaders() {
    // 绘制表头背景
    setfillcolor(m_headerBgColor);
    solidrectangle(m_x, m_y, m_x + m_w, m_y + m_headerHeight);

    // 绘制表头文本
    setbkmode(TRANSPARENT);
    settextcolor(m_headerTextColor);
    settextstyle(16, 0, L"微软雅黑");

    int currentX = m_x;
    for (size_t i = 0; i < m_headers.size(); i++) {
        // 绘制表头边框
        setlinecolor(m_borderColor);
        line(currentX, m_y, currentX, m_y + m_headerHeight);

        // 绘制表头文本
        int textX = currentX + 10;
        int textY = m_y + (m_headerHeight - 16) / 2;
        outtextxy(textX, textY, m_headers[i].title.c_str());

        currentX += m_headers[i].width;
    }

    // 绘制最后一列的右边框
    line(currentX, m_y, currentX, m_y + m_headerHeight);

    // 绘制表头下边框
    line(m_x, m_y + m_headerHeight, m_x + m_w, m_y + m_headerHeight);
}

void Table::drawRows() {
    int startRow = getStartRowIndex();
    int visibleRows = getVisibleRowCount();

    for (int i = 0; i < visibleRows; i++) {
        int rowIndex = startRow + i;
        if (rowIndex >= (int)m_rows.size()) break;

        int rowY = m_y + m_headerHeight + i * m_rowHeight;

        // 绘制行背景
        if (i % 2 == 0) {
            setfillcolor(m_rowBgColor);
        } else {
            setfillcolor(m_rowAltBgColor);
        }
        solidrectangle(m_x, rowY, m_x + m_w, rowY + m_rowHeight);

        // 绘制单元格文本
        const TableRow& row = m_rows[rowIndex];
        int currentX = m_x;

        for (size_t j = 0; j < row.cells.size() && j < m_headers.size(); j++) {
            // 绘制单元格边框
            setlinecolor(m_borderColor);
            line(currentX, rowY, currentX, rowY + m_rowHeight);

            // 设置文本颜色
            if (row.cells[j].isIncome) {
                settextcolor(m_incomeColor);
            } else if (row.cells[j].text.find(L'-') == 0) {
                settextcolor(m_expenseColor);
            } else {
                settextcolor(row.cells[j].textColor);
            }

            // 绘制单元格文本
            setbkmode(TRANSPARENT);
            settextstyle(14, 0, L"微软雅黑");
            int textX = currentX + 10;
            int textY = rowY + (m_rowHeight - 14) / 2;
            outtextxy(textX, textY, row.cells[j].text.c_str());

            currentX += m_headers[j].width;
        }

        // 绘制最后一列的右边框
        line(currentX, rowY, currentX, rowY + m_rowHeight);

        // 绘制行下边框
        line(m_x, rowY + m_rowHeight, m_x + m_w, rowY + m_rowHeight);
    }
}

void Table::drawPagination() {
    int paginationY = m_y + m_headerHeight + getVisibleRowCount() * m_rowHeight;
    int paginationHeight = 40;

    // 绘制分页背景
    setfillcolor(WHITE);
    solidrectangle(m_x, paginationY, m_x + m_w, paginationY + paginationHeight);

    // 绘制分页按钮和信息
    int centerX = m_x + m_w / 2;
    int btnWidth = 60;
    int btnHeight = 30;
    int btnY = paginationY + 5;

    // 上一页按钮
    setfillcolor(RGB(245, 245, 245));
    solidrectangle(centerX - btnWidth - 10, btnY, centerX - 10, btnY + btnHeight);
    setlinestyle(PS_SOLID, 1);
    setlinecolor(m_borderColor);
    rectangle(centerX - btnWidth - 10, btnY, centerX - 10, btnY + btnHeight);

    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(14, 0, L"微软雅黑");
    outtextxy(centerX - btnWidth + 10, btnY + (btnHeight - 14) / 2, L"上一页");

    // 页码信息
    std::wstringstream ss;
    ss << m_currentPage << L" / " << m_totalPages;
    std::wstring pageInfo = ss.str();

    int pageInfoWidth = textwidth(pageInfo.c_str());
    outtextxy(centerX - pageInfoWidth / 2, btnY + (btnHeight - 14) / 2, pageInfo.c_str());

    // 下一页按钮
    setfillcolor(RGB(245, 245, 245));
    solidrectangle(centerX + 10, btnY, centerX + 10 + btnWidth, btnY + btnHeight);
    setlinestyle(PS_SOLID, 1);
    setlinecolor(m_borderColor);
    rectangle(centerX + 10, btnY, centerX + 10 + btnWidth, btnY + btnHeight);

    settextcolor(BLACK);
    outtextxy(centerX + 20, btnY + (btnHeight - 14) / 2, L"下一页");

    // 绘制分页上边框
    line(m_x, paginationY, m_x + m_w, paginationY);
}

int Table::getVisibleRowCount() const {
    int availableHeight = m_h - m_headerHeight - 40; // 减去分页高度
    int visibleRows = availableHeight / m_rowHeight;
    return std::min(visibleRows, m_rowsPerPage);
}

int Table::getStartRowIndex() const {
    return (m_currentPage - 1) * m_rowsPerPage;
}

void Table::updateTotalPages() {
    m_totalPages = ((int)m_rows.size() + m_rowsPerPage - 1) / m_rowsPerPage;
    if (m_totalPages == 0) m_totalPages = 1;
    if (m_currentPage > m_totalPages) {
        m_currentPage = m_totalPages;
    }
}