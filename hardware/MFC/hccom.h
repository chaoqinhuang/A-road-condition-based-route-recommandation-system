#pragma once
#ifndef _HCCOM_H
#define _HCCOM_H_

extern char Read_Data[2];

int HC_Init();
int HC_Read();
void HC_Send(char command);

#endif