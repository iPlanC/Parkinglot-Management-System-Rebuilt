//Ԥ����
#define Debug
#define realUserName		"PlanC"
#define realUserPassword	"password"
#define defaultParkingSpace 1

//����
#include "included.h"

//ȫ�ֱ���
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

//�ṹ��
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

//���ñ�������
//���ͣ�	int
//���ã�	��������ʱ�ı�������
//����ֵ��	0 �޴���
int Func::Config() {
	int i = 0;
	int select = 0;
	char carSerial[6] = { "\0" };
	char Temp = '\0';

	while (1) {
		system("cls");
		cout << "\t1.����ÿСʱͣ���� $costPerHour = " << costPerHour << endl;
		cout << "\t2.��ӳ��ƺ���VIP�б� $VIPCounter = " << VIPCounter << endl;
		cout << "\t3.����VIP�ۿ� $VIPDiscount = " << VIPDiscount << endl;
		cout << "\t4.����ͣ������λ���� $totalSpace = " << totalSpace << endl;
		cout << "\t0.ֹͣ����" << endl;
		cout << "�����Ӧ������Ը�����Ӧ������";
		cin >> select;

		switch (select) {
		case 1:
			cout << "�µ�ÿСʱͣ���� > ";
			cin >> costPerHour;
			cout << "�޸ĳɹ�" << endl;
			break;
		case 2:
			cout << "�µ�VIP���� > ";
			cin >> VIPList.VIP[VIPCounter].carSerial;
			VIPCounter++;
			cout << "��ӳɹ����´ι���ʱ��Ч��" << endl;
			break;
		case 3:
			cout << "�µ�VIP�ۿ� > ";
			cin >> VIPDiscount;
			cout << "�޸ĳɹ�" << endl;
			break;
		case 4:
			cout << "�µĳ�λ���� > ";
			cin >> totalSpace;
			cout << "�޸ĳɹ�";
			break;
		case 0:
			return 0;
		}
		Temp = getchar();
	}
	return 0;
}

//Ӫҵ���
//���ͣ�	int
//˵����	��ʾӪҵʱ����Ӫҵ��
//����ֵ��	0 �޴���
int Func::Earn() {
	cout << "������ " << runningHour / 24 << " �죬 " << runningHour % 24 << " Сʱ������ " << totalEarn << " rmb��" << endl;
	return 0;
}

//��������
//���ͣ�	int
//˵����	��ʾ����֧�ֵ���������
//����ֵ��	0 �޴���
int Func::Help() {
	cout << endl;
	cout << "\t����ָ�" << endl;
	cout << "\t\tconfig  - ������ز���" << endl;
	cout << "\t\tcls     - �����ʷ����" << endl;
	cout << "\t\tearn    - ��ʾ��ʷ����" << endl;
	cout << "\t\texit    - �˳��˳���" << endl;
	cout << "\t\thelp    - ������б�" << endl;
	cout << "\t\tjump    - ��ʱ������ \"n\" Сʱ" << endl;
	cout << "\t\tleft    - �Ǽ�ָ���ĳ��ƺ����" << endl;
	cout << "\t\tmap     - �鿴ͣ����״��" << endl;
	cout << "\t\tpark    - ������⳵��" << endl;
	cout << "\t\tPMSR    - ��ʾ��������" << endl;
	cout << "\t\tsave    - ����ͣ����״��" << endl;
	cout << endl;
	return 0;
}

//ʱ�亯��
//���ͣ�	int
//˵����	����ָ����ʱ�� ��λСʱ
//����ֵ��	0 �޴���
int Func::Jump() {
	int i = 0;
	int hour = 0;
	
	cout << "������Ҫ������ʱ����";
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
	cout << "������ " << hour << " Сʱ" << endl;
	return 0;
}

