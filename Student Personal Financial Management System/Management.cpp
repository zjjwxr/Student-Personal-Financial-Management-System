#include "Management.h"

Management::Management() {
	::loadimage(&m_background, L"./images/background.png", Window::width(), Window::height());


	login_textBoxes.push_back(new textBox);
	login_textBoxes.push_back(new textBox);
	::settextstyle(60, 0, L"微软雅黑");
	for(int i=0;i<login_textBoxes.size();i++){
		login_textBoxes[i]->setFixedSize(400, 60);
		int login_tbx = (Window::width() - login_textBoxes[i]->getWidth())/ 2;
		int login_tby = (Window::height() - 4 * 60) / 2 + (2 * i + 1) * 60;
		login_textBoxes[i]->setPosition(login_tbx,login_tby);
	}

}

void Management::run() {
	int currentState = LOGIN;
	Window::beginDraw();
	while (true) {
		Window::clear();
		Window::drawBackground(m_background);
		if (Window::hasMessage()) {
			m_msg = Window::getMessage();
		}
		else m_msg.message = 0;//没有消息时，重置消息，防止上次的消息影响当前界面
		switch (currentState) {
		case LOGIN:
			login();
			break;
		case MENU:
			menu();
			break;
		default:
			exit(0);
			break;
		}
		Window::flushDraw();
	}
	Window::endDraw();
}

void Management::login() {
	std::wstring text1 = L"用户名";
	std::wstring text2 = L"密码";
	::settextstyle(60, 0, L"微软雅黑");
	int login_tx = (Window::width() - login_textBoxes[0]->getWidth()) / 2;
	int login_ty = (Window::height() - 4 * 60) / 2;
	::outtextxy(login_tx, login_ty, text1.c_str());
	::outtextxy(login_tx, login_ty + 2 * 60, text2.c_str());
	//for (auto& btn : login_Buttons) {
	//	btn->show();
	//	btn->eventLoop(m_msg);
	//}
	for(auto&btx:login_textBoxes){
		btx->eventLoop(m_msg);
		btx->show();
	}
}

void Management::menu() {
}
