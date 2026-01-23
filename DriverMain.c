#include <ntifs.h>
#include "Module.h"
#include "comm\comm.h"
#include "comm\commStruct.h"
#include "RW.h"
#include "ProtectedProcess.h"
#include "FarCall.h"

NTSTATUS NTAPI DispatchComm(PCommPackage package)
{
	PVOID data = package->Data;
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	//DbgPrintEx(77, 0, "[db]:%llx,%llx\r\n", package->Id, package->cmd);
	switch (package->cmd)
	{
	case CMD_TEST:
		status = STATUS_SUCCESS;
		break;
	
	case CMD_GET_MODULE:
	{
		
		PModuleInfo info = (PModuleInfo)data;
		if (info)
		{
			ULONG64 imageSize = 0;
			info->Module = GetModuleR3(info->pid, info->moduleName,&imageSize);
			info->ModuleSize = imageSize;
			status = STATUS_SUCCESS;
		}

		
	}
		break;

	case CMD_READ_MEMORY:
	{
		PReadWriteInfo info = (PReadWriteInfo)data;
		if (info)
		{
			status = ReadMemory2(info->pid, info->BaseAddress, info->Buffer, info->size);
		}
	}
	break;


	case CMD_WRITE_MEMORY:
	{
		PReadWriteInfo info = (PReadWriteInfo)data;
		if (info)
		{
			status = WriteMemory(info->pid, info->BaseAddress, info->Buffer, info->size);
		}
	}
	break;

	case CMD_QUERY_MEMORY:
	{
		PQueryMemoryInfo info = (PQueryMemoryInfo)data;
		if (info)
		{
			status = QueryMemory(info->pid, info->BaseAddress, &info->memoryInfo);
		}
	}
	break;


	case CMD_PROTECT_PROCESS:
	{
		PProtectInfo info = (PProtectInfo)data;
		if (info)
		{
			SetProtectPid(info->pid);
			status = STATUS_SUCCESS;
		}
	}
	break;

	case CMD_REMOTE_CALL:
	{
		PRemoteCallInfo info = (PRemoteCallInfo)data;
		if (info)
		{
			RemoteCall(info->pid, info->shellcode, info->shellcodeSize);
			status = STATUS_SUCCESS;
		}
	}
	break;

	default:
		status = STATUS_NOT_IMPLEMENTED;
		break;
	}
	
	return status;
}


VOID DriverUnload(PDRIVER_OBJECT pDriver)
{
	
	UnRegisterComm();
	DestoryObRegister();
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING pReg)
{
	//DbgBreakPoint();
	//ULONG_PTR moudleBase = GetModuleR3(1332, "kernel32.dll", NULL);
	RegisterComm(DispatchComm);


	InitObRegister();

	//1.直接读写 memcpy   直接切CR3 不附加了  调用附加函数

	//隐藏内存的时候 不会蓝屏
	//2.MmCopyVirtualMemory  ReadProcessMemory

	//3.MDL

	//4.直接映射物理页  第一个效率慢，第二个换页的时候 不是很精确，必须做跨页处理
	// 效率慢的原因 每层地址都自己转化 2 9 9 12   cr3 PDE PTE  10 10 12 2  9 9 9 9 12 4
	

	//5.APC读写 

	//6.队列读写   DXF system->线程下 父进程

	//DXF WIN7 0E异常 验证进程的白名单   PTE

	//CF  替换PML4 中 PDPTE

	//X64 CF 注入的  CR3 VAD  SXG // 

	//VT

	//pDriver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}