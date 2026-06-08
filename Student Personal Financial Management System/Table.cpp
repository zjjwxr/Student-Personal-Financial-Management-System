#include "Table.h"


Table::Table(int x, int y) :BasicWidget(x, y, 0, 0) {}

void Table::SetRowCol(int rows, int cols) {
    m_totalRows = rows;
    m_totalCols = cols;
    m_data.assign(m_totalRows, std::vector<TableCell>(m_totalCols));
    m_headers.assign(m_totalCols, Text(L""));
    m_colWidths.assign(m_totalCols, 80);//默认列宽80

}

void Table::SetColumnWidths(const std::vector<int>& widths) {
    if (widths.size() != m_colWidths.size()) return;
    m_colWidths = widths;
}

void Table::SetColumnWidth(int col, int width) {
    if (col >= 0 && col <= m_totalCols) m_colWidths[col] = width;
}

void Table::SetRowHeight(int height) {
    m_rowHeight = height;
}

void Table::SetHeaderHeight(int height) {
    m_headerHeight = height;
}

void Table::SetPaginationHeight(int height) {
    m_paginationHeight = height;
}

void Table::SetHeader(int col, const std::wstring& text) {
    if (col >= 0 && col < m_totalCols)m_headers[col].setText(text);
}

void Table::SetHeaders(const std::vector<std::wstring>& headerTexts) {
    if (headerTexts.size() != m_headers.size()) return;
    for (int i = 0; i < headerTexts.size(); i++) {
        m_headers[i].setText(headerTexts[i]);
    }
}

void Table::SetCellText(int row, int col, const std::wstring& text, COLORREF color) {
    if (row >= 0 && row < m_totalRows && col >= 0 && col < m_totalCols) {
        m_data[row][col].setText(text);
        m_data[row][col].setColor(color);
    }
}

std::wstring Table::GetCellText(int row, int col) {
    if (row >= 0 && row < m_totalRows && col >= 0 && col < m_totalCols) {
        return m_data[row][col].m_text.getText();
    }
    return std::wstring(L"");
}

void Table::UpdateVisibleRows(int availableHeight) {
    int headerHeight = m_showHeader ? m_headerHeight : 0;
    int remainHeight = availableHeight - headerHeight;
    if (remainHeight <= 0) m_visibleRows = 0;
    else m_visibleRows = remainHeight / m_rowHeight;
    UpdatePages();
}


void Table::UpdatePages() {
    if (m_visibleRows <= 0) {
        m_totalPages = 1;
    }
    else {
        m_totalPages = (m_totalRows + m_visibleRows - 1) / m_visibleRows;
        if (m_totalPages < 1) m_totalPages = 1;
    }
    if (m_currentPage > m_totalPages) m_currentPage = m_totalPages;
    if (m_currentPage < 1) m_currentPage = 1;
}

void Table::PrevPage() {
    if (m_currentPage > 1) {
        m_currentPage--;
    }
    UpdatePagination();
}

void Table::NextPage() {
    if (m_currentPage < m_totalPages) {
        m_currentPage++;
    }
    UpdatePagination();
}

void Table::GotoPage(int page) {
    if (page >= 1 && page <= m_totalPages) {
        m_currentPage = page;
    }
    UpdatePagination();
}

int Table::GetCurrentPage() const {
    return m_currentPage;
}

int Table::GetTotalPages() const {
    return m_totalPages;
}

void Table::SetColorTheme(COLORREF borderColor, COLORREF headerBgColor, COLORREF headerTextColor, COLORREF cellBgColor,COLORREF cellTextColor) {
    m_borderColor = borderColor;
    m_headerBgColor = headerBgColor;
    m_headerTextColor = headerTextColor;
    m_cellBgColor = cellBgColor;
    m_cellTextColor = cellTextColor;
}



int Table::GetTotalWidth() const {
    int total = 0;
    for (int w : m_colWidths) total += w;
    return total;
}

int Table::GetTotalHeight() const {
    int h = (m_showHeader ? m_headerHeight : 0) + m_visibleRows * m_rowHeight;
    return h;
}

