#include "Window.h"
#include "Management.h"
#include "FileManager.h"

int main() {
	Window w(960, 640, EX_SHOWCONSOLE );
	w.setWindowTitle(_T("学生个人财务管理系统"));

	Management m;
	m.run();

	return w.exec();
}


