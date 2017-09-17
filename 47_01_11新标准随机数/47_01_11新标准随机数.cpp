// 47_01_11新标准随机数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <random>
#include <iostream>
using namespace std;

int main()
{
#pragma region 例子1,就和以前的rand差不多
	//std::default_random_engine e;

	//for (size_t i = 0; i < 10; i++) {
	//	cout << e() << endl;
	//}
	//默认情况下，引擎产生的随机数范围在default_randm_engine::min()和default_random_engine::max()之间。
#pragma endregion

#pragma region 例2:产生5-20的均匀分布
	//std::default_random_engine e;
	//std::uniform_int_distribution<int> u(5, 20); //注意是int,double会报错
	////int的也可以产生unsigned类型的
	//std::uniform_real_distribution<double> u_d(2.0, 30.0);
	//for (size_t i = 0; i < 10; i++) {
	//	//cout << u(e) << endl;   //注意,传递的是e对象
	//	cout << u_d(e) << endl;
	//}
#pragma endregion


#pragma region gamma分步
	std::default_random_engine e;
	std::gamma_distribution<> u(1.0, 2.0);
	for (size_t i = 0; i < 10; i++) {
		cout << u(e) << endl;   //注意,传递的是e对象
	}
#pragma endregion



	system("pause");
    return 0;
}