//�ǳ�����
//���ͣ�	int
//˵����	�Ǽ���Ӧ�ĳ��ƺŽɷ����
//����ֵ��	0 �޴���
//			1 δ�ҵ�
int Func::Leave() {
	int i = 0;
	int j = 0;
	int flag = 0;
	char serial[6] = { "\0" };

	cout << "��������⳵�ƺţ�";
	cin >> serial;

	for (; i <= spacePointer; i++) {
		if (strcmp(parkingLot.parkingSpace[i].carSerial, serial) == 0) {
			flag = 1;
			totalEarn = totalEarn + parkingLot.parkingSpace[i].cost;
			cout << "���ƺ� " << parkingLot.parkingSpace[i].carSerial << " ����⣬��Ų�� " << spacePointer - i - 1 << " ����" << endl;
			break;
		}
	}

	if (flag != 1) {
		cout << "δ�ҵ����ƺţ���˶Ժ����ԡ�" << endl;
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

//���뺯��
//���ͣ�	int
//˵����	���ر�����ļ�¼
//����ֵ��	0 �޴���
//			1 δ�ҵ��ļ�
int Func::Load() {
	return 0;
}

//��¼����
//���ͣ�	int
//˵����	��֤��¼����
//����ֵ��	0 �޴���
//			1 �û����Ҳ���
//			2 �������
int Func::Login() {
	int i = 0;
	int retryTimes = 3;
	char inputUserName[10] = { "\0" };
	char inputUserPassword[15] = { "\0" };

#ifdef Release
	while (retryTimes--) {
		cout << "�������û�����";
		cin >> inputUserName;
		if (strcmp(inputUserName, realUserName)) {
			if (retryTimes == 0) {
				cout << endl << "���δ��󣬳����˳���" << endl;
				return 1;
			}
			cout << "���������������ԡ�" << endl;
			continue;
		}
		else {
			break;
		}
	}

	while (retryTimes--) {
		cout << "���������룺";
		cin >> inputUserPassword;
		if (strcmp(inputUserPassword, realUserPassword)) {
			if (retryTimes == 0) {
				cout << endl << "���δ��󣬳����˳���" << endl;
				return 2;
			}
			cout << "���������������ԡ�" << endl;
			continue;
		}
		else {
			break;
		}
	}
#endif
	return 0;
}

//��ʾ״̬����
//���ͣ�	int
//˵����	��ʾͣ����״������
//����ֵ;	0 �޴���
int Func::Map() {
	int i = 0;

	cout << "��ͣ�� " << spacePointer << " ����" << endl;
	cout << "�� λ\t�� ��\tʱ ��\t�� ��\t�� ��" << endl;
	
	for (i = 0; i < spacePointer; i++) {
		cout << parkingLot.parkingSpace[i].parkSerial << "\t" << parkingLot.parkingSpace[i].carSerial << "\t" << parkingLot.parkingSpace[i].time << "\t" << parkingLot.parkingSpace[i].cost << "\t";
		if (parkingLot.parkingSpace[i].isVIP) {
			cout << "  *  " << endl;
		}
		else {
			cout << endl;
		}
	}

	cout << endl << "����й��� " << sidewayPointer << " �����ڵȴ���" << endl;
	return 0;
}

//��⺯��
//���ͣ�	int
//˵����	������⳵��
//����ֵ��	0 �޴���
int Func::Park() {
	int i = 0;
	char serial[6] = { "\0" };

	cout << "��������⳵�ƺţ�";
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
		cout << "���ƺ� " << serial << " �����" << endl;
		spacePointer++;
	}
	else {
		strcpy_s(sideway.parkingSpace[sidewayPointer].carSerial, serial);
		cout << "�������������ƺ� " << sideway.parkingSpace[sidewayPointer].carSerial << " ��ͣ���������ǰ������ " << sidewayPointer << " ������" << endl;
		sidewayPointer++;
	}
	return 0;
}

//���溯��
//���ͣ�	int
//˵����	����ͣ��������
//����ֵ��	0 �޴���
//			1 �����ļ���������
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

//���ͺ���
//���ͣ�	int
//˵����	������������������Ӧ�ĺ���
//����ֵ��	0 �˳�
//			1 ���� config() ����
//			2 ���� system("cls") ����
//			3 ���� earn() ����
//			4 ���� help() ����
//			5 ���� jump() ����
//			6 ���� left() ����
//			7 ���� map() ����
//			8 ���� park() ����
//			9 ���� save() ����
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