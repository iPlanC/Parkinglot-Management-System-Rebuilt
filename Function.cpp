//预编译
#define Debug
#define realUserName		"PlanC"
#define realUserPassword	"password"
#define defaultParkingSpace 1

//引用
#include "included.h"

//全局变量
int runningHour = 0;
int sidewayPointer = 0;
int spacePointer = 0;
int totalSpace = defaultParkingSpace;
int VIPCounter = 0;
double costPerHour = 1.5;
double totalEarn = 0.0;
double VIPDiscount = 0.8;

using namespace std;
using namespace tinyxml2;

//结构体
struct parking_space {
	int time;
	int parkSerial;
	bool isVIP;
	char carSerial[6];
	double cost;
} parkingSpace;

struct parking_lot {
	struct parking_space parkingSpace[defaultParkingSpace];
} parkingLot;

struct sideway {
	struct parking_space parkingSpace[1000000];
} sideway;

struct vip {
	char carSerial[6];
} VIP;

struct vip_list {
	struct vip VIP[100];
} VIPList;

//配置变量函数
//类型：	int
//作用：	允许运行时改变程序参数
//返回值：	0 无错误
int Func::Config() {
	int i = 0;
	int select = 0;
	char carSerial[6] = { "\0" };
	char Temp = '\0';

	while (1) {
		system("cls");
		cout << "\t1.更改每小时停车费 $costPerHour = " << costPerHour << endl;
		cout << "\t2.添加车牌号至VIP列表 $VIPCounter = " << VIPCounter << endl;
		cout << "\t3.更改VIP折扣 $VIPDiscount = " << VIPDiscount << endl;
		cout << "\t4.更改停车场车位数量 $totalSpace = " << totalSpace << endl;
		cout << "\t0.停止更改" << endl;
		cout << "输入对应的序号以更改相应参数：";
		cin >> select;

		switch (select) {
		case 1:
			cout << "新的每小时停车费 > ";
			cin >> costPerHour;
			cout << "修改成功" << endl;
			break;
		case 2:
			cout << "新的VIP车牌 > ";
			cin >> VIPList.VIP[VIPCounter].carSerial;
			VIPCounter++;
			cout << "添加成功，下次光临时生效。" << endl;
			break;
		case 3:
			cout << "新的VIP折扣 > ";
			cin >> VIPDiscount;
			cout << "修改成功" << endl;
			break;
		case 4:
			cout << "新的车位数量 > ";
			cin >> totalSpace;
			cout << "修改成功";
			break;
		case 0:
			return 0;
		}
		Temp = getchar();
	}
	return 0;
}

//营业额函数
//类型：	int
//说明：	显示营业时长与营业额
//返回值：	0 无错误
int Func::Earn() {
	cout << "共计在 " << runningHour / 24 << " 天， " << runningHour % 24 << " 小时，收入 " << totalEarn << " rmb。" << endl;
	return 0;
}

//帮助函数
//类型：	int
//说明：	显示程序支持的所有命令
//返回值：	0 无错误
int Func::Help() {
	cout << endl;
	cout << "\t可用指令集" << endl;
	cout << "\t\tconfig  - 更改相关参数" << endl;
	cout << "\t\tcls     - 清除历史操作" << endl;
	cout << "\t\tearn    - 显示历史输入" << endl;
	cout << "\t\texit    - 退出此程序" << endl;
	cout << "\t\thelp    - 输出此列表" << endl;
	cout << "\t\tjump    - 将时间增加 \"n\" 小时" << endl;
	cout << "\t\tleft    - 登记指定的车牌号离库" << endl;
	cout << "\t\tmap     - 查看停车场状况" << endl;
	cout << "\t\tpark    - 新增入库车辆" << endl;
	cout << "\t\tPMSR    - 显示自述文字" << endl;
	cout << "\t\tsave    - 保存停车场状况" << endl;
	cout << endl;
	return 0;
}