void Table::UpdatePagination() {
    if (m_showPage.getText() == L"") {
        int height = m_paginationHeight / 2;
        m_showPage = Text(std::to_wstring(m_currentPage) + L" / " + std::to_wstring(m_totalPages));
        m_showPage.setFixedSize(height);
    }
    m_showPage.setText(std::to_wstring(m_currentPage) + L" / " + std::to_wstring(m_totalPages));
    int tx = m_x + this->GetTotalWidth() / 2 - ::textwidth(m_showPage.getText().c_str()) / 2;
    int ty = m_y + this->GetTotalHeight() + (m_paginationHeight - ::textheight(m_showPage.getText().c_str())) / 2;
    m_showPage.setPosition(tx, ty);
    if (m_buttons.size() == 0) {
        int buttonHeight = m_paginationHeight * 2 / 3;
        int buttonWidth = ::textwidth(L"上下一页");

        int temp = ::textwidth((L" / " + std::to_wstring(m_totalPages) + std::to_wstring(m_totalPages)).c_str());
        int bx1 = m_x + this->GetTotalWidth() / 2 - temp / 2 - buttonWidth;
        int bx2 = m_x + this->GetTotalWidth() / 2 + temp / 2 + temp / 4;
        int by = m_y + this->GetTotalHeight() + m_paginationHeight / 4;
        m_buttons.push_back(Button(L"上一页", bx1, by, buttonWidth, buttonHeight, 8, 8));
        m_buttons.push_back(Button(L"下一页", bx2, by, buttonWidth, buttonHeight, 8, 8));
        m_buttons[0].setDefaultColor(RGB(240, 240, 240));
        m_buttons[0].setHoverColor(RGB(200, 200, 200));
        m_buttons[0].setTextColor(BLACK);

        m_buttons[1].setDefaultColor(RGB(240, 240, 240));
        m_buttons[1].setHoverColor(RGB(200, 200, 200));
        m_buttons[1].setTextColor(BLACK);
    }
}



void Table::show() {
    int totalWidth = this->GetTotalWidth();
    int currentY = m_y;

    if (m_showHeader) {
        ::setfillcolor(m_headerBgColor);
        ::solidrectangle(m_x, currentY, m_x + totalWidth, currentY + m_headerHeight);

        int currentX = m_x;
        for (int i = 0; i < m_totalCols; i++) {
            int textWidth = ::textwidth(m_headers[i].getText().c_str());
            int textHeight = ::textheight(m_headers[i].getText().c_str());
            int tx = currentX + (m_colWidths[i] - textWidth) / 2;
            int ty = currentY + (m_headerHeight - textHeight) / 2;
            m_headers[i].setPosition(tx, ty);
            m_headers[i].show();
            currentX += m_colWidths[i];
        }

        currentY += m_headerHeight;
        ::setlinecolor(m_borderColor);
        ::line(m_x, currentY, m_x + totalWidth, currentY);
    }

    int startRow = (m_currentPage - 1) * m_visibleRows;
    int endRow = startRow + m_visibleRows;
    if (endRow > m_totalRows) endRow = m_totalRows;

    for (int row = startRow; row < endRow; row++) {
        ::setfillcolor(m_cellBgColor);
        ::solidrectangle(m_x, currentY, m_x + totalWidth, currentY + m_rowHeight);

        int currentX = m_x;
        for (int col = 0; col < m_totalCols; col++) {
            std::wstring text = m_data[row][col].m_text.getText();
            int textWidth = ::textwidth(text.c_str());
            int textHeight = ::textheight(text.c_str());
            int tx = currentX + (m_colWidths[col] - textWidth) / 2;
            int ty = currentY + (m_rowHeight - textHeight) / 2;
            m_data[row][col].m_text.setPosition(tx, ty);
            m_data[row][col].m_text.show();
            currentX += m_colWidths[col];
        }

        currentY += m_rowHeight;
        ::setlinecolor(m_borderColor);
        ::line(m_x, currentY, m_x + totalWidth, currentY);
    }


    UpdatePagination();
    if (m_buttons.size() >= 2) {
        ::setfillcolor(RGB(248, 249, 250));
        ::solidrectangle(m_x, currentY, m_x + totalWidth, currentY + m_paginationHeight);

        m_buttons[0].show();
        m_buttons[1].show();

        m_showPage.show();
    }
}

void Table::eventLoop(const ExMessage& msg) {
    m_msg = msg;

    if (m_buttons.size() >= 2) {
        m_buttons[0].eventLoop(msg);
        m_buttons[1].eventLoop(msg);

        if (m_buttons[0].isClicked()) {
            PrevPage();
        }
        if (m_buttons[1].isClicked()) {
            NextPage();
        }
    }
}
