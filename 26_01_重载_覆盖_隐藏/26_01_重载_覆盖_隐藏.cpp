// 26_01_重载_覆盖_隐藏.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;


// 1.重载:(同一作用域，不同参数)
// (1)相同范围(同一个类或者同一作用域内)
// (2)函数同名，参数不同(必须)，返回值任意，virtual任意

#pragma region 来自newcoder
//重载的概念是：
//方法名称相同，参数个数、次序、类型不同
//因此重载对返回值没有要求，可以相同，也可以不同
//但是如果参数的个数、类型、次序都相同，方法名也相同，仅返回值不同，则无法构成重载 
//特殊情况:	(1)参数const和非const要构成重载的话必须是底层指针(也就是说const必须修饰指针指向的对象而非指针本身)才行
//			(2)成员函数，const版本和非const版本进行重载，其实const版本就是 const T* const this，因此是底层指针了，所以构成了重载
#pragma endregion


// 2.覆盖(覆写)（就是通常的virtual函数被继承，必须整个签名一致）
// (1)不同范围(基类与派生类)
// (2)函数同名，参数相同，返回值相同（可以不同，Morexxx上7.1提到,
// 但是在vs里面编译器会说，类型不同必须可协变，就是有继承关系的指针之间可以不同,用于虚拟拷贝构造函数）
// ，有virtual

// 3.隐藏（子类有一个跟父类签名不同的同名函数，或者签名相同但父类不是virtual，就构成隐藏）
// (1)不同范围(基类与派生类)
// (2)函数同名，参数不同，返回值任意，virtual任意，基类函数被隐藏(与重载的区别在于作用域)
// (3)函数同名，参数相同，返回值任意，基类没有virtual，基类函数被隐藏(与覆盖的区别在于基类函数是否是virtual)


//总结:其实就如EffectiveC++中所言，就是一个作用域的问题，
// 函数调用的时候会先搜索当前local作用域，再当前类，再当前namespace,再global
// 所以，子类里面只要有一个同名函数，便会屏蔽掉基类里面的同名函数，无论参数和返回值
// 如果要在子类里面使用基类的被屏蔽(覆盖或者是隐藏)的函数，可以使用using Base::function()来实现

class Base{
public:
	void mf1() {}; //(1)
	void mf1(int) {}; //(2)
	int mf1(double) {}; //(3) ,1,2,3之间是重载关系,注意，参数必须不同，返回值任意


	virtual void mf2() {};//(4)

	virtual void mf3() { cout << "Base::mf3()" << endl; };//(5)


};

class Derived:public Base{

public:
	void mf2() {};//(6)	(4),(6)是覆盖,返回值必须相同,若参数不同,则是隐藏
	int mf2(int) {}; //(7) 隐藏了父类的mf2

	void mf3(int) {}; //(8) 隐藏了父类的mf3
	//using Base::mf3; //使父类被隐藏了的函数可以被调用

};

int main()
{
	Derived d;
	//d.Base::mf3(); //虽然被隐藏了，但是还是可以调用的(就算没声明using Base::mf3)
	//d.mf3(); //有声明using Base::mf3的情况下可以调用,否则会报错

	system("pause");
	return 0;
}