//时间函数
//类型：	int
//说明：	跳过指定的时间 单位小时
//返回值：	0 无错误
int Func::Jump() {
	int i = 0;
	int hour = 0;
	
	cout << "请输入要跳过的时长：";
	cin >> hour;

	for (i = 0; i < spacePointer; i++) {
		parkingLot.parkingSpace[i].time = parkingLot.parkingSpace[i].time + hour;
		if (parkingLot.parkingSpace[i].isVIP) {
			parkingLot.parkingSpace[i].cost = parkingLot.parkingSpace[i].cost + hour * costPerHour * VIPDiscount;
		}
		else {
			parkingLot.parkingSpace[i].cost = parkingLot.parkingSpace[i].cost + hour * costPerHour;
		}
	}

	runningHour = runningHour + hour;
	cout << "已跳过 " << hour << " 小时" << endl;
	return 0;
}

//记出函数
//类型：	int
//说明：	登记相应的车牌号缴费离库
//返回值：	0 无错误
//			1 未找到
int Func::Leave() {
	int i = 0;
	int j = 0;
	int flag = 0;
	char serial[6] = { "\0" };

	cout << "请输入离库车牌号：";
	cin >> serial;

	for (; i <= spacePointer; i++) {
		if (strcmp(parkingLot.parkingSpace[i].carSerial, serial) == 0) {
			flag = 1;
			totalEarn = totalEarn + parkingLot.parkingSpace[i].cost;
			cout << "车牌号 " << parkingLot.parkingSpace[i].carSerial << " 已离库，需挪动 " << spacePointer - i - 1 << " 辆车" << endl;
			break;
		}
	}

	if (flag != 1) {
		cout << "未找到车牌号，请核对后重试。" << endl;
		return 1;
	}

	for (; i < spacePointer; i++) {
		strcpy_s(parkingLot.parkingSpace[i - 1].carSerial, parkingLot.parkingSpace[i].carSerial);
		parkingLot.parkingSpace[i - 1].time = parkingLot.parkingSpace[i].time;
		parkingLot.parkingSpace[i - 1].cost = parkingLot.parkingSpace[i].cost;
	}
	if (sidewayPointer != 0) {
		strcpy_s(parkingLot.parkingSpace[totalSpace - 1].carSerial, sideway.parkingSpace[0].carSerial);
		parkingLot.parkingSpace[totalSpace - 1].parkSerial = totalSpace;
		parkingLot.parkingSpace[totalSpace - 1].time = 0;
		parkingLot.parkingSpace[totalSpace - 1].cost = 0;
		for (j = 0; j < VIPCounter; j++) {
			if (strcmp(parkingLot.parkingSpace[spacePointer].carSerial, VIPList.VIP[i].carSerial) == 0) {
				parkingLot.parkingSpace[spacePointer].isVIP = true;
			}
			else {
				parkingLot.parkingSpace[spacePointer].isVIP = false;
			}
		}
		for (j = 0; j < sidewayPointer; j++) {
			strcpy_s(sideway.parkingSpace[j].carSerial, sideway.parkingSpace[j + 1].carSerial);
		}
		sidewayPointer--;
	}
	else {
		spacePointer--;
	}
	return 0;
}

//载入函数
//类型：	int
//说明：	重载保存过的记录
//返回值：	0 无错误
//			1 未找到文件
int Func::Load() {
	return 0;
}

//登录函数
//类型：	int
//说明：	验证登录过程
//返回值：	0 无错误
//			1 用户名找不到
//			2 密码错误
int Func::Login() {
	int i = 0;
	int retryTimes = 3;
	char inputUserName[10] = { "\0" };
	char inputUserPassword[15] = { "\0" };

#ifdef Release
	while (retryTimes--) {
		cout << "请输入用户名：";
		cin >> inputUserName;
		if (strcmp(inputUserName, realUserName)) {
			if (retryTimes == 0) {
				cout << endl << "三次错误，程序退出。" << endl;
				return 1;
			}
			cout << "输入错误，请检查后重试。" << endl;
			continue;
		}
		else {
			break;
		}
	}

	while (retryTimes--) {
		cout << "请输入密码：";
		cin >> inputUserPassword;
		if (strcmp(inputUserPassword, realUserPassword)) {
			if (retryTimes == 0) {
				cout << endl << "三次错误，程序退出。" << endl;
				return 2;
			}
			cout << "输入错误，请检查后重试。" << endl;
			continue;
		}
		else {
			break;
		}
	}
#endif
	return 0;
}

