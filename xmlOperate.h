#pragma once
#ifndef XMLOPERATE
#define XMLOPERATE

class XmlOperate {
public:
	int CreateXML();
	int insertData_Parkinglot(int time, int parkSerial, bool isVIP, char* carserial, double cost);
	int insertData_Sideway(char* carserial);
};

#endif