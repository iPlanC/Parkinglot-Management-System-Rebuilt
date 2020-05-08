//引用
#include "included.h"

using namespace std;
using namespace tinyxml2;

//创建XML文件函数
//类型：	int
//作用：	保存当前状况为XML文档
//返回值：	0 无错误
int XmlOperate::CreateXML() {
	const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
	XMLDocument doc;
	doc.Parse(declaration);

	XMLElement* root = doc.NewElement("Parkinglot");
	doc.InsertEndChild(root);

	return doc.SaveFile(".\\save.xml");
}

//插入数据函数
//类型：	int
//作用：	插入数据至XML文档
//返回值：	0 无错误
//			x 读取有误
int XmlOperate::insertData_Parkinglot(int time, int parkSerial, bool isVIP, char* carserial, double cost) {
	char Buffer[100];
	XMLDocument doc;
	int res = doc.LoadFile(".\\save.xml");
	if (res != 0) {
		cout << "载入 XML 文档发生错误 请检查" << endl;
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

//插入数据函数
//类型：	int
//作用：	插入数据至XML文档
//返回值：	0 无错误
//			x 读取有误
int XmlOperate::insertData_Sideway(char* carserial) {
	XMLDocument doc;
	int res = doc.LoadFile(".\\save.xml");
	if (res != 0) {
		cout << "载入 XML 文档发生错误 请检查" << endl;
		return res;
	}

	XMLElement* root = doc.RootElement();
	XMLElement* carNode = doc.NewElement("Sideway");
	carNode->SetAttribute("carserial", carserial);
	root->InsertEndChild(carNode);

	return doc.SaveFile(".\\save.xml");
}
