// Test1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FaceUI.h"
using namespace Face;
using namespace std;
#pragma comment(lib, "FaceUI.lib")

void Test()
{
	WString str = L"chencheng";
	std::cout << "���ȣ�" << str.Length() << endl;
	const wchar_t* ch = str.Buffer();
	int i = 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test();
	return 0;
}

