

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{

	//小数点后的位权应该是2的负数次方才没有误差，其它的情况都有误差。

	double d1 = 0.1;

	double d2 = pow(10, 30);
	double d3 = 0.5;
	double d4 = 0.25;
	//double d41 = 0.26;
	double d5 = 0.125;
	double d6 = 0.111;
	cout << d1 << endl; //从调试窗口可以看到是0.10000000000000001
	if (d1 == 0.1)
	{
		cout << "d1 == 0.1" << endl; //但是这里仍然会执行，说明==号内部是做了处理的
	}
	if (d1 == 0.10000000000000001)
	{
		cout << "d1 == 0.10000000000000001" << endl; //执行
	}
	if (d1 == 0.1000000000001)
	{
		cout << "d1 == 0.1000000000001" << endl; //不会执行，具体是怎么个处理法？
	}
	if (d1 == 0.100000000000000001)
	{
		cout << "d1 == 0.100000000000000001" << endl; //执行
	}

	
	cout << d2 << endl;
	system("pause");
	return 0;
}
