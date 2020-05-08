//����
#include "included.h"

using namespace std;
using namespace tinyxml2;

//����XML�ļ�����
//���ͣ�	int
//���ã�	���浱ǰ״��ΪXML�ĵ�
//����ֵ��	0 �޴���
int XmlOperate::CreateXML() {
	const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
	XMLDocument doc;
	doc.Parse(declaration);

	XMLElement* root = doc.NewElement("Parkinglot");
	doc.InsertEndChild(root);

	return doc.SaveFile(".\\save.xml");
}

//�������ݺ���
//���ͣ�	int
//���ã�	����������XML�ĵ�
//����ֵ��	0 �޴���
//			x ��ȡ����
int XmlOperate::insertData_Parkinglot(int time, int parkSerial, bool isVIP, char* carserial, double cost) {
	char Buffer[100];
	XMLDocument doc;
	int res = doc.LoadFile(".\\save.xml");
	if (res != 0) {
		cout << "���� XML �ĵ��������� ����" << endl;
		return res;
	}

	XMLElement* root = doc.RootElement();
	XMLElement* carNode = doc.NewElement("car");
	carNode->SetAttribute("carserial", carserial);

		sprintf_s(Buffer, "%d", time);
		XMLElement* timeNode = doc.NewElement("time");
		timeNode->InsertEndChild(doc.NewText(Buffer));
		carNode->InsertEndChild(timeNode);

		sprintf_s(Buffer, "%d", parkSerial);
		XMLElement* parkSerialNode = doc.NewElement("parkserial");
		parkSerialNode->InsertEndChild(doc.NewText(Buffer));
		carNode->InsertEndChild(parkSerialNode);

		sprintf_s(Buffer, "%d", isVIP);
		XMLElement* isVIPNode = doc.NewElement("isVIP");
		isVIPNode->InsertEndChild(doc.NewText(Buffer));
		carNode->InsertEndChild(isVIPNode);

		sprintf_s(Buffer, "%.2f", cost);
		XMLElement* costNode = doc.NewElement("cost");
		costNode->InsertEndChild(doc.NewText(Buffer));
		carNode->InsertEndChild(costNode);

	root->InsertEndChild(carNode);

	return doc.SaveFile(".\\save.xml");
}

//�������ݺ���
//���ͣ�	int
//���ã�	����������XML�ĵ�
//����ֵ��	0 �޴���
//			x ��ȡ����
int XmlOperate::insertData_Sideway(char* carserial) {
	XMLDocument doc;
	int res = doc.LoadFile(".\\save.xml");
	if (res != 0) {
		cout << "���� XML �ĵ��������� ����" << endl;
		return res;
	}

	XMLElement* root = doc.RootElement();
	XMLElement* carNode = doc.NewElement("Sideway");
	carNode->SetAttribute("carserial", carserial);
	root->InsertEndChild(carNode);

	return doc.SaveFile(".\\save.xml");
}
