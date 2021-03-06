// 54_02_placement_new.cpp : 定义控制台应用程序的入口点。
//
//
//Placement new的含义
//
//placement new 是重载operator new 的一个标准、全局的版本
//它"不能够被自定义的版本代替"（不像普通版本的operator new和operator delete能够被替换）。
//
//void *operator new(size_t, void * p) throw() { return p; }
//
//placement new的执行忽略了size_t参数，只返还第二个参数。
//其结果是允许用户把一个对象放到一个特定的地方，达到调用构造函数的效果。
//和其他普通的new不同的是，它在括号里多了另外一个参数。比如：
//
//Widget * p = new Widget;                    //ordinary new
//
//pi = new (ptr) int; pi = new (ptr) int;     //placement new
//
//括号里的参数ptr是一个指针，它指向一个内存缓冲器，placement new将在这个缓冲器上分配一个对象。
//Placement new的返回值是这个被构造对象的地址(比如括号中的传递参数)。
//placement new主要适用于：在对时间要求非常高的应用程序中，因为这些程序分配的时间是确定的；
//长时间运行而不被打断的程序；以及执行一个垃圾收集器(garbage collector)。

//////////////////////////////////////////////////////////////////////////
//三者对比
//new 、operator new 和 placement new 区别
//
//（1）new ：不能被重载，其行为总是一致的。它先调用operator new分配内存，然后调用构造函数初始化那段内存。
//
//new 操作符的执行过程：
//1. 调用operator new分配内存 ；
//2. 调用构造函数生成类对象；
//3. 返回相应指针。
//
//（2）operator new：要实现不同的内存分配行为，应该重载operator new，而不是new。
//
//operator new就像operator + 一样，是可以重载的。如果类中没有重载operator new，
//那么调用的就是全局的::operator new来完成堆的分配。
//同理，operator new[]、operator delete、operator delete[]也是可以重载的。
//
//（3）placement new：只是operator new重载的一个版本。
//它并不分配内存，只是返回指向已经分配好的某段内存的一个指针。因此不能删除它，但需要调用对象的析构函数。
//
//如果你想在已经分配的内存中创建一个对象，使用new是行不通的。
//也就是说placement new允许你在一个已经分配好的内存中（栈或者堆中）构造一个新的对象。
//原型中void* p实际上就是指向一个已经分配好的内存缓冲区的的首地址。
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

//Placement new使用步骤
//
//在很多情况下，placement new的使用方法和其他普通的new有所不同。这里提供了它的使用步骤。
//
//第一步  缓存提前分配
//
//有三种方式：
//
//1.为了保证通过placement new使用的缓存区的memory alignment(内存队列)正确准备，使用普通的new来分配它：在堆上进行分配
//class Task;
//char * buff = new[sizeof(Task)]; //分配内存
//(请注意auto或者static内存并非都正确地为每一个对象类型排列，所以，你将不能以placement new使用它们。)
//
//2.在栈上进行分配
//class Task;
//char buf[N * sizeof(Task)]; //分配内存
//
//3.还有一种方式，就是直接通过地址来使用。(必须是有意义的地址)
//void* buf = reinterpret_cast<void*> (0xF00F);
//
//第二步：对象的分配
//
//在刚才已分配的缓存区调用placement new来构造一个对象。
//Task *ptask = new (buf) Task
//
//第三步：使用
//
//按照普通方式使用分配的对象：
//
//ptask->memberfunction();
//
//ptask->member;
//
////...
//
//第四步：对象的析构
//
//一旦你使用完这个对象，你必须调用它的析构函数来毁灭它。按照下面的方式调用析构函数：
//ptask->~Task(); //调用外在的析构函数
//
//第五步：释放
//
//你可以反复利用缓存并给它分配一个新的对象（重复步骤2，3，4）如果你不打算再次使用这个缓存，你可以象这样释放它：delete[] buf;
//
//跳过任何步骤就可能导致运行时间的崩溃，内存泄露，以及其它的意想不到的情况。如果你确实需要使用placement new，请认真遵循以上的步骤。

//////////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include <iostream>
using namespace std;

class X
{
public:
	X() { cout << "constructor of X" << endl; }
	~X() { cout << "destructor of X" << endl; }

	void SetNum(int n)
	{
		num = n;
	}

	int GetNum()
	{
		return num;
	}

private:
	int num;
};

int main()
{
	char* buf = new char[sizeof(X)]; //分配内存，但是没有调用构造函数
	X *px = new(buf) X; //调用placement new 执行构造函数
	px->SetNum(10); //使用对象
	cout << px->GetNum() << endl;
	px->~X(); //显示析构
	//delete[]buf; //清除缓存
	operator delete[] (buf); //个人感觉应该这意图更明确吧，operator delete[] 只删除内存
	
	//例子2
	{
		X* p = (X*)::operator new(sizeof(X)); //分配  

		new(p) X(); //构造  

		p->~X();   //析构  

		::operator delete(p); //释放

	}
	
	return 0;
}
