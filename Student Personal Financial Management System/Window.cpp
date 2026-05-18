#include "Window.h"


Window::Window(int w, int h, int flag=NULL) {
	m_handle = ::initgraph(w, h, flag);
	::setbkmode(TRANSPARENT);
}

void Window::setWindowTitle(const std::wstring& s) {
	::SetWindowText(m_handle, s.data());
}

int Window::exec() {
	return getchar();
}

int Window::width() {
	return ::getwidth();
}

int Window::height() {
	return ::getheight();
}

void Window::drawBackground(const IMAGE& img) {
	::putimage(0, 0, &img);
}

void Window::clear() {
	::cleardevice();
}

void Window::beginDraw() {
	::BeginBatchDraw();
}

void Window::flushDraw() {
	::FlushBatchDraw();
}

void Window::endDraw() {
	::EndBatchDraw();
}