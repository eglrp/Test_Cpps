// 22_0_抽象类和纯虚函数.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class A
{
public:
	virtual void printInfo() = 0;
	void printName() { cout << name << endl; }
	string name = "yxp";
};

class B:public A
{
public:
	B() { this->name = "yxp,B"; }
	void printInfo() { cout << this->name << endl; }
	
};



int main()
{

	//A a; //含有纯虚函数的类叫做抽象类，不能声明抽象类的对象，不能用于返回值和参数

	//只能声明指针，用来指向派生类，实现多态

	A *a = new B;
	a->printInfo();

	system("pause");

	return 0;
}