//显示状态函数
//类型：	int
//说明：	显示停车场状况函数
//返回值;	0 无错误
int Func::Map() {
	int i = 0;

	cout << "共停了 " << spacePointer << " 辆车" << endl;
	cout << "车 位\t车 牌\t时 间\t缴 费\t贵 宾" << endl;
	
	for (i = 0; i < spacePointer; i++) {
		cout << parkingLot.parkingSpace[i].parkSerial << "\t" << parkingLot.parkingSpace[i].carSerial << "\t" << parkingLot.parkingSpace[i].time << "\t" << parkingLot.parkingSpace[i].cost << "\t";
		if (parkingLot.parkingSpace[i].isVIP) {
			cout << "  *  " << endl;
		}
		else {
			cout << endl;
		}
	}

	cout << endl << "便道中共有 " << sidewayPointer << " 辆车在等待。" << endl;
	return 0;
}

//入库函数
//类型：	int
//说明：	新增入库车辆
//返回值：	0 无错误
int Func::Park() {
	int i = 0;
	char serial[6] = { "\0" };

	cout << "请输入入库车牌号：";
	cin >> serial;
	
	if (spacePointer < totalSpace) {
		strcpy_s(parkingLot.parkingSpace[spacePointer].carSerial, serial);
		parkingLot.parkingSpace[spacePointer].time = 0;
		for (i = 0; i < VIPCounter; i++) {
			if (strcmp(parkingLot.parkingSpace[spacePointer].carSerial, VIPList.VIP[i].carSerial) == 0) {
				parkingLot.parkingSpace[spacePointer].isVIP = true;
			}
			else {
				parkingLot.parkingSpace[spacePointer].isVIP = false;
			}
		}
		parkingLot.parkingSpace[spacePointer].parkSerial = spacePointer + 1;
		cout << "车牌号 " << serial << " 已入库" << endl;
		spacePointer++;
	}
	else {
		strcpy_s(sideway.parkingSpace[sidewayPointer].carSerial, serial);
		cout << "车库已满，车牌号 " << sideway.parkingSpace[sidewayPointer].carSerial << " 已停放至便道，前方共有 " << sidewayPointer << " 辆车。" << endl;
		sidewayPointer++;
	}
	return 0;
}

//保存函数
//类型：	int
//说明：	保存停车场函数
//返回值：	0 无错误
//			1 创建文件发生错误
int Func::Save() {
	int i = 0;
	XmlOperate Xml;
	
	Xml.CreateXML();
	for (i = 0; i < spacePointer; i++) {
		Xml.insertData_Parkinglot(parkingLot.parkingSpace[i].time, parkingLot.parkingSpace[i].parkSerial, parkingLot.parkingSpace[i].isVIP, parkingLot.parkingSpace[i].carSerial, parkingLot.parkingSpace[i].cost);
	}

	for (i = 0; i < sidewayPointer; i++) {
		Xml.insertData_Sideway(sideway.parkingSpace[i].carSerial);
	}
	return 0;
}

//解释函数
//类型：	int
//说明：	根据输入的命令调用相应的函数
//返回值：	0 退出
//			1 调用 config() 函数
//			2 调用 system("cls") 函数
//			3 调用 earn() 函数
//			4 调用 help() 函数
//			5 调用 jump() 函数
//			6 调用 left() 函数
//			7 调用 map() 函数
//			8 调用 park() 函数
//			9 调用 save() 函数
int Func::Statues() {
	int i = 0;
	char command[20] = { "\0" };

	cout << "PMSR >>> ";
	cin >> command;

	if (strcmp(command, "exit") == 0) {
		return 0;
	}

	if (strcmp(command, "config") == 0) {
		Config();
		return 1;
	}

	if (strcmp(command, "cls") == 0) {
		system("cls");
		return 2;
	}

	if (strcmp(command, "earn") == 0) {
		Earn();
		return 3;
	}

	if (strcmp(command, "help") == 0) {
		Help();
		return 4;
	}

	if (strcmp(command, "jump") == 0) {
		Jump();
		return 5;
	}

	if (strcmp(command, "left") == 0) {
		Leave();
		return 6;
	}

	if (strcmp(command, "map") == 0) {
		Map();
		return 7;
	}

	if (strcmp(command, "park") == 0) {
		Park();
		return 8;
	}

	if (strcmp(command, "save") == 0) {
		Save();
		return 9;
	}

	return -1;
}