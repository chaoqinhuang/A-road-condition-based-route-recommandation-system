#include "hccom.h"
#include "stdafx.h"
#include <string>
#include <Windows.h>

HANDLE hCom;
unsigned char buff[20];
DWORD WINAPI ThreadFun(LPVOID pm);
char Read_Data[2];
int HC_Init() 
{
	hCom = CreateFile(TEXT("\\\\.\\COM43"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hCom == INVALID_HANDLE_VALUE) {
		return 1;
	}
	SetupComm(hCom, 4096, 4096);  //���û���������
	PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR); //��ջ�����

	COMMTIMEOUTS CommTimeOuts;                         //���ö�д��ʱ
	CommTimeOuts.ReadIntervalTimeout = 1000;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 500;
	CommTimeOuts.ReadTotalTimeoutConstant = 500;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 500;
	CommTimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &CommTimeOuts);

	DCB ComDcb;
	GetCommState(hCom, &ComDcb);    //��ô��ж˿ڵ�ǰ������Ϣ
	ComDcb.BaudRate = 38400;        //���ò�����
	ComDcb.ByteSize = 8;            //����8λ����λ
	ComDcb.Parity = NOPARITY;       //����żУ��λ
	ComDcb.StopBits = TWOSTOPBITS;  //��������ֹͣλ
	SetCommState(hCom, &ComDcb);    //�������ô��ж˿���Ϣ

	HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);

	return 0;
}

void HC_Send(char command)
{
		DWORD dwBytesWritten;
		char szMessage[2];
		szMessage[0] = command;
		memset(buff, 0, 2);                       //�����ڴ�ռ�                    
		int value_size = sizeof(szMessage);
		for (int i = 0; i < value_size; ++i) {
			WriteFile(hCom, (LPSTR)&szMessage[i], 1, &dwBytesWritten, NULL);    //��������	
		}
		PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR); //��ջ�����
}

int HC_Read()
{
	char str[5];
	DWORD wCount;
	BOOL bReadStat;
	memset(buff, 0, 2);
	bReadStat = ReadFile(hCom, str, 5, &wCount, NULL);
	if (!bReadStat)
	{
		return 0;
	}
	else
		Read_Data[0] = str[0] - '0';
		Read_Data[1] = str[1] - '0';
		PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR); //��ջ�����
		return 1;
	
}

DWORD WINAPI ThreadFun(LPVOID pm) {
	return 0;
}
