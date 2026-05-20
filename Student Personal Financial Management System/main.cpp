#include "Window.h"
#include "Management.h"

int main() {
	Window w(960, 640, EX_SHOWCONSOLE );
	w.setWindowTitle(_T("学生个人财务管理系统"));

	Management m;
	m.run();

	return w.exec();
}


//#include <easyx.h>
//#include <string>
//
//int main() {
//    initgraph(400, 300);
//    setbkmode(TRANSPARENT);
//    settextstyle(20, 0, L"微软雅黑");
//
//    std::wstring text = L"";
//    ExMessage msg;  // ✅ 用来接收消息
//
//    BeginBatchDraw();
//    while (true) {
//        cleardevice();
//
//        // ✅ peekmessage 直接拿到消息，不要再用 getmessage
//        while (peekmessage(&msg, EX_KEY | EX_CHAR)) {
//            if (msg.message == WM_CHAR) {
//                wchar_t ch = (wchar_t)msg.ch;
//                if (ch >= 32 && ch != 127) {
//                    text.push_back(ch);
//                }
//            }
//            if (msg.message == WM_KEYDOWN) {
//                if (msg.vkcode == VK_BACK && !text.empty()) {
//                    text.pop_back();
//                }
//            }
//        }
//
//        outtextxy(10, 10, text.c_str());
//        FlushBatchDraw();
//    }
//
//    EndBatchDraw();
//    closegraph();
//    return 0;
//}