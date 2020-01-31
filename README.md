# 开发笔记

## 使用说明

### 通过输入命令来使用该工具

```
config  - 更改相关参数
cls     - 清除历史操作
earn    - 显示历史输入
exit    - 退出此程序
help    - 输出此列表
jump    - 将时间增加 "n" 小时
left    - 登记指定的车牌号离库
map     - 查看停车场状况
park    - 新增入库车辆
PMSR    - 显示自述文字
save    - 保存停车场状况
```

### 通过随机托管使用该工具（开发中）

```
automata - 随机托管运行管理系统
```



## 源码文件说明

| 序号 | 文件名                                  | 说明           |
| ---- | --------------------------------------- | -------------- |
| 1    | Function.cpp                            | 函数体功能源码 |
| 2    | Function.h                              | 函数体头文件   |
| 3    | included.h                              | 引用头文件目录 |
| 4    | Parkinglot Management System Rebult.cpp | 主程序源码     |
| 5    | tinyxml2.cpp                            | Xml功能源码    |
| 6    | tinyxml2.h                              | Xml头文件      |

## 参数及变量

### 函数及说明

| 序号 | 函数名                  | 作用                         | 用户调用 | 位置           |
| ---- | ----------------------- | ---------------------------- | -------- | -------------- |
| 1    | Config()                | 允许运行时改变程序参数       | y        | Function.cpp   |
| 2    | Earn()                  | 显示营业时长与营业额         | y        | Function.cpp   |
| 3    | Help()                  | 显示程序支持的所有命令       | y        | Function.cpp   |
| 4    | Jump()                  | 跳过指定的时间 单位小时      | y        | Function.cpp   |
| 5    | Leave()                 | 登记相应的车牌号缴费离库     | y        | Function.cpp   |
| 6    | Load()                  | 重载保存过的记录             | n        | Function.cpp   |
| 7    | Login()                 | 验证登录过程                 | n        | Function.cpp   |
| 8    | Map()                   | 显示停车场状况函数           | y        | Function.cpp   |
| 9    | Park()                  | 新增入库车辆                 | y        | Function.cpp   |
| 10   | Save()                  | 保存停车场函数               | y        | Function.cpp   |
| 11   | Statues()               | 根据输入的命令调用相应的函数 | n        | Function.cpp   |
| 12   | CreateXML()             | 创建XML文档函数              | n        | xmlOperate.cpp |
| 13   | insertData_Parkinglot() | 插入数据函数                 | n        | xmlOperate.cpp |
| 14   | insertData_Sideway()    | 插入数据函数                 | n        | xmlOperate.cpp |

```c++
int insertData_Parkinglot(int time, int parkSerial, bool isVIP, char* carserial, double cost);
//time			停车时间
//parkSerial		停车位
//isVIP			是否VIP
//carserial		车牌号
//cost			应缴金额
int insertData_Sideway(char* carserial);
//carserial		车牌号
```
### 停车场车位结构体

|类型|大小|类型|描述|
|:---|:---|:---|:---|
|time|4|int|进入停车场的有效时间|
|parkSerial|4|int|停车序号|
|isVIP|1|byte|是否VIP客户|
|carserial|6|char[6]|车牌号|
|cost|8| double  |花费|

**示例**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Parkinglot>
	<car carserial="11111">
		<time>3</time>
		<parkserial>1</parkserial>
		<isVIP>0</isVIP>
		<cost>4.5</cost>
	</car>
	<Sideway carserial="22222"/>
	<Sideway carserial="33333"/>
</Parkinglot>
```

