// DLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"


#define DLL_API extern "C" _declspec(dllexport)

#include "ShareDLL.h"


// �����ݶ�������֡�
#pragma data_seg("SharedDataInDll")				
int data[80][80][40] = {0};
#pragma data_seg()

//���ﻹ��Ҫ�������������� SharedDataInDll ���ݶ�Ϊ�ɶ���д�ɹ���
#pragma comment(linker, "/SECTION:SharedDataInDll,RWS")

//����ָ�������ݵ�ָ�룬by adress
int* GetDataPoint()
{
	int * pos = &data[0][0][0];
	return pos;
}

//д���ݣ�ͨ��ֵ����
void SetData(int tmpData, int i, int j, int k)
{
	data[i][j][k] = tmpData;
}

//�����ݣ�ͨ��ֵ����
int	GetData(int i, int j, int k)
{
	return data[i][j][k];
}


/// int �İ汾���Ѿ���֤�ɹ���
#if 0

//ʹ�� #pragma data_seg() ��������һ������Ϊ��������
//һ��Ҫע�������ı�����ʼ���������޷�ʵ�������ڶ�����̼乲 ��
#pragma data_seg("SharedDataInDll")				// �Ǹ�������ݶ����˸����֡�

//��ʼ��Ϊ 0
int data = 0;

#pragma data_seg()


//���ﻹ��Ҫ�������������� SharedDataInDll ���ݶ�Ϊ�ɶ���д�ɹ���
#pragma comment(linker, "/SECTION:SharedDataInDll,RWS")


//���ع�������
int GetData()
{
	return data;
}

//���ù�������
void SetData(int tmpData)
{
	data = tmpData;
}

#endif
