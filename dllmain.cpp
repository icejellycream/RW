// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "CommR3.h"
#include "Api.h"

int main(int argc, char * argv[])
{
	if (SH_DriverLoad())
	{
		
		printf("驱动加载成功\r\n");
		//HWND hwnd = NULL;
		//do
		//{
		//	hwnd = FindWindowA("地下城与勇士", "地下城与勇士");
		//	
		//
		//} while (!hwnd);
		//
		//printf("hwnd = %llx\r\n", hwnd);
		//
		//DWORD pid = 0;
		//GetWindowThreadProcessId(hwnd, &pid);
		DWORD pid = 1356;
		
		HMODULE hmodule = LoadLibraryA("user32.dll");
		ULONG_PTR msg = (ULONG_PTR)GetProcAddress(hmodule, "MessageBoxA");

		
		char bufcode[] =
		{
			0x31, 0xC9,
			0x31, 0xD2,
			0x4D, 0x31, 0xC0,
			0x4D, 0x31, 0xC9,
			0x48, 0xB8, 0x99, 0x78, 0x56, 0x34, 0x12, 0x00, 0x00, 0x00,
			0x48, 0x81, 0xEC, 0xA8, 0x00, 0x00, 0x00,
			0xFF, 0xD0,
			0x48, 0x81, 0xC4, 0xA8, 0x00, 0x00, 0x00,
			0xC3
		};

		*(PULONG64)&bufcode[12] = msg;

		SH_RemoteCall(pid, bufcode, sizeof(bufcode));
		//ULONG64 module = SH_GetModule(pid, "explorer.exe");
		//printf("module = %llx\r\n", module);
		//
		//MMEMORY_BASIC_INFORMATION info = {0};
		//
		//SH_QueryMemory(pid, module+0x1234, &info);
		//
		//printf("AllocationBase %llx\r\n", info.AllocationBase);
		//printf("AllocationProtect %llx\r\n", info.AllocationProtect);
		//printf("BaseAddress %llx\r\n", info.BaseAddress);
		//printf("Protect %llx\r\n", info.Protect);
		//printf("RegionSize %llx\r\n", info.RegionSize);
		//printf("State %llx\r\n", info.State);
		//printf("Type %llx\r\n", info.Type);
		//
		//SH_ProtectProcess(GetCurrentProcessId());
		/*
		//A4052D0;
		ULONG64 buffer = 0;
		ULONG startTime = GetTickCount();
		ULONG64 role = module;
		for (int i = 0; i < 1000000; i++)
		{
			SH_ReadMemory(pid, role, &buffer, sizeof(buffer));
		}
		
		ULONG EndTime = GetTickCount();
		
		printf("读100W次耗时 %d毫秒\r\n", EndTime - startTime);
		
		printf("role = %llx\r\n", buffer);
		
		system("pause");
		printf("开始写内存\r\n");
		char buf[4] = {'T','X','S','B'};
		
		SH_WriteMemory(pid,0x12345678, buf, 4);
		*/
		system("pause");
		SH_UnDriverLoad();
	}
	else 
	{
		printf("驱动加载失败\r\n");
	}
	


	system("pause");
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

