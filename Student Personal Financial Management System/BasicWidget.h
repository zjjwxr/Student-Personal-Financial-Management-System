#pragma once
#include "Configure.h"
class BasicWidget {
protected:
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	inline static ExMessage m_msg;
public:
	BasicWidget(int x, int y, int w, int h);//初始化位置和大小
	int getWidth() const; // 获取宽度
	int getHeight() const; // 获取高度
	void setFixedSize(int w, int h); //设置固定大小
	
	int getX() const;//获取x
	int getY() const;//获取y
	void setPosition(int x, int y); //设置位置

	bool isHover();//判断鼠标是否悬停在按钮上
	bool isClicked();//判断按钮是否被点击

	virtual void show() = 0;// 显示控件
};

