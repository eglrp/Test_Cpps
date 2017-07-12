// 09_类型size.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <iostream>
using namespace std;

struct A {
	A(int i):r1(i) {}
	~A() {}
	int m1;
	int m2;
	int &r1; //引用类型和其引用的类型占用一致
	//char m1;
	//char m2;
	//char r1;
};
struct B :A {
	B(int i):A(i) {}
	~B() {}
	int m1;
	char m2;
	static char m3;
	void printParentM() { cout << A::m1 << endl; cout << A::m2 << endl; } //在类内访问父类的同名成员
};
struct C {
	C() {}
	virtual~C() {}
	int m1;
	short m2;
};

int main()
{

	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;

	A a(10);
	B b(10);
	C c;
	cout << b.m1 << endl; //同名的成员变量相互独立，而同名的成员函数会发生覆盖。
	cout << b.m2 << endl;
	cout << b.A::m1 << endl; //在类外面访问父类的同名成员

//		答案解析：类的大小只与成员变量（非static数据成员变量）和虚函数指针有关，还要考虑到对齐. 
// 		那么类A的大小是8个字节；
// 		类B继承类A，在类A的8个字节基础上，再加上B自己的大小8字节，所以类B大小是16个字节；
// 		类C是4个字节 + 4个字节（考虑对齐） + 4个字节（指向虚析构函数的指针） = 12个字节

	system("pause");
	return 0;
}
