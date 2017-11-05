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
	SetupComm(hCom, 4096, 4096);  //设置缓冲区容量
	PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR); //清空缓冲区

	COMMTIMEOUTS CommTimeOuts;                         //设置读写超时
	CommTimeOuts.ReadIntervalTimeout = 1000;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 500;
	CommTimeOuts.ReadTotalTimeoutConstant = 500;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 500;
	CommTimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &CommTimeOuts);

	DCB ComDcb;
	GetCommState(hCom, &ComDcb);    //获得串行端口当前配置信息
	ComDcb.BaudRate = 38400;        //设置波特率
	ComDcb.ByteSize = 8;            //采用8位数据位
	ComDcb.Parity = NOPARITY;       //无奇偶校验位
	ComDcb.StopBits = TWOSTOPBITS;  //采用两个停止位
	SetCommState(hCom, &ComDcb);    //重新配置串行端口信息

	HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);

	return 0;
}

void HC_Send(char command)
{
		DWORD dwBytesWritten;
		char szMessage[2];
		szMessage[0] = command;
		memset(buff, 0, 2);                       //申请内存空间                    
		int value_size = sizeof(szMessage);
		for (int i = 0; i < value_size; ++i) {
			WriteFile(hCom, (LPSTR)&szMessage[i], 1, &dwBytesWritten, NULL);    //发送数据	
		}
		PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR); //清空缓冲区
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
		PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR); //清空缓冲区
		return 1;
	
}

DWORD WINAPI ThreadFun(LPVOID pm) {
	return 0;
}
