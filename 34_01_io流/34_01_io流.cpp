// 34_01_io流.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>  //包含geiline(istream,string)
#include <stdio.h>
#include <cstring>
using namespace std;

int main()
{

	////string的读入，两种:>>和getline()
	//{
	//	string temp;
	//	cin >> temp; //cin作为输入的话，不会接受空白字符
	//	cout << "输入的是" << temp << endl;
	//	getline(cin, temp); //可以包含空白字符，以回车结束

	//}
	//
	////get,put函数
	//{
	//	char arr[7];
	//	//遇到EOF(CTRL+Z)都会结束
	//	//cin.get(arr,6); //指定读入最大6个字符
	//	cin.get(arr, 6,'\n'); //指定读入最大6个字符或者遇到'\n'结束,默认也是遇到'\n'结束

	//	cout << arr << endl; 

	//}


	//char c[10];
	//cin.getline(&c[0], 5, 'g'); //指定接受5-1个字符，因为最后一个是\0

	//
	
	{
		char str[20];
		//gets(str); //C++11中被删除了，用fgets替代
		char * str1 = fgets(str, 200, stdin); //gets相比于scanf的好处是到行末才会停止，因此可以接收空白字符
		//fgets的话会添加新换行符在末尾，gets不会
		std::cout << str1 << std::endl;
	}
	

	system("pause");
	return 0;
}

