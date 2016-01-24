
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include<cstdio>
#include<iostream>
#include<time.h>
#include<vector>
#include <windows.h>  
using namespace std;

//#define CLOCKS_PER_SEC ((clock_t)1000)

//#define MAX 2000000

// 微秒的 用法
//http://blog.csdn.net/morewindows/article/details/6854764

const int maxIndex = 2000000;		//  其实要减1


int getData(const vector<int> &er, const int &index)
{
	return er[index];
}

void for200times() 
{
	clock_t start, end;
	vector<int> vecv1(maxIndex, 20);
	srand(time(nullptr));


	// 微秒计时
	LARGE_INTEGER  large_interger;  
	double dff;  
	__int64  c1, c2;  
	QueryPerformanceFrequency(&large_interger);  
	dff = large_interger.QuadPart;  

	// 毫秒计时
	start = clock();
	
	QueryPerformanceCounter(&large_interger);  
	c1 = large_interger.QuadPart;  
	
	//int index = 0;
	for (int i = 0; i < 200; i++) {
		int index = rand()%maxIndex;
		getData(vecv1, index);
	}

	// 微秒计时
	QueryPerformanceCounter(&large_interger);  
	c2 = large_interger.QuadPart; 

	// 毫秒计时
	end = clock();


	cout << "Run time: " << (double)(c2 - c1)*1000*1000 / dff << "Micro-second" << endl; 
	cout << "Run time: " << (double)(end - start) << "MS" << endl; 

}