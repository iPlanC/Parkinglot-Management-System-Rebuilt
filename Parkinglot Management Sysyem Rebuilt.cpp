#include "included.h"

using namespace std;
using namespace tinyxml2;

int main(int argc, char* argv[]) {
	char Temp = '\0';

	cout << "+------------------------+" << endl;
	cout << "| 欢迎来到停车场管理系统 |" << endl;
	cout << "+------------------------+" << endl;

	Func Function;
	if (Function.Login() != 0) {
		return 1;
	}

	cout << "登陆成功，按回车键继续......" << endl;
	Temp = getchar();

	system("cls");
	cout << "输入 \"help\" 以显示指令集" << endl;
	Function.Help();
	while (Function.Statues() != 0);
	cout << "程序已退出" << endl;

	return 0;
}