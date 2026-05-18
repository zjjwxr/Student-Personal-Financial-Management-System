#pragma once
#include "Configure.h"
class Window {
public:
	Window(int w, int h, int flag);
	void setWindowTitle(const std::wstring& s);
	int exec();

	static int width();
	static int height();
	static void drawBackground(const IMAGE& img);
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	static bool hasMessage() { return peekmessage(&m_msg, EX_MOUSE | EX_KEY | EX_CHAR); }
	static ExMessage& getMessage() { return m_msg; }
private:
	HWND m_handle;
	inline static ExMessage m_msg;
};

