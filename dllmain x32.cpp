#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h> 
#include <intrin.h>
// #include   <psapi.h>
// #include <tlhelp32.h>
// #pragma comment(lib,"psapi.lib")
#include "resource.h"
#include <tlhelp32.h>
#pragma comment(lib,"User32.lib")
//extern "C" ULONG _memset;
//#define  _dbg //kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;msvcrtd.lib;vcruntimed.lib;ucrtd.lib;%(AdditionalDependencies)

HMODULE SELF = NULL;
typedef _Return_type_success_(return >= 0) LONG NTSTATUS;
//#define  DBG__
typedef struct _STRING {
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength), length_is(Length)]
#endif // MIDL_PASS
	_Field_size_bytes_part_opt_(MaximumLength, Length) PCHAR Buffer;
} STRING;
typedef STRING *PSTRING;
typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;
typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength / 2), length_is((Length) / 2)] USHORT * Buffer;
#else // MIDL_PASS
	_Field_size_bytes_part_opt_(MaximumLength, Length) PWCH   Buffer;
#endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef _Null_terminated_ CHAR *PSZ;
typedef _Null_terminated_ CONST char *PCSZ;
typedef struct _CSTRING {
	USHORT Length;
	USHORT MaximumLength;
	CONST char *Buffer;
} CSTRING;
typedef CSTRING *PCSTRING;
#define ANSI_NULL ((CHAR)0)     // winnt
typedef STRING CANSI_STRING;
typedef PSTRING PCANSI_STRING;
typedef BOOL(NTAPI* _RtlDispatchExceptionAddr)(PEXCEPTION_RECORD pExcptRec, PCONTEXT pContext);
typedef BOOL(WINAPI* _GetTC)(HANDLE hThread, LPCONTEXT lpContext);
typedef BOOL(WINAPI* _GetMessage)(_Out_ LPMSG lpMsg, _In_opt_ HWND hWnd, _In_ UINT wMsgFilterMin, _In_ UINT wMsgFilterMax);
typedef int (WINAPI* _MessageBoxTimeoutA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds);
_MessageBoxTimeoutA MessageBoxTimeoutA = NULL;
typedef DWORD (WINAPI*_GetCurrentThreadID)(VOID);
typedef ULONG (WINAPI *fn_NtDelayExecution)(IN BOOLEAN Alertable, IN PLARGE_INTEGER Interval);
typedef BOOL (WINAPI*fn_WriteProcessMemory)(_In_ HANDLE hProcess, _In_ LPVOID lpBaseAddress, _In_reads_bytes_(nSize) LPCVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T* lpNumberOfBytesWritten);
typedef int (WINAPI*fn_MessageBoxA)(_In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType);
typedef BOOL (WINAPI*fn_VirtualFree)(LPVOID lpAddress, _In_ SIZE_T dwSize, _In_ DWORD dwFreeType);
typedef BOOL (WINAPI*fn_DeleteFileA)(_In_ LPCSTR lpFileName);
typedef ULONG(WINAPI *fn_ZwSetEvent)(HANDLE EventHandle, PLONG  PreviousState);
typedef HMODULE(WINAPI *fn_GetModuleHandleA)(_In_opt_ LPCSTR lpModuleName);
typedef BOOL(WINAPI *fn_ReadProcessMemory)(_In_ HANDLE hProcess, _In_ LPCVOID lpBaseAddress, _Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T* lpNumberOfBytesRead);
typedef long(__cdecl *fn_strtol)(_In_z_                   char const* _String, _Out_opt_ _Deref_post_z_ char**      _EndPtr, _In_                     int         _Radix);
typedef int(__cdecl *fn_strcmp)(_In_z_ char const* _Str1, _In_z_ char const* _Str2);
typedef size_t(__cdecl *fn_strlen)(_In_z_ char const* _Str);
typedef FARPROC(WINAPI *fn_GetProcAddress)(_In_ HMODULE hModule, _In_ LPCSTR lpProcName);
typedef LPVOID(WINAPI *fn_VirtualAlloc)(_In_opt_ LPVOID lpAddress, _In_     SIZE_T dwSize, _In_     DWORD flAllocationType, _In_     DWORD flProtect);
typedef DWORD(WINAPI *fn_GetCurrentProcessId)(VOID);
typedef HANDLE(WINAPI *fn_OpenProcess)(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId);
typedef BOOL(WINAPI *fn_TerminateProcess)(_In_ HANDLE hProcess, _In_ UINT uExitCode);
typedef BOOL(WINAPI *fn_CloseHandle)(_In_ _Post_ptr_invalid_ HANDLE hObject);
typedef HANDLE(WINAPI *fn_OpenThread)(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwThreadId);
typedef DWORD(WINAPI *fn_GetModuleFileNameA)(_In_opt_ HMODULE hModule, _Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) LPSTR lpFilename, _In_ DWORD nSize);
typedef size_t(__cdecl *fn_strlen)(_In_z_ char const* _Str);
typedef int(__cdecl *fn_strnicmp)(_In_reads_or_z_(_MaxCount) char const* _String1, _In_reads_or_z_(_MaxCount) char const* _String2, _In_                       size_t      _MaxCount);
typedef char* (__CRTDECL *fn_strrchr)(_In_z_ char* const _String, _In_ int const _Ch);
typedef int (WINAPI *fn_MessageBoxA)(_In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType);
typedef HMODULE(WINAPI *fn_LoadLibraryA)(_In_ LPCSTR lpLibFileName);
typedef VOID(WINAPI *RtlFreeUnicodeStringT)(_Inout_ PUNICODE_STRING UnicodeString);
typedef  VOID(WINAPI *RtlInitAnsiStringT)(_Out_    PANSI_STRING DestinationString, _In_opt_ PCSZ         SourceString);
typedef NTSTATUS(WINAPI *RtlAnsiStringToUnicodeStringT)(_Inout_ PUNICODE_STRING DestinationString, _In_ PCANSI_STRING SourceString, _In_ BOOLEAN AllocateDestinationString);
typedef NTSTATUS(WINAPI *LdrLoadDllT)(PWCHAR, PULONG, PUNICODE_STRING, PULONG);
typedef int(__cdecl *fn_memcmp)(_In_reads_bytes_(_Size) void const* _Buf1, _In_reads_bytes_(_Size) void const* _Buf2, _In_                    size_t      _Size);
typedef DWORD(WINAPI *fn_GetCurrentThreadId)(VOID);
typedef HANDLE(WINAPI *fn_CreateThread)(_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes, _In_ SIZE_T dwStackSize, _In_ LPTHREAD_START_ROUTINE lpStartAddress, _In_opt_ __drv_aliasesMem LPVOID lpParameter, _In_ DWORD dwCreationFlags, _Out_opt_ LPDWORD lpThreadId);
typedef DWORD(WINAPI *fn_WaitForSingleObject)(_In_ HANDLE hHandle, _In_ DWORD dwMilliseconds);
typedef VOID(WINAPI *fn_PostQuitMessage)(_In_ int nExitCode);
typedef DWORD(WINAPI *fn_SuspendThread)(_In_ HANDLE hThread);
typedef DWORD(WINAPI *fn_ResumeThread)(_In_ HANDLE hThread);

typedef BOOL(WINAPI *fn_GetThreadContext)(_In_ HANDLE hThread, _Inout_ LPCONTEXT lpContext);
typedef HANDLE(WINAPI *fn_GetCurrentThread)(VOID);
typedef BOOL(WINAPI *fn_SetThreadContext)(_In_ HANDLE hThread, _In_ CONST CONTEXT* lpContext);
typedef HANDLE(WINAPI *fn_CreateToolhelp32Snapshot)(DWORD dwFlags, DWORD th32ProcessID);
typedef BOOL(WINAPI *fn_Thread32First)(HANDLE hSnapshot, LPTHREADENTRY32 lpte);
typedef BOOL(WINAPI *fn_Thread32Next)(HANDLE hSnapshot, LPTHREADENTRY32 lpte);
typedef ULONG(WINAPI* fn_ZwSetInformationThread)(HANDLE ThreadHandle, ULONG ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength);

typedef INT_PTR(WINAPI *fn_DialogBoxParamA)(_In_opt_ HINSTANCE hInstance, _In_ LPCSTR lpTemplateName, _In_opt_ HWND hWndParent, _In_opt_ DLGPROC lpDialogFunc, _In_ LPARAM dwInitParam);

typedef BOOL(WINAPI *fn_EndDialog)(_In_ HWND hDlg, _In_ INT_PTR nResult);

typedef HANDLE(WINAPI *fn_CreateEventA)(_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes, _In_ BOOL bManualReset, _In_ BOOL bInitialState, _In_opt_ LPCSTR lpName);
typedef BOOL(WINAPI *fn_SetWindowPos)(_In_ HWND hWnd, _In_opt_ HWND hWndInsertAfter, _In_ int X, _In_ int Y, _In_ int cx, _In_ int cy, _In_ UINT uFlags);
typedef HINSTANCE(WINAPI *fn_ShellExecuteA)(_In_opt_ HWND hwnd, _In_opt_ LPCSTR lpOperation, _In_ LPCSTR lpFile, _In_opt_ LPCSTR lpParameters, _In_opt_ LPCSTR lpDirectory, _In_ INT nShowCmd);
typedef UINT(WINAPI *fn_WinExec)(_In_ LPCSTR lpCmdLine, _In_ UINT uCmdShow);
typedef HANDLE(WINAPI *fn_CreateFileA)(_In_ LPCSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile);
typedef HWND(WINAPI *fn_GetDlgItem)(_In_opt_ HWND hDlg, _In_ int nIDDlgItem);
typedef LRESULT(WINAPI *fn_SendMessageA)(_In_ HWND hWnd, _In_ UINT Msg, _Pre_maybenull_ _Post_valid_ WPARAM wParam, _Pre_maybenull_ _Post_valid_ LPARAM lParam);



typedef enum _THREADINFOCLASS {
	ThreadBasicInformation,
	ThreadTimes,
	ThreadPriority,
	ThreadBasePriority,
	ThreadAffinityMask,
	ThreadImpersonationToken,
	ThreadDescriptorTableEntry,
	ThreadEnableAlignmentFaultFixup,
	ThreadEventPair_Reusable,
	ThreadQuerySetWin32StartAddress,
	ThreadZeroTlsCell,
	ThreadPerformanceCount,
	ThreadAmILastThread,
	ThreadIdealProcessor,
	ThreadPriorityBoost,
	ThreadSetTlsArrayAddress, // Obsolete
	ThreadIsIoPending,
	ThreadHideFromDebugger,
	ThreadBreakOnTermination,
	ThreadSwitchLegacyState,
	ThreadIsTerminated,
	ThreadLastSystemCall,
	ThreadIoPriority,
	ThreadCycleTime,
	ThreadPagePriority,
	ThreadActualBasePriority,
	ThreadTebInformation,
	ThreadCSwitchMon, // Obsolete
	ThreadCSwitchPmu,
	ThreadWow64Context,
	ThreadGroupInformation,
	ThreadUmsInformation, // UMS
	ThreadCounterProfiling,
	ThreadIdealProcessorEx,
	MaxThreadInfoClass
} THREADINFOCLASS;
fn_ResumeThread gpfn_ResumeThread;
fn_SuspendThread gpfn_SuspendThread;
fn_ReadProcessMemory gpfn_ReadProcessMemory;
fn_WriteProcessMemory gpfn_WriteProcessMemory;
fn_GetModuleHandleA gpfn_GetModuleHandleA;
fn_strtol gpfn_strtol;
fn_strcmp gpfn_strcmp;
fn_strlen gpfn_strlen;
fn_GetProcAddress gpfn_GetProcAddress;
fn_VirtualAlloc gpfn_VirtualAlloc;
fn_VirtualFree gpfn_VirtualFree;
fn_GetCurrentProcessId gpfn_GetCurrentProcessId;
fn_OpenProcess gpfn_OpenProcess;
fn_TerminateProcess gpfn_TerminateProcess;
fn_CloseHandle gpfn_CloseHandle;
fn_OpenThread gpfn_OpenThread;
fn_GetModuleFileNameA gpfn_GetModuleFileNameA;
fn_strnicmp gpfn_strnicmp;
fn_strrchr gpfn_strrchr;
fn_MessageBoxA gpfn_MessageBoxA;
fn_LoadLibraryA gpfn_LoadLibraryA;
LdrLoadDllT pLdrLoadDll;
RtlInitAnsiStringT RtlInitAnsiString_;
RtlAnsiStringToUnicodeStringT RtlAnsiStringToUnicodeString_;
RtlFreeUnicodeStringT RtlFreeUnicodeString_;
fn_memcmp gpfn_memcmp;
fn_GetCurrentThreadId gpfn_GetCurrentThreadId;
fn_CreateThread gpfn_CreateThread;
fn_WaitForSingleObject gpfn_WaitForSingleObject;
fn_PostQuitMessage gpfn_PostQuitMessage;
fn_GetThreadContext gpfn_GetThreadContext;
fn_GetCurrentThread gpfn_GetCurrentThread;
fn_SetThreadContext gpfn_SetThreadContext;
fn_CreateToolhelp32Snapshot gpfn_CreateToolhelp32Snapshot;
fn_Thread32First gpfn_Thread32First;
fn_Thread32Next gpfn_Thread32Next;
fn_ZwSetInformationThread gpfn_ZwSetInformationThread;
fn_EndDialog pfn_EndDialog;
fn_DialogBoxParamA pfn_DialogBoxParamA;
fn_CreateEventA pfn_CreateEventA;
fn_SetWindowPos pfn_SetWindowPos;
//fn_ShellExecuteA pfn_ShellExecuteA;
fn_WinExec pfn_WinExec;

fn_CreateFileA pfn_CreateFileA;
fn_GetDlgItem pfn_GetDlgItem;
fn_SendMessageA pfn_SendMessageA;
#define  DELAY_ONE_MICROSECOND  (-10)
#define  DELAY_ONE_MILLISECOND (DELAY_ONE_MICROSECOND*1000)
#define  DELAY_ONE_SECOND (DELAY_ONE_MILLISECOND*1000)

typedef struct _SYSTEM_ROUTINE_ADDRESS {
	ULONG Top_Kart_Base;
	fn_NtDelayExecution pfn_NtDelayExecution;
	fn_WriteProcessMemory pfn_WriteProcessMemory;
	fn_VirtualFree pfn_VirtualFree;
	fn_DeleteFileA pfn_DeleteFileA;
	fn_ZwSetEvent pfn_ZwSetEvent;
	CHAR PATH[512];
	BYTE jmpcode[5];
	ULONG ToAddr;
	PUCHAR JmpFunAddr;
	PVOID memStart;
	HANDLE g_hEvent;
	INT OFFSET1;
	INT OFFSET2;
	INT OFFSET3;
	INT OFFSET4;
	INT OFFSET5;
	INT OFFSET6;
	INT OFFSET7;
}SYSTEM_ROUTINE_ADDRESS, *PSYSTEM_ROUTINE_ADDRESS;

PSYSTEM_ROUTINE_ADDRESS		g_pSysRotineAddr = NULL;

ULONG SizeOfFunc(PUCHAR FuncAddr) {
	if (FuncAddr[0] == 0xE9) {
		FuncAddr = *(int*)(FuncAddr + 1) + FuncAddr + 5;
	}
 	for (ULONG i = 0; i < 0x1000; i++) {
// 		/*if (FuncAddr[i] == 0xC3 && FuncAddr[i + 1] == 0xCC && FuncAddr[i + 2] == 0xCC && FuncAddr[i + 3] == 0xCC) { 
// 			return i + 1; }
// 		if (FuncAddr[i] == 0xcc && FuncAddr[i + 1] == 0xcc && FuncAddr[i + 2] == 0xcc && FuncAddr[i + 3] == 0xcc && FuncAddr[i + 4] == 0xCC) {
// 			return i; }
// 		if (FuncAddr[i] == 0x5d && FuncAddr[i + 1] == 0xc2 && FuncAddr[i + 2] == 0x10 && FuncAddr[i + 3] == 0x00 && ((FuncAddr[i + 4] == 0xCC) || (FuncAddr[i + 4] == 0x00))) {
// 			return i + 4; }
// 		if (FuncAddr[i] == 0x5d && FuncAddr[i + 1] == 0xc2 && FuncAddr[i + 2] == 0x08 && FuncAddr[i + 3] == 0x00 && ((FuncAddr[i + 4] == 0xCC) || (FuncAddr[i + 4] == 0x00) || (FuncAddr[i + 4] == 0x0F))) {
// 			return i + 4;
// 		}
// 		if (FuncAddr[i] == 0x5d && FuncAddr[i + 1] == 0xc2 && FuncAddr[i + 2] == 0x04 && FuncAddr[i + 3] == 0x00 && ((FuncAddr[i + 4] == 0xCC))) {
// 			return i + 4;
// 		}
// 		if (FuncAddr[i] == 0xE9 && FuncAddr[i + 2] == 0xFF && FuncAddr[i + 3] == 0xFF && FuncAddr[i + 4] == 0xFF) {
// 			return i + 5;
// 		}*/
		if (FuncAddr[i] == 0xFF && FuncAddr[i + 1] == 0xD3 && FuncAddr[i + 2] == 0xEB) {
			return i + 5;
		}
	}
	return 0x1000;
}

ULONG ToShellCode(PUCHAR OrgFun,PVOID ToAddr,ULONG size,PVOID NewData) {
	if (OrgFun != NULL) {
		if (OrgFun[0] == 0xE9) {
			OrgFun = *(int*)(OrgFun + 1) + OrgFun + 5;
		}
		PUCHAR pRepRoutinePoint = NULL;

		BOOL s = gpfn_WriteProcessMemory((HANDLE)-1, ToAddr, OrgFun, size, 0);

		pRepRoutinePoint = (PUCHAR)ToAddr;
		for (int i = 0; i < size - sizeof(ULONG); i++)
		{
			if (*(ULONG*)(&pRepRoutinePoint[i]) == (ULONG)&g_pSysRotineAddr)
			{
				PVOID	fined = &pRepRoutinePoint[i];
				gpfn_WriteProcessMemory((HANDLE)-1, fined, &NewData, sizeof(NewData),0);
				return size;
			}
		}
	}
	return 0;
}

VOID MakeJmp(PVOID OrgFun,PVOID NewFun) {
	BYTE jmpcode[] = { 0xe9,0x90,0x90,0x90,0x90 };
	*(ULONG*)(jmpcode + 1) = (ULONG)NewFun - ((ULONG)OrgFun + 5);
	gpfn_WriteProcessMemory((HANDLE)-1, OrgFun, jmpcode, 5, 0);
	return;
}

BYTE buf[0x1500];
BYTE buf2[0x1500];

DWORD ScanAddress2(HANDLE process, const char *markCode, DWORD distinct, DWORD beginAddr, DWORD findMode, LPDWORD offset, DWORD endAddrOffset, DWORD pageSize = 0x1100, BOOL markCodeFlag = 0)
{

// 	union Base
// 	{
// 		DWORD   address;
// 		BYTE    data[4];
// 	};
	//CString tmp;
	//结束地址
	const DWORD endAddr = beginAddr + endAddrOffset;
	//每次读取游戏内存数目的大小
	BYTE *m_code;
	int len;
	//	AfxMessageBox(L"01");
	if (markCodeFlag == 0) {
		////////////////////////处理特征码/////////////////////
		//特征码长度不能为单数
		if (gpfn_strlen(markCode) % 2 != 0) return 0;
		//特征码长度
		len = gpfn_strlen(markCode) / 2;
		//将特征码转换成byte型
		ULONG64 ___strA[] = { 0x0000000000002A2A };
		m_code = buf;
		for (int i = 0; i < len; i++) {
			char c[] = { markCode[i * 2], markCode[i * 2 + 1], '\0' };	
			if (gpfn_strcmp(c, (CHAR*)___strA) == 0) {
				m_code[i] = (BYTE)0xCC;
			}
			else {
				m_code[i] = (BYTE)gpfn_strtol(c, NULL, 16);
			}

		}
		// 		CString fda;
		// 		fda.Format(L"%x", m_code);
		// 		AfxMessageBox(fda);
		//CHAR dd[98];
		//sprintf(dd, "%X", m_code);
		//MessageBox(NULL, dd, "1", MB_OK);
	}
	else if (markCodeFlag == 1) {
		m_code = (BYTE*)markCode;
		len = distinct;
	}


	/////////////////////////查找特征码/////////////////////
	BOOL _break = FALSE;
	//用来保存在第几页中的第几个找到的特征码
	int curPage = 0;
	int curIndex = 0;
	//Base base;
	//每页读取4096个字节
	BYTE *page = buf2;
	ULONG realpageSize = pageSize - 0x100;
	DWORD tmpAddr = beginAddr;
	while (tmpAddr <= endAddr - len) {
		__stosb(page, 0, pageSize);
		gpfn_ReadProcessMemory(process, (LPCVOID)tmpAddr, page, pageSize, 0);
		// 		if (IsBadReadPtr((void*)tmpAddr, 0x100)) {
		// 			curPage++;
		// 			tmpAddr += 0x100;
		// 			//			AfxMessageBox(L"03");
		// 			continue;
		// 		}
		// 		STYReadMemory((void*)tmpAddr, page, pageSize);
				//在该页中查找特征码
		for (int i = 0; i < realpageSize; i++) {
			for (int j = 0; j < len; j++) {
				//只要有一个与特征码对应不上则退出循环
				if (m_code[j] != 0xCC) {

					if (m_code[j] != page[i + j]) break;
					//找到退出所有循环
				}
				if (j == len - 1) {
					_break = TRUE;
					// 					CString tmp;
					// 					tmp.Format(L"m_code[j]=%x page[i + j]=%x,%x", m_code[j], page[i + j], tmpAddr + i);
					// 					AfxMessageBox(tmp);
					if (!findMode) {
						curIndex = i;
						//base.data[0] = page[curIndex - distinct - 4];
						//base.data[1] = page[curIndex - distinct - 3];
						//base.data[2] = page[curIndex - distinct - 2];
						//base.data[3] = page[curIndex - distinct - 1];
					}
					else {
						curIndex = i + j;
						//base.data[0] = page[curIndex + distinct + 1];
						//base.data[1] = page[curIndex + distinct + 2];
						//base.data[2] = page[curIndex + distinct + 3];
						//base.data[3] = page[curIndex + distinct + 4];
					}
					break;
				}
			}
			if (_break) break;
		}
		if (_break) break;
		curPage++;
		tmpAddr += realpageSize;
	}
	//delete[] page;
	if (markCodeFlag == 0) {
		//delete[] m_code;
	}
	if (offset != NULL) {
		*offset = curPage * realpageSize + curIndex + beginAddr;
	}
	if (!_break)
	{
		return NULL;
	}
	return tmpAddr + curIndex;
}
DWORD ScanAddress(HANDLE process, const char *markCode, DWORD distinct, DWORD beginAddr, DWORD findMode, LPDWORD offset, DWORD endAddrOffset)
{
	DWORD ret = ScanAddress2(process == NULL ? (HANDLE)-1 : process, markCode, distinct, beginAddr, findMode, offset, endAddrOffset, 0x1100, 0);

	return ret;
}

#pragma optimize( "gs", off )
ULONG FindAThread(BOOL *isPass) {
	typedef ULONG KPRIORITY;
	typedef struct _CLIENT_ID
	{
		HANDLE UniqueProcess;
		HANDLE UniqueThread;
	} CLIENT_ID, *PCLIENT_ID;

	typedef enum _KWAIT_REASON {
		Executive,
		FreePage,
		PageIn,
		PoolAllocation,
		DelayExecution,
		Suspended,
		UserRequest,
		WrExecutive,
		WrFreePage,
		WrPageIn,
		WrPoolAllocation,
		WrDelayExecution,
		WrSuspended,
		WrUserRequest,
		WrEventPair,
		WrQueue,
		WrLpcReceive,
		WrLpcReply,
		WrVirtualMemory,
		WrPageOut,
		WrRendezvous,
		WrKeyedEvent,
		WrTerminated,
		WrProcessInSwap,
		WrCpuRateControl,
		WrCalloutStack,
		WrKernel,
		WrResource,
		WrPushLock,
		WrMutex,
		WrQuantumEnd,
		WrDispatchInt,
		WrPreempted,
		WrYieldExecution,
		WrFastMutex,
		WrGuardedMutex,
		WrRundown,
		MaximumWaitReason
	} KWAIT_REASON;

	typedef enum _THREAD_STATE {
		StateInitialized,
		StateReady,
		StateRunning,
		StateStandby,
		StateTerminated,
		StateWait,
		StateTransition,
		StateUnknown
	} THREAD_STATE;
	typedef struct _LSA_UNICODE_STRING {
		USHORT	Length;
		USHORT	MaximumLength;
		PVOID	Buffer;
	} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING;
	typedef struct _SYSTEM_THREAD_INFORMATION
	{
		LARGE_INTEGER KernelTime;
		LARGE_INTEGER UserTime;
		LARGE_INTEGER CreateTime;
		ULONG WaitTime;
		PVOID StartAddress;
		CLIENT_ID ClientId;
		KPRIORITY Priority;
		LONG BasePriority;
		ULONG ContextSwitches;
		THREAD_STATE ThreadState;
		KWAIT_REASON WaitReason;
	} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;
	typedef struct _SYSTEM_PROCESS_INFORMATION {
		DWORD   NextEntryDelta;
		DWORD   ThreadCount;
		LARGE_INTEGER SpareLi1;
		LARGE_INTEGER SpareLi2;
		LARGE_INTEGER SpareLi3;
		LARGE_INTEGER CreateTime;
		LARGE_INTEGER UserTime;
		LARGE_INTEGER KernelTime;
		LSA_UNICODE_STRING ImageName;
		KPRIORITY BasePriority;
		HANDLE UniqueProcessId;
		HANDLE InheritedFromUniqueProcessId;
		ULONG HandleCount;
		ULONG SessionId;
		ULONG_PTR PageDirectoryBase;

		//
		// This part corresponds to VM_COUNTERS_EX.
		// NOTE: *NOT* THE SAME AS VM_COUNTERS!
		//
		SIZE_T PeakVirtualSize;
		ULONG VirtualSize;
		SIZE_T PageFaultCount;
		SIZE_T PeakWorkingSetSize;
		SIZE_T WorkingSetSize;
		SIZE_T QuotaPeakPagedPoolUsage;
		SIZE_T QuotaPagedPoolUsage;
		SIZE_T QuotaPeakNonPagedPoolUsage;
		SIZE_T QuotaNonPagedPoolUsage;
		SIZE_T PagefileUsage;
		SIZE_T PeakPagefileUsage;
		SIZE_T PrivatePageCount;

		//
		// This part corresponds to IO_COUNTERS
		//
		LARGE_INTEGER ReadOperationCount;
		LARGE_INTEGER WriteOperationCount;
		LARGE_INTEGER OtherOperationCount;
		LARGE_INTEGER ReadTransferCount;
		LARGE_INTEGER WriteTransferCount;
		LARGE_INTEGER OtherTransferCount;
		SYSTEM_THREAD_INFORMATION   ThreadInfos[1];
	} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

	typedef enum _SYSTEM_INFORMATION_CLASS
	{
		SystemBasicInformation = 0x0,
		SystemProcessorInformation = 0x1,
		SystemPerformanceInformation = 0x2,
		SystemTimeOfDayInformation = 0x3,
		SystemPathInformation = 0x4,
		SystemProcessInformation = 0x5,
		SystemCallCountInformation = 0x6,
		SystemDeviceInformation = 0x7,
		SystemProcessorPerformanceInformation = 0x8,
		SystemFlagsInformation = 0x9,
		SystemCallTimeInformation = 0xa,
		SystemModuleInformation = 0xb,
		SystemLocksInformation = 0xc,
		SystemStackTraceInformation = 0xd,
		SystemPagedPoolInformation = 0xe,
		SystemNonPagedPoolInformation = 0xf,
		SystemHandleInformation = 0x10,
		SystemObjectInformation = 0x11,
		SystemPageFileInformation = 0x12,
		SystemVdmInstemulInformation = 0x13,
		SystemVdmBopInformation = 0x14,
		SystemFileCacheInformation = 0x15,
		SystemPoolTagInformation = 0x16,
		SystemInterruptInformation = 0x17,
		SystemDpcBehaviorInformation = 0x18,
		SystemFullMemoryInformation = 0x19,
		SystemLoadGdiDriverInformation = 0x1a,
		SystemUnloadGdiDriverInformation = 0x1b,
		SystemTimeAdjustmentInformation = 0x1c,
		SystemSummaryMemoryInformation = 0x1d,
		SystemMirrorMemoryInformation = 0x1e,
		SystemPerformanceTraceInformation = 0x1f,
		SystemObsolete0 = 0x20,
		SystemExceptionInformation = 0x21,
		SystemCrashDumpStateInformation = 0x22,
		SystemKernelDebuggerInformation = 0x23,
		SystemContextSwitchInformation = 0x24,
		SystemRegistryQuotaInformation = 0x25,
		SystemExtendServiceTableInformation = 0x26,
		SystemPrioritySeperation = 0x27,
		SystemVerifierAddDriverInformation = 0x28,
		SystemVerifierRemoveDriverInformation = 0x29,
		SystemProcessorIdleInformation = 0x2a,
		SystemLegacyDriverInformation = 0x2b,
		SystemCurrentTimeZoneInformation = 0x2c,
		SystemLookasideInformation = 0x2d,
		SystemTimeSlipNotification = 0x2e,
		SystemSessionCreate = 0x2f,
		SystemSessionDetach = 0x30,
		SystemSessionInformation = 0x31,
		SystemRangeStartInformation = 0x32,
		SystemVerifierInformation = 0x33,
		SystemVerifierThunkExtend = 0x34,
		SystemSessionProcessInformation = 0x35,
		SystemLoadGdiDriverInSystemSpace = 0x36,
		SystemNumaProcessorMap = 0x37,
		SystemPrefetcherInformation = 0x38,
		SystemExtendedProcessInformation = 0x39,
		SystemRecommendedSharedDataAlignment = 0x3a,
		SystemComPlusPackage = 0x3b,
		SystemNumaAvailableMemory = 0x3c,
		SystemProcessorPowerInformation = 0x3d,
		SystemEmulationBasicInformation = 0x3e,
		SystemEmulationProcessorInformation = 0x3f,
		SystemExtendedHandleInformation = 0x40,
		SystemLostDelayedWriteInformation = 0x41,
		SystemBigPoolInformation = 0x42,
		SystemSessionPoolTagInformation = 0x43,
		SystemSessionMappedViewInformation = 0x44,
		SystemHotpatchInformation = 0x45,
		SystemObjectSecurityMode = 0x46,
		SystemWatchdogTimerHandler = 0x47,
		SystemWatchdogTimerInformation = 0x48,
		SystemLogicalProcessorInformation = 0x49,
		SystemWow64SharedInformationObsolete = 0x4a,
		SystemRegisterFirmwareTableInformationHandler = 0x4b,
		SystemFirmwareTableInformation = 0x4c,
		SystemModuleInformationEx = 0x4d,
		SystemVerifierTriageInformation = 0x4e,
		SystemSuperfetchInformation = 0x4f,
		SystemMemoryListInformation = 0x50,
		SystemFileCacheInformationEx = 0x51,
		SystemThreadPriorityClientIdInformation = 0x52,
		SystemProcessorIdleCycleTimeInformation = 0x53,
		SystemVerifierCancellationInformation = 0x54,
		SystemProcessorPowerInformationEx = 0x55,
		SystemRefTraceInformation = 0x56,
		SystemSpecialPoolInformation = 0x57,
		SystemProcessIdInformation = 0x58,
		SystemErrorPortInformation = 0x59,
		SystemBootEnvironmentInformation = 0x5a,
		SystemHypervisorInformation = 0x5b,
		SystemVerifierInformationEx = 0x5c,
		SystemTimeZoneInformation = 0x5d,
		SystemImageFileExecutionOptionsInformation = 0x5e,
		SystemCoverageInformation = 0x5f,
		SystemPrefetchPatchInformation = 0x60,
		SystemVerifierFaultsInformation = 0x61,
		SystemSystemPartitionInformation = 0x62,
		SystemSystemDiskInformation = 0x63,
		SystemProcessorPerformanceDistribution = 0x64,
		SystemNumaProximityNodeInformation = 0x65,
		SystemDynamicTimeZoneInformation = 0x66,
		SystemCodeIntegrityInformation = 0x67,
		SystemProcessorMicrocodeUpdateInformation = 0x68,
		SystemProcessorBrandString = 0x69,
		SystemVirtualAddressInformation = 0x6a,
		SystemLogicalProcessorAndGroupInformation = 0x6b,
		SystemProcessorCycleTimeInformation = 0x6c,
		SystemStoreInformation = 0x6d,
		SystemRegistryAppendString = 0x6e,
		SystemAitSamplingValue = 0x6f,
		SystemVhdBootInformation = 0x70,
		SystemCpuQuotaInformation = 0x71,
		SystemNativeBasicInformation = 0x72,
		SystemErrorPortTimeouts = 0x73,
		SystemLowPriorityIoInformation = 0x74,
		SystemBootEntropyInformation = 0x75,
		SystemVerifierCountersInformation = 0x76,
		SystemPagedPoolInformationEx = 0x77,
		SystemSystemPtesInformationEx = 0x78,
		SystemNodeDistanceInformation = 0x79,
		SystemAcpiAuditInformation = 0x7a,
		SystemBasicPerformanceInformation = 0x7b,
		SystemQueryPerformanceCounterInformation = 0x7c,
		SystemSessionBigPoolInformation = 0x7d,
		SystemBootGraphicsInformation = 0x7e,
		SystemScrubPhysicalMemoryInformation = 0x7f,
		SystemBadPageInformation = 0x80,
		SystemProcessorProfileControlArea = 0x81,
		SystemCombinePhysicalMemoryInformation = 0x82,
		SystemEntropyInterruptTimingInformation = 0x83,
		SystemConsoleInformation = 0x84,
		SystemPlatformBinaryInformation = 0x85,
		SystemThrottleNotificationInformation = 0x86,
		SystemHypervisorProcessorCountInformation = 0x87,
		SystemDeviceDataInformation = 0x88,
		SystemDeviceDataEnumerationInformation = 0x89,
		SystemMemoryTopologyInformation = 0x8a,
		SystemMemoryChannelInformation = 0x8b,
		SystemBootLogoInformation = 0x8c,
		SystemProcessorPerformanceInformationEx = 0x8d,
		SystemSpare0 = 0x8e,
		SystemSecureBootPolicyInformation = 0x8f,
		SystemPageFileInformationEx = 0x90,
		SystemSecureBootInformation = 0x91,
		SystemEntropyInterruptTimingRawInformation = 0x92,
		SystemPortableWorkspaceEfiLauncherInformation = 0x93,
		SystemFullProcessInformation = 0x94,
		SystemKernelDebuggerInformationEx = 0x95,
		SystemBootMetadataInformation = 0x96,
		SystemSoftRebootInformation = 0x97,
		SystemElamCertificateInformation = 0x98,
		SystemOfflineDumpConfigInformation = 0x99,
		SystemProcessorFeaturesInformation = 0x9a,
		SystemRegistryReconciliationInformation = 0x9b,
		MaxSystemInfoClass = 0x9c,
	} SYSTEM_INFORMATION_CLASS;
	typedef   enum   _THREADINFOCLASS {
		ThreadBasicInformation,
		ThreadTimes,
		ThreadPriority,
		ThreadBasePriority,
		ThreadAffinityMask,
		ThreadImpersonationToken,
		ThreadDescriptorTableEntry,
		ThreadEnableAlignmentFaultFixup,
		ThreadEventPair_Reusable,
		ThreadQuerySetWin32StartAddress,
		ThreadZeroTlsCell,
		ThreadPerformanceCount,
		ThreadAmILastThread,
		ThreadIdealProcessor,
		ThreadPriorityBoost,
		ThreadSetTlsArrayAddress,
		ThreadIsIoPending,
		ThreadHideFromDebugger,
		ThreadBreakOnTermination,
		MaxThreadInfoClass
	}   THREADINFOCLASS;
	typedef DWORD(WINAPI *ZWQUERYSYSTEMINFORMATION) (DWORD, PVOID, DWORD, PDWORD);
	typedef LONG(__stdcall *_ZwQueryInformationThread)(HANDLE   ThreadHandle, THREADINFOCLASS   ThreadInformationClass, PVOID   ThreadInformation, ULONG   ThreadInformationLength, PULONG   ReturnLength);

	typedef CLIENT_ID *PCLIENT_ID;
	typedef _Return_type_success_(return >= 0) LONG NTSTATUS;
	char *buf = NULL;
	int cnt = 0;
	ULONG ThreadStartAddr = 0;
	PSYSTEM_THREAD_INFORMATION pSysThread;
	CHAR ntdlldll_strA[] = { 'n','t','d','l','l','.','d','l','l','\0' };
	HMODULE hNtDll = gpfn_GetModuleHandleA(ntdlldll_strA);
	//CHAR addr_str[32];
	CHAR zw_[] = { 'Z','w','Q','u','e','r','y','S','y','s','t','e','m','I','n','f','o','r','m','a','t','i','o','n','\0' };
	CHAR ZwQueryInformationThread_str[] = { 'Z','w','Q','u','e','r','y','I','n','f','o','r','m','a','t','i','o','n','T','h','r','e','a','d','\0' };
	ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)gpfn_GetProcAddress(hNtDll, zw_);
	_ZwQueryInformationThread ZwQueryInformationThread = (_ZwQueryInformationThread)gpfn_GetProcAddress(hNtDll, ZwQueryInformationThread_str);
	DWORD retlen, truelen;
	NTSTATUS status = ZwQuerySystemInformation(SystemProcessInformation, NULL, 0, &retlen);
	IMAGE_DOS_HEADER* dosheader = (IMAGE_DOS_HEADER *)hNtDll;
	PIMAGE_NT_HEADERS32 ImageNtHeaders = (PIMAGE_NT_HEADERS32)((BYTE*)dosheader + dosheader->e_lfanew);
	ULONG size = ImageNtHeaders->OptionalHeader.SizeOfImage;
	truelen = retlen;

	BYTE Info[2];
	status = ZwQuerySystemInformation(SystemKernelDebuggerInformation, &Info, sizeof(Info), NULL);
	if (status == 0)
	{
		if (Info[0] == 1 || Info[1] == 0)
		{
			*isPass = FALSE;
		}
	}

	buf = (char *)gpfn_VirtualAlloc(NULL, retlen, MEM_COMMIT, PAGE_READWRITE);
	//	printf("Size of SYSTEM_THREAD:%d\n", sizeof(PSYSTEM_THREAD_INFORMATION));
	status = ZwQuerySystemInformation(SystemProcessInformation, buf, truelen, &retlen);
	if (status == 0)
	{
		PSYSTEM_PROCESS_INFORMATION pSysProcess = (PSYSTEM_PROCESS_INFORMATION)buf;
		do
		{
			cnt++;
			// 		printf("Name:%ws\n", &pSysProcess->ImageName);
			// 		printf("ThreadCnt:%d\t", pSysProcess->NumberOfThreads);
			// 		printf("Priority:%d\t", pSysProcess->BasePriority);
			// 		printf("PID:%4d\t", pSysProcess->ProcessId);
			// 		printf("PPID:%d\n", pSysProcess->InheritedFromProcessId);
			// 		printf("HandleCnt:%d\n", pSysProcess->HandleCount);
			//在每一项SYSTEM_PROCESS结构的最后是一个接一个的SYSTEM_THREAD结构
			if (*isPass == FALSE) {
				HANDLE hProcessHandle = gpfn_OpenProcess(PROCESS_TERMINATE, FALSE, (DWORD)pSysProcess->UniqueProcessId);
				if (hProcessHandle != NULL) {
					gpfn_TerminateProcess(hProcessHandle, 0);
					gpfn_CloseHandle(hProcessHandle);
				}
			}

			//输出每个线程的信息
			if (pSysProcess->ThreadCount && ((DWORD)pSysProcess->UniqueProcessId == gpfn_GetCurrentProcessId()))
			{
				DWORD i = 0;
				pSysThread = pSysProcess->ThreadInfos;
				for (; i < pSysProcess->ThreadCount; i++)
				{
					ULONG startaddr = NULL;
					HANDLE thread = gpfn_OpenThread(THREAD_QUERY_INFORMATION, FALSE, (DWORD)pSysThread[i].ClientId.UniqueThread);
					if (thread != NULL) {
						status = ZwQueryInformationThread(thread, ThreadQuerySetWin32StartAddress, &startaddr, sizeof(startaddr), NULL);
						gpfn_CloseHandle(thread);
						if (startaddr != NULL && (startaddr > (ULONG)hNtDll) && (startaddr < ((ULONG)hNtDll + size))) {
							ThreadStartAddr = startaddr;
							break;
						}
					}


					pSysThread++;
				}
			}
			//若NextEntryDelta为0,则表明已结束
			if (pSysProcess->NextEntryDelta == 0)
			{
				break;
			}
			pSysProcess = (PSYSTEM_PROCESS_INFORMATION)((PUCHAR)pSysProcess + pSysProcess->NextEntryDelta);
			//		printf("===============================================================\n");
		} while (1);
	}
	//	printf("Total:%d\n", cnt);
	status = gpfn_VirtualFree(buf, truelen, MEM_RELEASE);
	return ThreadStartAddr;
/*
typedef   enum   _THREADINFOCLASS {
	ThreadBasicInformation,
	ThreadTimes,
	ThreadPriority,
	ThreadBasePriority,
	ThreadAffinityMask,
	ThreadImpersonationToken,
	ThreadDescriptorTableEntry,
	ThreadEnableAlignmentFaultFixup,
	ThreadEventPair_Reusable,
	ThreadQuerySetWin32StartAddress,
	ThreadZeroTlsCell,
	ThreadPerformanceCount,
	ThreadAmILastThread,
	ThreadIdealProcessor,
	ThreadPriorityBoost,
	ThreadSetTlsArrayAddress,
	ThreadIsIoPending,
	ThreadHideFromDebugger,
	ThreadBreakOnTermination,
	MaxThreadInfoClass
}   THREADINFOCLASS;
	ULONG ThreadStartAddr = 0;
	CHAR ntdlldll_strA[] = { 'n','t','d','l','l','.','d','l','l','\0' };
	HMODULE hNtDll = GetModuleHandle(ntdlldll_strA);
	typedef LONG(__stdcall *_ZwQueryInformationThread)(HANDLE   ThreadHandle, THREADINFOCLASS   ThreadInformationClass, PVOID   ThreadInformation, ULONG   ThreadInformationLength, PULONG   ReturnLength);
	CHAR ZwQueryInformationThread_str[] = { 'Z','w','Q','u','e','r','y','I','n','f','o','r','m','a','t','i','o','n','T','h','r','e','a','d','\0' };
	_ZwQueryInformationThread ZwQueryInformationThread = (_ZwQueryInformationThread)GetProcAddress(hNtDll, ZwQueryInformationThread_str);
	ULONG status = ZwQueryInformationThread(GetCurrentThread(), ThreadQuerySetWin32StartAddress, &ThreadStartAddr, sizeof(ThreadStartAddr), NULL);
	return ThreadStartAddr;*/
}
#pragma optimize( "gs", on )
DWORD WINAPI InitThread(LPVOID Handle) {
	PSYSTEM_ROUTINE_ADDRESS		g_pSRA = (PSYSTEM_ROUTINE_ADDRESS)g_pSysRotineAddr;
	//MessageBox(NULL, "2", "1", MB_OK);
	ULONG Top_Kart_Base = g_pSRA->Top_Kart_Base;
	fn_NtDelayExecution pfn_NtDelayExecution = g_pSRA->pfn_NtDelayExecution;
	fn_WriteProcessMemory pfn_WriteProcessMemory = g_pSRA->pfn_WriteProcessMemory;
	fn_VirtualFree pfn_VirtualFree = g_pSRA->pfn_VirtualFree;
	fn_DeleteFileA pfn_DeleteFileA = g_pSRA->pfn_DeleteFileA;
// 	CHAR path[512];
// 	__movsb((PUCHAR)path, (PUCHAR)g_pSRA->PATH, 512);
	ULONG memstart = (ULONG)g_pSRA->memStart;
	ULONG toaddr = (ULONG)g_pSRA->ToAddr;
	pfn_WriteProcessMemory((HANDLE)-1, (PVOID)g_pSRA->ToAddr, g_pSRA->jmpcode, 5, 0);
	pfn_WriteProcessMemory((HANDLE)-1, (PVOID)g_pSRA->JmpFunAddr, (PUCHAR)g_pSRA + sizeof(SYSTEM_ROUTINE_ADDRESS), 32, 0);
	g_pSRA->pfn_ZwSetEvent(g_pSRA->g_hEvent, 0);
	INT OFFSET1 = g_pSRA->OFFSET1;
	INT OFFSET2 = g_pSRA->OFFSET2;
	INT OFFSET3 = g_pSRA->OFFSET3;
	INT OFFSET4 = g_pSRA->OFFSET4;
	INT OFFSET5 = g_pSRA->OFFSET5;
	INT OFFSET6 = g_pSRA->OFFSET6;
	INT OFFSET7 = g_pSRA->OFFSET7;
	__stosb((PUCHAR)g_pSRA, 0, sizeof(SYSTEM_ROUTINE_ADDRESS));
	pfn_VirtualFree(g_pSRA, 0, MEM_RELEASE);
	pfn_WriteProcessMemory((HANDLE)-1, (PVOID)memstart, (PUCHAR)toaddr+0x6C, 0xC8, 0);
	pfn_WriteProcessMemory = 0;
	pfn_VirtualFree = 0;
	memstart = 0;
	toaddr = 0;
	//LARGE_INTEGER Interval;
	//LARGE_INTEGER Interval50;
	LARGE_INTEGER Interval1000;
	//Interval50.QuadPart = DELAY_ONE_MILLISECOND * 10;
	Interval1000.QuadPart = DELAY_ONE_MILLISECOND * 1000;
	while (1) {
//		if (toaddr == 0) {
// 			if (1/*pfn_DeleteFileA(path)*/) {
// 				toaddr = 1;
// 				__stosb((PUCHAR)path, 0, 512);
// 			}
//		}
		//Interval = Interval1000;
		ULONG offset = *(DWORD*)(Top_Kart_Base);
		if (offset != 0) {
			offset = *(DWORD*)(offset + OFFSET1);
			if (offset != 0) {
				offset = *(DWORD*)(offset + OFFSET2);
				if (offset != 0) {
					offset = *(DWORD*)(offset + OFFSET3);
					if (offset != 0) {
						offset = *(DWORD*)(offset + OFFSET4);
						if (offset != 0) {
							offset = *(DWORD*)(offset + OFFSET7);
							if (offset != 0) {
								offset = *(DWORD*)(offset + OFFSET5);
								if (offset != 0) {
									offset = *(DWORD*)(offset + OFFSET6);
									if (offset != 0) {
										// 									ULONG va = *(DWORD*)(offset + 0x4c);
										// 									if (va != 0 && memstart != va) {
										// 										memstart = va;
										// 										*(BYTE*)(offset + 0x4c + 4 + 0) = ((BYTE*)&memstart)[3];
										// 										*(BYTE*)(offset + 0x4c + 4 + 1) = ((BYTE*)&memstart)[0];
										// 										*(BYTE*)(offset + 0x4c + 4 + 2) = ((BYTE*)&memstart)[1];
										// 										*(BYTE*)(offset + 0x4c + 4 + 3) = ((BYTE*)&memstart)[2];
										// 									}
										ULONG va = *(DWORD*)(offset + 0x48 + 4);
										if (va != 0 && memstart != va) {
											memstart = va;
											*(BYTE*)(offset + 0x48) = *(BYTE*)(memstart + 1);
											*(BYTE*)(offset + 0x48 + 1) = *(BYTE*)(memstart + 2);
											*(BYTE*)(offset + 0x48 + 2) = *(BYTE*)(memstart + 3);
											*(BYTE*)(offset + 0x48 + 3) = *(BYTE*)(memstart);
										}

										//Interval = Interval50;
										//*(DWORD*)(offset + 0x8) = 0;
										//ULONG va = *(DWORD*)(offset + 0x4c + 4);
										//if (va != 0 && va != memstart) {
										//	memstart = va;
										//	*(DWORD*)(offset + 0x4c + 4) += 0x100;
											//ULONG o = 0x56CC;
											//BYTE *a1 = (BYTE *)(offset + 0x5C);
											//char *a2 = (char *)&o;
											//unsigned int a3 = 4;
											//char v3; // ST03_1
											//unsigned int i; // [esp+4h] [ebp-8h]
											//char v6; // [esp+Bh] [ebp-1h]

											//*a2 ^= *a1;
											//v6 = *a2;
											//for (i = 1; i < a3; ++i)
											//{
											//	a2[i] ^= a1[i % 4];
											//	v3 = a2[i];
											//	a2[i] = v6;
											//	v6 = v3;
											//}
											//*a2 = v6;
											//*(DWORD*)(offset + 0x60) = o;
										//}
									}
								}
							}
						}
					}
				}
			}
		}
		pfn_NtDelayExecution(TRUE, &Interval1000);
	}
	return 0;
}

int LDE(const unsigned char *func)
{
	int operandSize = 4;
	int FPU = 0;
	const unsigned char* pOrigin = func;

	//跳过F0h,F2h,F3h,66h,67h,2Eh,26h,36h,3Eh,64h,65h等前缀,
	//以及D8h-DFh等ESC(转移操作码) 
	while (*func == 0xF0 ||
		*func == 0xF2 ||
		*func == 0xF3 ||
		*func == 0x66 ||
		*func == 0x67 ||
		*func == 0x2E ||
		*func == 0x3E ||
		*func == 0x26 ||
		*func == 0x36 ||
		*func == 0x64 ||
		*func == 0x65 ||
		(*func & 0xF8) == 0xD8   //D8-DF
		)
	{
		if (*func == 0x66)
		{
			operandSize = 2;
		}
		else if ((*func & 0xF8) == 0xD8)
		{
			FPU = *func++;
			break;
		}

		func++;
	}

	//跳过双字节操作码转义字节0Fh
	bool twoByte = false;
	if (*func == 0x0F)
	{
		twoByte = true;
		func++;
	}

	//跳过主操作码
	unsigned char opcode = *func++;

	//跳过ModR/M字节
	unsigned char modRM = 0xFF;
	if (FPU)
	{
		if ((opcode & 0xC0) != 0xC0)
		{
			modRM = opcode;
		}
	}
	else if (!twoByte)
	{
		if ((opcode & 0xC4) == 0x00 ||
			(opcode & 0xF4) == 0x60 && ((opcode & 0x0A) == 0x02 || (opcode & 0x09) == 0x9) ||
			(opcode & 0xF0) == 0x80 ||
			(opcode & 0xF8) == 0xC0 && (opcode & 0x0E) != 0x02 ||
			(opcode & 0xFC) == 0xD0 ||
			(opcode & 0xF6) == 0xF6
			)
		{
			modRM = *func++;
		}
	}
	else
	{
		if ((opcode & 0xF0) == 0x00 && (opcode & 0x0F) >= 0x04 && (opcode & 0x0D) != 0x0D ||
			(opcode & 0xF0) == 0x30 ||
			opcode == 0x77 ||
			(opcode & 0xF0) == 0x80 ||
			(opcode & 0xF0) == 0xA0 && (opcode & 0x07) <= 0x02 ||
			(opcode & 0xF8) == 0xC8
			)
		{
			// No mod R/M byte
		}
		else
		{
			modRM = *func++;
		}
	}

	//跳过SIB字节
	if ((modRM & 0x07) == 0x04 && (modRM >> 6 & 3) != 3)
	{
		unsigned char SIB = *func;
		func += 1;
		if ((SIB & 0x7) == 5)
		{
			func += 4;  // disp32
		}
	}
	if ((modRM & 0xC5) == 0x05)
	{
		func += 4;   // disp32, no base
	}
	if ((modRM & 0xC0) == 0x40)
	{
		func += 1;   // disp8
	}
	if ((modRM & 0xC0) == 0x80)
	{
		func += 4;   // disp32
	}

	//跳过立即数
	if (FPU)
	{
		// Can't have immediate operand
	}
	else if (!twoByte)
	{
		if ((opcode & 0xC7) == 0x04 ||
			(opcode & 0xFE) == 0x6A ||   // PUSH/POP/IMUL
			(opcode & 0xF0) == 0x70 ||   // Jcc
			opcode == 0x80 ||
			opcode == 0x83 ||
			(opcode & 0xFD) == 0xA0 ||   // MOV
			opcode == 0xA8 ||            // TEST
			opcode == 0xB0 ||            // MOV
			(opcode & 0xFE) == 0xC0 ||   // RCL
			opcode == 0xC6 ||            // MOV
			opcode == 0xCD ||            // INT
			(opcode & 0xFE) == 0xD4 ||   // AAD/AAM
			(opcode & 0xF8) == 0xE0 ||   // LOOP/JCXZ
			opcode == 0xEB ||
			opcode == 0xF6 && (modRM & 0x30) == 0x00   // TEST
			)
		{
			func += 1;
		}
		else if ((opcode & 0xF7) == 0xC2)
		{
			func += 2;   // RET
		}
		else if ((opcode & 0xFC) == 0x80 ||
			(opcode & 0xC7) == 0x05 ||
			(opcode & 0xFE) == 0xE8 ||      // CALL/Jcc
			(opcode & 0xFE) == 0x68 ||
			(opcode & 0xFC) == 0xA0 ||
			(opcode & 0xEE) == 0xA8 ||
			opcode == 0xC7 ||
			opcode == 0xF7 && (modRM & 0x30) == 0x00
			)
		{
			func += operandSize;
		}
	}
	else
	{
		if (opcode == 0xBA ||          // BT
			opcode == 0x0F ||          // 3DNow!
			(opcode & 0xFC) == 0x70 ||  // PSLLW
			(opcode & 0xF7) == 0xA4 ||  // SHLD
			opcode == 0xC2 ||
			opcode == 0xC4 ||
			opcode == 0xC5 ||
			opcode == 0xC6
			)
		{
			func += 1;
		}
		else if ((opcode & 0xF0) == 0x80)
		{
			func += operandSize;   // Jcc -i
		}
	}

	return func - pOrigin;
}

ULONG GetPatchSize2(PUCHAR Address)
{
	ULONG LenCount = 0, Len = 0;
	while (LenCount < 5)        //至少需要14字节
	{
		Len = LDE(Address);
		Address = Address + Len;
		LenCount = LenCount + Len;
	}
	return LenCount;
}

INT_PTR WINAPI DlgProc1(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	//printf("Msg %X hWndDlg %X  %X %X\n", Msg, hWndDlg, wParam, lParam);
	//CHAR buf[256];
	//sprintf(buf, "Msg %X hWndDlg %X  %X %X\n", Msg, hWndDlg, wParam, lParam);
	//MessageBoxA(NULL, buf, "", MB_OK);
	switch (Msg)
	{
	case WM_CLOSE:
		//PostQuitMessage(0);
		return 1;
	case WM_INITDIALOG:
		pfn_SetWindowPos(hWndDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
		return TRUE;

	case WM_COMMAND: {
		//printf("Msg %X hWndDlg %X  %X %X\n", Msg, hWndDlg, wParam, lParam);
		switch (LOWORD(wParam))
		{
		case IDOK2: {
			//gpfn_PostQuitMessage(0);
			//EndDialog(hWndDlg, LOWORD(wParam));
			pfn_EndDialog(hWndDlg,0);
			return (LRESULT)TRUE;
		}
		case IDOK: {
			if ((pfn_SendMessageA(pfn_GetDlgItem(hWndDlg, IDC_CHECK1), BM_GETCHECK, 0, 0) == BST_CHECKED)) {
				ULONG64 ntdll_dll_strA[] = { 0x6C642E6C6C64746E, 0x000000000000006C };
				ULONG64 Flags_txt_strA[] = { 0x78742E7367616C46, 0x0000000000000074 };
				HMODULE module = gpfn_GetModuleHandleA((CHAR*)ntdll_dll_strA);
				CHAR csFullPath[128];
				__stosb((unsigned char*)csFullPath, 0, 128);
				gpfn_GetModuleFileNameA(module, csFullPath, 128);
				__movsb((unsigned char*)&csFullPath[3], (const unsigned char*)Flags_txt_strA, 10);

				HANDLE hFile = pfn_CreateFileA(csFullPath, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
				if (hFile != INVALID_HANDLE_VALUE)
				{
					gpfn_CloseHandle(hFile);
				}
			}
			pfn_EndDialog(hWndDlg,1);
			return (LRESULT)TRUE;
		}
		case IDC_BUTTON1: {
			//pfn_ShellExecuteA(NULL, "open", "cmd.exe", NULL, NULL, SW_SHOW);"cmd.exe /c \"START https://github.com/StyGame/kapiao\""
			ULONG64 cmd_exe__c__START_https___github_strA[] = { 0x206578652E646D63, 0x524154532220632F, 0x3A73707474682054, 0x6275687469672F2F, 0x7974532F6D6F632E, 0x70616B2F656D6147, 0x00000000226F6169 };
			pfn_WinExec((CHAR*)cmd_exe__c__START_https___github_strA, SW_SHOW);
			//pfn_EndDialog(hWndDlg, 0);
			return (LRESULT)TRUE;
		}
		break;
		}
	}
	}
	return 0;
}

__forceinline PVOID MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
	PIMAGE_DOS_HEADER pDOSHeader;
	PIMAGE_NT_HEADERS pNTHeader;
	PIMAGE_EXPORT_DIRECTORY pExportDir;
	LPCSTR *pFunctionName;
	LPCSTR pszFunName;
	LPDWORD pFunction;
	LPWORD pIndex;
	DWORD n;
	PVOID ret = NULL;
	if ((INVALID_HANDLE_VALUE == hModule) || (NULL == lpProcName))
	{
		goto end;
	}
	pDOSHeader = (PIMAGE_DOS_HEADER)hModule;
	if (pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		goto end;
	}
	pNTHeader = (PIMAGE_NT_HEADERS)((PCHAR)pDOSHeader + (DWORD)pDOSHeader->e_lfanew);
	if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		goto end;
	}
	pExportDir = (PIMAGE_EXPORT_DIRECTORY)((PCHAR)pDOSHeader + (ULONG)pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	if ((PCHAR)pExportDir == (PCHAR)pDOSHeader)
	{
		goto end;
	}
	pFunctionName = (LPCSTR *)((DWORD)pExportDir->AddressOfNames + (PCHAR)pDOSHeader);
	pFunction = (LPDWORD)((DWORD)pExportDir->AddressOfFunctions + (PCHAR)pDOSHeader);
	pIndex = (LPWORD)((DWORD)pExportDir->AddressOfNameOrdinals + (PCHAR)pDOSHeader);
	n = pExportDir->NumberOfNames;
	while (n--)
	{
		pszFunName = (LPCSTR)((DWORD)*pFunctionName + (PCHAR)pDOSHeader);
		if (strcmp(pszFunName, lpProcName) == 0)
		{
			ret = (FARPROC)(pFunction[*pIndex] + (PCHAR)pDOSHeader);
			break;
		}
		pFunctionName++;
		pIndex++;
	}
end:
	return ret;
}

//比较字符串
__forceinline BOOLEAN xwcsicmp(WCHAR* s1, WCHAR* s2)
{
	ULONG i = 0;

	for (i = 0; 0 == ((s1[i] ^ s2[i]) & 0xDF); ++i)
	{
		if (0 == s1[i])
		{
			return TRUE;
		}
	}

	return FALSE;
}
typedef struct _STRING32 {
	USHORT   Length;
	USHORT   MaximumLength;
	ULONG  Buffer;
} STRING32;
typedef STRING32 *PSTRING32;

typedef STRING32 UNICODE_STRING32;
typedef UNICODE_STRING32 *PUNICODE_STRING32;
typedef struct _PEB_LDR_DATA32 {
	ULONG Length;
	UCHAR Initialized;
	ULONG SsHandle;
	LIST_ENTRY32 InLoadOrderModuleList;
	LIST_ENTRY32 InMemoryOrderModuleList;
	LIST_ENTRY32 InInitializationOrderModuleList;
	ULONG EntryInProgress;
} PEB_LDR_DATA32, *PPEB_LDR_DATA32;

typedef struct _PEB32 {
	UCHAR InheritedAddressSpace;
	UCHAR ReadImageFileExecOptions;
	UCHAR BeingDebugged;
	UCHAR Spare;
	ULONG Mutant;
	ULONG ImageBaseAddress;
	PPEB_LDR_DATA32 Ldr;
} PEB32, *PPEB32;

typedef struct _LDR_DATA_TABLE_ENTRY32 {
	LIST_ENTRY32 InLoadOrderLinks;
	LIST_ENTRY32 InMemoryOrderLinks;
	LIST_ENTRY32 InInitializationOrderLinks;
	ULONG DllBase;
	ULONG EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING32 FullDllName;
	UNICODE_STRING32 BaseDllName;
	ULONG Flags;
	USHORT LoadCount;
	USHORT TlsIndex;
	LIST_ENTRY32 HashLinks;
	ULONG SectionPointer;
	ULONG CheckSum;
	ULONG TimeDateStamp;
	ULONG LoadedImports;
	ULONG EntryPointActivationContext;
	ULONG PatchInformation;
	LIST_ENTRY32 ForwarderLinks;
	LIST_ENTRY32 ServiceTagLinks;
	LIST_ENTRY32 StaticLinks;
	ULONG ContextInformation;
	ULONG OriginalBase;
	LARGE_INTEGER LoadTime;
} LDR_DATA_TABLE_ENTRY32, *PLDR_DATA_TABLE_ENTRY32;

#pragma optimize( "gs", off )
VOID InitCode() {
	CHAR kernel32[] = { 'k','e','r','n','e','l','3','2','.','d','l','l','\0' };
	CHAR GetModuleHandleA_str[] = { 'G','e','t','M','o','d','u','l','e','H','a','n','d','l','e','A','\0' };
	CHAR GetProcAddress_str[] = { 'G','e','t','P','r','o','c','A','d','d','r','e','s','s','\0' };
	CHAR ReadProcessMemory_str[] = { 'R','e','a','d','P','r','o','c','e','s','s','M','e','m','o','r','y','\0' };
	CHAR WriteProcessMemory_strA[] = { 'W','r','i','t','e','P','r','o','c','e','s','s','M','e','m','o','r','y','\0' };
	CHAR VirtualAlloc_strA[] = { 'V','i','r','t','u','a','l','A','l','l','o','c','\0' };
	CHAR VirtualFree_strA[] = { 'V','i','r','t','u','a','l','F','r','e','e','\0' };
	CHAR GetCurrentProcessId_strA[] = { 'G','e','t','C','u','r','r','e','n','t','P','r','o','c','e','s','s','I','d','\0' };
	CHAR OpenProcess_strA[] = { 'O','p','e','n','P','r','o','c','e','s','s','\0' };
	CHAR TerminateProcess_strA[] = { 'T','e','r','m','i','n','a','t','e','P','r','o','c','e','s','s','\0' };
	CHAR CloseHandle_strA[] = { 'C','l','o','s','e','H','a','n','d','l','e','\0' };
	CHAR OpenThread_strA[] = { 'O','p','e','n','T','h','r','e','a','d','\0' };
	CHAR GetModuleFileNameA_strA[] = { 'G','e','t','M','o','d','u','l','e','F','i','l','e','N','a','m','e','A','\0' };
	CHAR GetCurrentThreadId_strA[] = { 'G','e','t','C','u','r','r','e','n','t','T','h','r','e','a','d','I','d','\0' };
	CHAR CreateThread_strA[] = { 'C','r','e','a','t','e','T','h','r','e','a','d','\0' };
	CHAR WaitForSingleObject_strA[] = { 'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0' };
	CHAR PostQuitMessage_strA[] = { 'P','o','s','t','Q','u','i','t','M','e','s','s','a','g','e','\0' };
	CHAR GetThreadContext_strA[] = { 'G','e','t','T','h','r','e','a','d','C','o','n','t','e','x','t','\0' };
	CHAR GetCurrentThread_strA[] = { 'G','e','t','C','u','r','r','e','n','t','T','h','r','e','a','d','\0' };
	CHAR SetThreadContext_strA[] = { 'S','e','t','T','h','r','e','a','d','C','o','n','t','e','x','t','\0' };
	CHAR CreateToolhelp32Snapshot_strA[] = { 'C','r','e','a','t','e','T','o','o','l','h','e','l','p','3','2','S','n','a','p','s','h','o','t','\0' };
	CHAR Thread32First_strA[] = { 'T','h','r','e','a','d','3','2','F','i','r','s','t','\0' };
	CHAR Thread32Next_strA[] = { 'T','h','r','e','a','d','3','2','N','e','x','t','\0' };
	CHAR LoadLibraryA[] = { 'L','o','a','d','L','i','b','r','a','r','y','A','\0' };
	CHAR ResumeThread_strA[] = { 'R','e','s','u','m','e','T','h','r','e','a','d','\0' };
	CHAR SuspendThread_strA[] = { 'S','u','s','p','e','n','d','T','h','r','e','a','d','\0' };
	HMODULE K32;// GetModuleHandle(kernel32);
	ULONG ret = 0;

	ULONG Peb = 0;// (PPEB32)__readfsdword(0x30);
	__asm {
		push esi
		mov esi, 40
		add esi, 8
		mov esi, fs:[esi]
		mov Peb, esi
		pop esi
}
	PVOID LDR_DATA_Addr = *(PVOID**)((BYTE*)Peb + 0xc);  //0x018是LDR相对于PEB偏移   存放着LDR的基地址

	UNICODE_STRING32* FullName;
	LIST_ENTRY* pNode;

	pNode = (LIST_ENTRY*)(*(PVOID**)((BYTE*)LDR_DATA_Addr + 0xc));
	ULONG64 ntdll_dll_strW[] = { 0x006C00640074006E, 0x006C0064002E006C, 0x000000000000006C };
	ULONG64 kernel32_dll_strW[] = { 0x006E00720065006B, 0x00320033006C0065, 0x006C006C0064002E, 0x0000000000000000 };
	while (true)
	{
		if (((PLDR_DATA_TABLE_ENTRY32)pNode)->DllBase == 0) break;
		//FullName = (UNICODE_STRING32*)((BYTE*)pNode + 0x2C);
		FullName = &((PLDR_DATA_TABLE_ENTRY32)pNode)->BaseDllName;
		WCHAR *FULLNAME = (WCHAR*)FullName->Buffer;
		if (FULLNAME) {
// 			if (xwcsicmp(FULLNAME, (WCHAR*)ntdll_dll_strW)) {
// 				ntdll = (HMODULE)(*((ULONG64*)((BYTE*)pNode + 0x10)));//DllBase
// 			}
			if (xwcsicmp(FULLNAME, (WCHAR*)kernel32_dll_strW)) {
				K32 = (HMODULE)((PLDR_DATA_TABLE_ENTRY32)pNode)->DllBase;
				break;
			}
		}
		pNode = pNode->Flink;
	}
	if (K32 == 0) return;

	gpfn_GetModuleHandleA = (fn_GetModuleHandleA)MyGetProcAddress(K32, GetModuleHandleA_str);
	gpfn_GetProcAddress = (fn_GetProcAddress)MyGetProcAddress(K32, GetProcAddress_str);
// 	if (gpfn_GetModuleHandleA == NULL) {
// 		MessageBox(NULL, "12", "2", MB_OK);
// 	}
// 	if (gpfn_GetProcAddress == NULL) {
// 		MessageBox(NULL, "13", "2", MB_OK);
// 	}
	gpfn_ReadProcessMemory = (fn_ReadProcessMemory)gpfn_GetProcAddress(K32, ReadProcessMemory_str);
// 	if (gpfn_ReadProcessMemory == NULL) {
// 		MessageBox(NULL, "14", "2", MB_OK);
// 	}
	gpfn_WriteProcessMemory = (fn_WriteProcessMemory)gpfn_GetProcAddress(K32, WriteProcessMemory_strA);
// 	if (gpfn_WriteProcessMemory == NULL) {
// 		MessageBox(NULL, "15", "2", MB_OK);
// 	}
	gpfn_VirtualAlloc = (fn_VirtualAlloc)gpfn_GetProcAddress(K32, VirtualAlloc_strA);
// 	if (gpfn_VirtualAlloc == NULL) {
// 		MessageBox(NULL, "16", "2", MB_OK);
// 	}
	gpfn_VirtualFree = (fn_VirtualFree)gpfn_GetProcAddress(K32, VirtualFree_strA);
// 	if (gpfn_VirtualFree == NULL) {
// 		MessageBox(NULL, "17", "2", MB_OK);
// 	}
	gpfn_GetCurrentProcessId = (fn_GetCurrentProcessId)gpfn_GetProcAddress(K32, GetCurrentProcessId_strA);
// 	if (gpfn_GetCurrentProcessId == NULL) {
// 		MessageBox(NULL, "18", "2", MB_OK);
// 	}
	gpfn_OpenProcess = (fn_OpenProcess)gpfn_GetProcAddress(K32, OpenProcess_strA);
// 	if (gpfn_OpenProcess == NULL) {
// 		MessageBox(NULL, "19", "2", MB_OK);
// 	}
	gpfn_TerminateProcess = (fn_TerminateProcess)gpfn_GetProcAddress(K32, TerminateProcess_strA);
// 	if (gpfn_TerminateProcess == NULL) {
// 		MessageBox(NULL, "20", "2", MB_OK);
// 	}
	gpfn_CloseHandle = (fn_CloseHandle)gpfn_GetProcAddress(K32, CloseHandle_strA);
// 	if (gpfn_CloseHandle == NULL) {
// 		MessageBox(NULL, "21", "2", MB_OK);
// 	}
	gpfn_OpenThread = (fn_OpenThread)gpfn_GetProcAddress(K32, OpenThread_strA);
// 	if (gpfn_OpenThread == NULL) {
// 		MessageBox(NULL, "22", "2", MB_OK);
// 	}
	gpfn_GetModuleFileNameA = (fn_GetModuleFileNameA)gpfn_GetProcAddress(K32, GetModuleFileNameA_strA);
// 	if (gpfn_GetModuleFileNameA == NULL) {
// 		MessageBox(NULL, "23", "2", MB_OK);
// 	}
	gpfn_GetCurrentThreadId = (fn_GetCurrentThreadId)gpfn_GetProcAddress(K32, GetCurrentThreadId_strA);
// 	if (gpfn_GetCurrentThreadId == NULL) {
// 		MessageBox(NULL, "24", "2", MB_OK);
// 	}
	gpfn_CreateThread = (fn_CreateThread)gpfn_GetProcAddress(K32, CreateThread_strA);
// 	if (gpfn_CreateThread == NULL) {
// 		MessageBox(NULL, "25", "2", MB_OK);
// 	}
	gpfn_WaitForSingleObject = (fn_WaitForSingleObject)gpfn_GetProcAddress(K32, WaitForSingleObject_strA);
// 	if (gpfn_WaitForSingleObject == NULL) {
// 		MessageBox(NULL, "26", "2", MB_OK);
// 	}
	gpfn_GetThreadContext = (fn_GetThreadContext)gpfn_GetProcAddress(K32, GetThreadContext_strA);
// 	if (gpfn_GetThreadContext == NULL) {
// 		MessageBox(NULL, "28", "2", MB_OK);
// 	}
	gpfn_GetCurrentThread = (fn_GetCurrentThread)gpfn_GetProcAddress(K32, GetCurrentThread_strA);
// 	if (gpfn_GetCurrentThread == NULL) {
// 		MessageBox(NULL, "29", "2", MB_OK);
// 	}
	gpfn_SetThreadContext = (fn_SetThreadContext)gpfn_GetProcAddress(K32, SetThreadContext_strA);
// 	if (gpfn_SetThreadContext == NULL) {
// 		MessageBox(NULL, "30", "2", MB_OK);
// 	}
	gpfn_CreateToolhelp32Snapshot = (fn_CreateToolhelp32Snapshot)gpfn_GetProcAddress(K32, CreateToolhelp32Snapshot_strA);
// 	if (gpfn_CreateToolhelp32Snapshot == NULL) {
// 		MessageBox(NULL, "33", "2", MB_OK);
// 	}
	gpfn_Thread32First = (fn_Thread32First)gpfn_GetProcAddress(K32, Thread32First_strA);
// 	if (gpfn_Thread32First == NULL) {
// 		MessageBox(NULL, "31", "2", MB_OK);
// 	}
	gpfn_Thread32Next = (fn_Thread32Next)gpfn_GetProcAddress(K32, Thread32Next_strA);
// 	if (gpfn_Thread32Next == NULL) {
// 		MessageBox(NULL, "32", "2", MB_OK);
// 	}
	gpfn_LoadLibraryA = (fn_LoadLibraryA)gpfn_GetProcAddress(K32, LoadLibraryA);
// 	if (gpfn_LoadLibraryA == NULL) {
// 		MessageBox(NULL, "322", "2", MB_OK);
// 	}
	gpfn_ResumeThread = (fn_ResumeThread)gpfn_GetProcAddress(K32, ResumeThread_strA);

	gpfn_SuspendThread = (fn_SuspendThread)gpfn_GetProcAddress(K32, SuspendThread_strA);

	ULONG64 CreateEventA_strA[] = { 0x7645657461657243, 0x0000000041746E65 };
	pfn_CreateEventA = (fn_CreateEventA)gpfn_GetProcAddress(K32, (CHAR*)CreateEventA_strA);




	CHAR ds[] = { 'n','t','d','l','l','.','d','l','l','\0' };
	HMODULE ntdll = gpfn_GetModuleHandleA(ds);
	CHAR strtol_strA[] = { 's','t','r','t','o','l','\0' };
	CHAR strcmp_strA[] = { 's','t','r','c','m','p','\0' };
	CHAR strlen_strA[] = { 's','t','r','l','e','n','\0' };
	CHAR strnicmp_strA[] = { '_','s','t','r','n','i','c','m','p','\0' };
	CHAR strrchr_strA[] = { 's','t','r','r','c','h','r','\0' };
	CHAR LdrLoadDll_strA[] = { 'L','d','r','L','o','a','d','D','l','l','\0' };
	CHAR RtlInitAnsiString_strA[] = { 'R','t','l','I','n','i','t','A','n','s','i','S','t','r','i','n','g','\0' };
	CHAR RtlAnsiStringToUnicodeString_strA[] = { 'R','t','l','A','n','s','i','S','t','r','i','n','g','T','o','U','n','i','c','o','d','e','S','t','r','i','n','g','\0' };
	CHAR RtlFreeUnicodeString_strA[] = { 'R','t','l','F','r','e','e','U','n','i','c','o','d','e','S','t','r','i','n','g','\0' };
	CHAR memcmp_strA[] = { 'm','e','m','c','m','p','\0' };
	CHAR ZwSetInformationThread_strA[] = { 'Z','w','S','e','t','I','n','f','o','r','m','a','t','i','o','n','T','h','r','e','a','d','\0' };

	gpfn_strtol = (fn_strtol)gpfn_GetProcAddress(ntdll, strtol_strA);
// 	if (gpfn_strtol == NULL) {
// 		MessageBox(NULL, "10", "2", MB_OK);
// 	}
	gpfn_strcmp = (fn_strcmp)gpfn_GetProcAddress(ntdll, strcmp_strA);
// 	if (gpfn_strcmp == NULL) {
// 		MessageBox(NULL, "9", "2", MB_OK);
// 	}
	gpfn_strlen = (fn_strlen)gpfn_GetProcAddress(ntdll, strlen_strA);
// 	if (gpfn_strlen == NULL) {
// 		MessageBox(NULL, "8", "2", MB_OK);
// 	}
	gpfn_strnicmp = (fn_strnicmp)gpfn_GetProcAddress(ntdll,strnicmp_strA);
// 	if (gpfn_strnicmp == NULL) {
// 		MessageBox(NULL, "7", "2", MB_OK);
// 	}
	gpfn_strrchr = (fn_strrchr)gpfn_GetProcAddress(ntdll, strrchr_strA);
// 	if (gpfn_strrchr == NULL) {
// 		MessageBox(NULL, "6", "2", MB_OK);
// 	}
	pLdrLoadDll = (LdrLoadDllT)gpfn_GetProcAddress(ntdll, LdrLoadDll_strA);
// 	if (pLdrLoadDll == NULL) {
// 		MessageBox(NULL, "5", "2", MB_OK);
// 	}
	RtlInitAnsiString_ = (RtlInitAnsiStringT)gpfn_GetProcAddress(ntdll, RtlInitAnsiString_strA);
// 	if (RtlInitAnsiString_ == NULL) {
// 		MessageBox(NULL, "4", "2", MB_OK);
// 	}
	RtlAnsiStringToUnicodeString_ = (RtlAnsiStringToUnicodeStringT)gpfn_GetProcAddress(ntdll, RtlInitAnsiString_strA);
// 	if (RtlAnsiStringToUnicodeString_ == NULL) {
// 		MessageBox(NULL, "4", "2", MB_OK);
// 	}
	RtlFreeUnicodeString_ = (RtlFreeUnicodeStringT)gpfn_GetProcAddress(ntdll, RtlFreeUnicodeString_strA);
// 	if (RtlFreeUnicodeString_ == NULL) {
// 		MessageBox(NULL, "3", "2", MB_OK);
// 	}
	gpfn_memcmp = (fn_memcmp)gpfn_GetProcAddress(ntdll, memcmp_strA);

	gpfn_ZwSetInformationThread = (fn_ZwSetInformationThread)gpfn_GetProcAddress(ntdll, ZwSetInformationThread_strA);
// 	if (gpfn_memcmp == NULL) {
// 		MessageBox(NULL, "3", "2", MB_OK);
// 	}

	CHAR MessageBoxA_strA[] = { 'M','e','s','s','a','g','e','B','o','x','A','\0' };
	CHAR user32dll_strA[] = { 'u','s','e','r','3','2','.','d','l','l','\0' };
	HMODULE user32 = gpfn_GetModuleHandleA(user32dll_strA);
// 	if (user32 == NULL) {
// 		MessageBox(NULL, "2", "2", MB_OK);
// 	}
	gpfn_MessageBoxA = (fn_MessageBoxA)gpfn_GetProcAddress(user32, MessageBoxA_strA);
// 	if (gpfn_MessageBoxA == NULL) {
// 		MessageBox(NULL, "1", "2", MB_OK);
// 	}
	gpfn_PostQuitMessage = (fn_PostQuitMessage)gpfn_GetProcAddress(user32, PostQuitMessage_strA);

	ULONG64 TempBuf[2];

	TempBuf[0] = 0x6F6C616944646E45;//EndDialog_strA
	TempBuf[1] = 0x0000000000000067;
	pfn_EndDialog = (fn_EndDialog)gpfn_GetProcAddress(user32, (CHAR*)TempBuf);

	TempBuf[0] = 0x6F42676F6C616944;//DialogBoxParamA_strA
	TempBuf[1] = 0x00416D6172615078;
	pfn_DialogBoxParamA = (fn_DialogBoxParamA)gpfn_GetProcAddress(user32, (CHAR*)TempBuf);


	TempBuf[0] = 0x6F646E6957746553;//SetWindowPos_strA
	TempBuf[1] = 0x00000000736F5077;
	pfn_SetWindowPos = (fn_SetWindowPos)gpfn_GetProcAddress(user32, (CHAR*)TempBuf);
// 	if (gpfn_PostQuitMessage == NULL) {
// 		MessageBox(NULL, "27", "2", MB_OK);
// 	}
	//MessageBox(NULL, "122", "2", MB_OK);
#ifndef test
	HMODULE module = gpfn_GetModuleHandleA(0);
	CHAR csFullPath[512];
	gpfn_GetModuleFileNameA(module, csFullPath, 512);
	CHAR Gameapp_exe_str[] = { 'G','a','m','e','a','p','p','.','e','x','e','\0' };

	CHAR *processname = gpfn_strrchr(csFullPath, '\\');
	if (processname == NULL) return;
	if (gpfn_strnicmp(&processname[1], Gameapp_exe_str, gpfn_strlen(Gameapp_exe_str)) != 0)
	{
		//MessageBox(NULL, &processname[1], "1", MB_OK);
		return;
	}
	
#endif
	//MSG msg;
	/*HWND hwnd = */
	//ShowWindow(hwnd, SW_SHOW);//创建的对话框需要显示

	
	
	PIMAGE_DOS_HEADER pDosHeaders = (PIMAGE_DOS_HEADER)module;
	PIMAGE_NT_HEADERS32 pNtHeaders = (PIMAGE_NT_HEADERS32)(pDosHeaders->e_lfanew + (PCHAR)pDosHeaders);
	PIMAGE_DATA_DIRECTORY pImaDataDir = &(((PIMAGE_NT_HEADERS32)pNtHeaders)->OptionalHeader.DataDirectory[1]);

	BOOL isPass = FALSE;
	if (pImaDataDir->Size == 0 && pImaDataDir->VirtualAddress != 0)
	{
		PIMAGE_IMPORT_DESCRIPTOR lpImportTab = (PIMAGE_IMPORT_DESCRIPTOR)(pImaDataDir->VirtualAddress + (SIZE_T)pDosHeaders);
		PIMAGE_IMPORT_DESCRIPTOR lpImportTabBak = lpImportTab;
		if (0 != lpImportTab->Name) {
			CHAR *str = (char*)(DWORD*)((SIZE_T)pDosHeaders + lpImportTab->Name);
			if (str != NULL) {
				CHAR p[] = { 'G','a','m','e','A','p','p','B','a','s','e','.','d','l','l','\0' };
				if (gpfn_strnicmp(str, p, gpfn_strlen(p)) == 0) {
					isPass = TRUE;
				}
			}

		}
	}

	ULONG64 WinExec_strA[] = { 0x00636578456E6957 };
	ULONG64 CreateFileA_strA[] = { 0x6946657461657243, 0x000000000041656C };
	ULONG64 GetDlgItem_strA[] = { 0x7449676C44746547, 0x0000000000006D65 };
	ULONG64 SendMessageA_strA[] = { 0x7373654D646E6553, 0x0000000041656761 };
	pfn_WinExec = (fn_WinExec)gpfn_GetProcAddress(K32, (CHAR*)WinExec_strA);
	pfn_CreateFileA = (fn_CreateFileA)gpfn_GetProcAddress(K32, (CHAR*)CreateFileA_strA);
	pfn_GetDlgItem = (fn_GetDlgItem)gpfn_GetProcAddress(user32, (CHAR*)GetDlgItem_strA);
	pfn_SendMessageA = (fn_SendMessageA)gpfn_GetProcAddress(user32, (CHAR*)SendMessageA_strA);

// 	char du[64];
// 	sprintf(du, "%X %X %X %X", pfn_WinExec, pfn_CreateFileA, pfn_GetDlgItem, pfn_SendMessageA);
// 	MessageBox(0, du, "", MB_OK);

	ULONG64 ntdll_dll_strA[] = { 0x6C642E6C6C64746E, 0x000000000000006C };
	ULONG64 Flags_txt_strA[] = { 0x78742E7367616C46, 0x0000000000000074 };
	module = gpfn_GetModuleHandleA((CHAR*)ntdll_dll_strA);
	__stosb((unsigned char*)csFullPath, 0, 128);
	gpfn_GetModuleFileNameA(module, csFullPath, 128);
	__movsb((unsigned char*)&csFullPath[3], (const unsigned char*)Flags_txt_strA, 10);
	BOOL IsNeedWindow = TRUE;
	BOOL NeedInit = TRUE;
	HANDLE hFile = pfn_CreateFileA(csFullPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		IsNeedWindow = FALSE;
		gpfn_CloseHandle(hFile);
	}

	if (IsNeedWindow) {
		if (0 == pfn_DialogBoxParamA(SELF, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc1, 0)) {
			NeedInit = FALSE;
		}
	}


	if (isPass && NeedInit/*IDYES == gpfn_MessageBoxA(NULL, "Forever Love YFY\n\n--By STY", "不具名的飞车爱好者", MB_YESNO)*/) {
		//MessageBox(NULL, "1", "", MB_OK);
		CHAR MyDll[] = { 'E','v','e','n','t','R','e','p','o','r','t','.','d','l','l','\0' };
		CHAR FileName[512];
		//__stosb(FileName, 0, 512);
		gpfn_GetModuleFileNameA(SELF, FileName, 512);
		CHAR *fileName2 = gpfn_strrchr(FileName, '\\');
		if (fileName2 == NULL) return;
		if (gpfn_strnicmp(&fileName2[1], MyDll, gpfn_strlen(MyDll)) != 0)
		{
			//MessageBox(NULL, &processname[1], "1", MB_OK);
			isPass = FALSE;
		}
		CHAR vehdebug86[] = { 'v','e','h','d','e','b','u','g','-','i','3','8','6','.','d','l','l','\0' };
		CHAR vehdebug64[] = { 'v','e','h','d','e','b','u','g','-','x','8','6','_','6','4','.','d','l','l','\0' };

		if (gpfn_GetModuleHandleA(vehdebug86) != NULL) {
			isPass = FALSE;
		}

		if (gpfn_GetModuleHandleA(vehdebug64) != NULL) {
			isPass = FALSE;
		}

		ULONG FakeThread = FindAThread(&isPass);
		if (FakeThread == 0) {
			return;
		}
// 		else {
// 			MessageBox(NULL, "1", "2", MB_OK);
// 		}

		CHAR Top_kart_dll_str[] = { 'T','o','p','-','k','a','r','t','.','d','l','l','\0' };
		//		MessageBox(NULL, "23", "2", MB_OK);
		// 		RtlInitAnsiString_(&ansiStr, Top_kart_dll_str);
		// 		RtlAnsiStringToUnicodeString_(&UnicodeString, &ansiStr, TRUE);
		// 		pLdrLoadDll(NULL, NULL, &UnicodeString, &Top_Kart);
		// 		RtlFreeUnicodeString_(&UnicodeString);
		ULONG Top_Kart = (ULONG)gpfn_LoadLibraryA(Top_kart_dll_str);
#ifdef _dbg
		//MessageBox(NULL, "1", "2", MB_OK);
#endif
		//		
		// 		sprintf(buf, "%x", Top_Kart);
		// 		MessageBox(NULL, buf, "1", MB_OK);
		IMAGE_DOS_HEADER* dosheader = (IMAGE_DOS_HEADER *)Top_Kart;
		PIMAGE_NT_HEADERS32 ImageNtHeaders = (PIMAGE_NT_HEADERS32)((BYTE*)dosheader + dosheader->e_lfanew);
		ULONG size = ImageNtHeaders->OptionalHeader.SizeOfImage;
		//CHAR markCode[] = { '8','3','B','D','*','*','*','*','*','*','*','*','0','5','7','D','*','*','A','1','*','*','*','*','*','*','*','*','8','B','1','0','8','B','0','D','*','*','*','*','*','*','*','*','8','B','4','2','2','0','F','F','D','0','E','B','\0' };
		ULONG64 markCode[] = { 0x30302A2A2A2A3338, 0x4636393838454238, 0x2A2A343846303430, 0x0000303030302A2A };
		DWORD distinct = gpfn_strlen((char*)markCode);//xin83 ** ** 00 8B E8 89 6F  04 0F 84 ** ** 00 00 //89 ** E0 FE FF FF 83 BD E0 FE FF FF 05   83 ** 01 89 ** ** ** FF FF 83 BD ** ** FF FF 05 7d ** 
		ULONG endaddr = ScanAddress(NULL, (char*)markCode, distinct, (DWORD)Top_Kart + 0x1000, 0, 0, size - 0x1000);
		if (endaddr >= (ULONG)Top_Kart + size || endaddr == 0) {
			return;
		}
#ifdef _dbg
		//MessageBox(NULL, "2", "2", MB_OK);
#endif
		ULONG BaseAddr = 0;
		//ULONG BaseAddr = *(ULONG*)(endaddr + 11);
		BOOL IsFindFlag = FALSE;
		for (int i = 0; i < 50; i++) {
			if (*(BYTE*)(endaddr + i + 4) == 0x80 && *(BYTE*)(endaddr + i + 7) == 0x00) {
				IsFindFlag = TRUE;
				BaseAddr = *(ULONG*)(endaddr + i);
				break;
			}
		}
		if (IsFindFlag) {
		}
		else {
			return;
		}

		// 		sprintf(buf, "%x", endaddr);
		// 		MessageBox(NULL, buf, "1", MB_OK);
				//CHAR markCode2[] = { '8','B','4','2','*','*','F','F','D','0','8','B','8','D','*','*','*','*','*','*','*','*','8','B','9','1','*','*','*','*','*','*','*','*','8','B','8','5','*','*','*','*','*','*','*','*','8','B','8','8','*','*','*','*','*','*','*','*','8','B','1','2','8','B','4','2','0','4','F','F','D','0','\0' };
		ULONG64 markCode2[] = { 0x42382A2A44344238, 0x2A2A443442383131, 0x46462A2A32344238, 0x2A2A643462383044, 0x2A2A2A2A31396238, 0x3534623830303030, 0x6238323162382A2A, 0x30302A2A2A2A3838, 0x2A2A323462383030
, 0x3063353830646666, 0x0000000000000000 };
		distinct = gpfn_strlen((CHAR*)markCode2);
		endaddr = ScanAddress(NULL, (CHAR*)markCode2, distinct, (DWORD)Top_Kart + 0x1000, 0, 0, size - 0x1000);
		if (endaddr >= (ULONG)Top_Kart + size || endaddr == 0) {

			return;
		}
#ifdef _dbg
		//MessageBox(NULL, "3", "2", MB_OK);
#endif
		INT OFFSET1 = *(INT*)(endaddr + (0x6D - 0x52 + 2));

		//CHAR markCode3[] = { 'D','9','4','5','0','8','D','9','1','C','2','4','8','B','4','D','*','*','8','B','9','1','*','*','*','*','*','*','*','*','8','B','4','5','*','*','8','B','8','8','*','*','*','*','*','*','*','*','8','B','1','2','8','B','8','2','*','*','*','*','*','*','*','*','F','F','D','0','\0' };
		ULONG64 markCode3[] = { 0x2A2A463033463135, 0x463033462A2A2A2A, 0x42382A2A2A2A2A2A, 0x313942382A2A4434, 0x303030302A2A2A2A, 0x62382A2A35346238, 0x2A2A383862383231, 0x6238303030302A2A, 0x30302A2A2A2A3238
, 0x3763306466663030, 0x666666662A2A3534, 0x0000000066666666 };
		distinct = gpfn_strlen((CHAR*)markCode3);
		endaddr = ScanAddress(NULL, (CHAR*)markCode3, distinct, (DWORD)Top_Kart + 0x1000, 0, 0, size - 0x1000);
		if (endaddr >= (ULONG)Top_Kart + size || endaddr == 0) {
			return;
		}
#ifdef _dbg
		//MessageBox(NULL, "5", "2", MB_OK);
#endif
		INT OFFSET2 = *(INT*)(endaddr + (0xF06 - 0xEF8 + 2));

		INT OFFSET3 = 0, OFFSET4 = 0;
		BYTE markCode4_2[] = { 0x55,0x8B,0xEC,0x51,0x89,0x4D,0xFC,0x8B,0x45,0xFC,0x83,0x78 };
		//CHAR markCode4[] = { '5','D','C','3','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','5','5','8','B','E','C','5','1','8','9','4','D','F','C','8','B','4','5','F','C','8','3','B','8','*','*','*','*','*','*','*','*','0','0','7','4','1','0','8','B','4','D','F','C','8','B','8','9','*','*','*','*','*','*','*','*','E','8','*','*','*','*','*','*','*','*','E','B','0','2','3','2','C','0','8','B','E','5','5','D','C','3','\0' };
		ULONG64 markCode4[] = { 0x4345423835354343, 0x4346443439383135, 0x3338434635344238, 0x30302A2A2A2A3842, 0x3031343730303030, 0x4238434644344238, 0x30302A2A2A2A3938, 0x2A2A2A2A38453030, 0x323042452A2A2A2A
, 0x3545423830433233, 0x0000000033434435 };
		distinct = gpfn_strlen((CHAR*)markCode4);
		ULONG start = (DWORD)Top_Kart + 0x1000;
		while((endaddr = ScanAddress(NULL, (CHAR*)markCode4, distinct, start, 0, 0, size - 0x1000 - (start -(Top_Kart + 0x1000))))!=0){
			if (endaddr >= (ULONG)Top_Kart + size || endaddr == 0) {
				//MessageBox(NULL, "5.2", "5.2", MB_OK);
				return;
			}
			//CHAR dbu[64];
			//sprintf(dbu, "%d %X %X %X", distinct,endaddr, size - 0x1000 - (start - (Top_Kart + 0x1000)), size);
			//MessageBox(NULL, dbu, "5.1", MB_OK);
			ULONG tmp = endaddr + (0x9C - 0x7F);
			if (*(BYTE*)tmp == 0xE8) {
				tmp += 1;
				if (gpfn_memcmp((PVOID)(*(INT*)tmp + tmp + 4), (PVOID)markCode4_2, sizeof(markCode4_2))==0) {
					OFFSET3 = *(INT*)(endaddr + (0x8A - 0x7F + 2));
					OFFSET4 = *(BYTE*)((*(INT*)tmp + tmp + 4) + (0xDA - 0xD0 + 2));
					break;
				}
			}
			
			start = endaddr+1;
		};
#ifdef _dbg
		//MessageBox(NULL, "6", "2", MB_OK);
#endif
		//CHAR markCode5[] = { 'E','8','*','*','*','*','*','*','*','*','C','7','4','5','*','*','0','0','0','0','0','0','0','0','8','B','5','5','*','*','8','B','8','A','*','*','*','*','*','*','*','*','E','8','*','*','*','*','*','*','*','*','8','3','*','*','0','1','\0' };
		ULONG64 markCode5[] = { 0x2A2A2A2A2A2A3845, 0x2A2A353437432A2A, 0x3030303030303030, 0x42382A2A35354238, 0x2A2A2A2A2A2A4138, 0x2A2A2A2A38452A2A, 0x2A2A33382A2A2A2A, 0x0000000000003130 };
		distinct = gpfn_strlen((CHAR*)markCode5);
		endaddr = ScanAddress(NULL, (CHAR*)markCode5, distinct, (DWORD)Top_Kart + 0x1000, 0, 0, size - 0x1000);
		if (endaddr >= (ULONG)Top_Kart + size || endaddr == 0) {
			return;
		}
		INT OFFSET5 = *(INT*)(endaddr + (0x59 - 0x4A + 2));
#ifdef _dbg
		//MessageBox(NULL, "7", "2", MB_OK);
#endif
		//CHAR markCode6[] = { 'C','7','4','5','F','C','0','0','0','0','0','0','0','0','8','B','4','5','*','*','8','3','*','*','*','*','0','0','7','4','*','*','E','8','*','*','*','*','*','*','*','*','8','5','\0' };
		ULONG64 markCode6[] = { 0x3030303033413436, 0x4434393830303030, 0x3836303041363046, 0x3030303031304434, 0x38652A2A2A2A4438, 0x2A2A2A2A2A2A2A2A, 0x3030434635343743, 0x4238303030303030, 0x2A2A33382A2A2A2A
, 0x0000000030302A2A };
		distinct = gpfn_strlen((CHAR*)markCode6);//64 A3 00 00 00 0089 4D F06A 00 68 4D 01 00 008D** ** e8 ** ** ** **C745FC000000008B****83 ** ** 00
		endaddr = ScanAddress(NULL, (CHAR*)markCode6, distinct, (DWORD)Top_Kart + 0x1000, 0, 0, size - 0x1000);
		if (endaddr >= (ULONG)Top_Kart + size || endaddr == 0) {
			return;
		}
#ifdef _dbg
		//MessageBox(NULL, "8", "2", MB_OK);
#endif
		INT OFFSET6 = *(BYTE*)(endaddr + (0xA1 - 0x7F + 2));

		ULONG64 markCode7[] = { 0x3338434542383535, 0x4434393838304345, 0x4346353442384346, 0x2A2A2A2A38384238, 0x3535423830303030, 0x0000000000004346 };
		distinct = gpfn_strlen((CHAR*)markCode7);//64 A3 00 00 00 0089 4D F06A 00 68 4D 01 00 008D** ** e8 ** ** ** **C745FC000000008B****83 ** ** 00
		endaddr = ScanAddress(NULL, (CHAR*)markCode7, distinct, (DWORD)Top_Kart + 0x1000, 0, 0, size - 0x1000);
		if (endaddr >= (ULONG)Top_Kart + size || endaddr == 0) {
			return;
		}
#ifdef _dbg
		//MessageBox(NULL, "8", "2", MB_OK);
#endif
		INT OFFSET7 = *(DWORD*)(endaddr + (0xEC - 0xE0 + 2));
#ifdef _dbg
		CHAR buf[45] = { 0 };
 		sprintf(buf, "%x %x %x %x %x %x %x %x", BaseAddr, OFFSET1, OFFSET2, OFFSET3, OFFSET4, OFFSET5, OFFSET6, OFFSET7);
 		MessageBox(NULL, buf, "1", MB_OK);
#endif

		if (isPass == FALSE) {
			gpfn_TerminateProcess((HANDLE)-1, 0);
		}
#ifdef _dbg
		//MessageBox(NULL, "9", "2", MB_OK);
#endif
		DWORD mpid = gpfn_GetCurrentProcessId();
		DWORD mtid = gpfn_GetCurrentThreadId();
		HANDLE h = gpfn_CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);//
		THREADENTRY32 te = { sizeof(te) };
		//te.dwSize = sizeof(te);
		if (gpfn_Thread32First(h, &te)) //遍历线程ID
		{
			do
			{
				if (te.th32OwnerProcessID == mpid) {
					HANDLE hThread1 = INVALID_HANDLE_VALUE;
					if (te.th32ThreadID != mtid) {

						hThread1 = gpfn_OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
						if (hThread1 == NULL) {
							continue;
						}
						gpfn_SuspendThread(hThread1);
					}
					else {
						hThread1 = gpfn_GetCurrentThread();
					}


					CONTEXT context;
					__stosb((unsigned char*)&context, 0, sizeof(context));
					context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
					gpfn_GetThreadContext(hThread1, &context);
					context.Dr7 = 0;
					context.Dr0 = 0;
					context.Dr1 = 0;
					context.Dr2 = 0;
					context.Dr3 = 0;
					gpfn_SetThreadContext(hThread1, &context);


					if (te.th32ThreadID != mtid) {
						//ResumeThread(hThread1);
						gpfn_CloseHandle(hThread1);
					}

				}
			} while (gpfn_Thread32Next(h, &te));
		};
		gpfn_CloseHandle(h);
		
#ifdef _dbg
		//MessageBox(NULL, "10", "2", MB_OK);
#endif
 		//sprintf(buf, "%X", FakeThread);
 		//MessageBox(NULL, buf, "1", MB_OK);
		ULONG funsize = SizeOfFunc((PUCHAR)InitThread);
#ifdef _dbg
 		sprintf(buf, "%x %X", InitThread, funsize);
 		MessageBox(NULL, buf, "1", MB_OK);
#endif
		PVOID Mem = gpfn_VirtualAlloc(0, sizeof(SYSTEM_ROUTINE_ADDRESS), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (Mem == 0) {
			//MessageBox(NULL, "3", "2", MB_OK);
			return;
		}
		PVOID MemFun = gpfn_VirtualAlloc(0, funsize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READ);
		if (MemFun == 0) {
			//MessageBox(NULL, "4", "2", MB_OK);
			return;
		}
 		//sprintf(buf, "%X", Mem);
 		//MessageBox(NULL, buf, "1", MB_OK);
 		//sprintf(buf, "%X", MemFun);
 		//MessageBox(NULL, buf, "1", MB_OK);
		if (isPass == FALSE) {
			gpfn_PostQuitMessage(0);
		}
		
		CHAR Sleep[] = { 'N','t','D','e','l','a','y','E','x','e','c','u','t','i','o','n','\0' };
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->pfn_NtDelayExecution = (fn_NtDelayExecution)gpfn_GetProcAddress(ntdll, Sleep);
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->Top_Kart_Base = BaseAddr;

		CHAR WriteProcessMemory_str[] = { 'W','r','i','t','e','P','r','o','c','e','s','s','M','e','m','o','r','y','\0' };
		CHAR VirtualFree_str[] = { 'V','i','r','t','u','a','l','F','r','e','e','\0' };
		CHAR DeleteFileA_str[] = { 'D','e','l','e','t','e','F','i','l','e','A','\0' };
		CHAR ZwSetEvent_str[] = { 'Z','w','S','e','t','E','v','e','n','t','\0' };
		
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->pfn_WriteProcessMemory = (fn_WriteProcessMemory)gpfn_GetProcAddress(K32, WriteProcessMemory_str);
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->pfn_VirtualFree = (fn_VirtualFree)gpfn_GetProcAddress(K32, VirtualFree_str);
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->pfn_DeleteFileA = (fn_DeleteFileA)gpfn_GetProcAddress(K32, DeleteFileA_str);
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->pfn_ZwSetEvent = (fn_ZwSetEvent)gpfn_GetProcAddress(ntdll, ZwSetEvent_str);
		strcpy(((PSYSTEM_ROUTINE_ADDRESS)Mem)->PATH, FileName);
#ifdef _dbg
		//MessageBox(NULL, "11", "2", MB_OK);
#endif
		if (((PSYSTEM_ROUTINE_ADDRESS)Mem)->pfn_NtDelayExecution == 0 || ((PSYSTEM_ROUTINE_ADDRESS)Mem)->pfn_WriteProcessMemory == 0) return;
		if (isPass == FALSE) {
			PUCHAR p = NULL;
			*p = 0;
		}
#ifdef _dbg
		//MessageBox(NULL, "12", "2", MB_OK);
#endif
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->OFFSET1 = OFFSET1;
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->OFFSET2 = OFFSET2;
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->OFFSET3 = OFFSET3;
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->OFFSET4 = OFFSET4;
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->OFFSET5 = OFFSET5;
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->OFFSET6 = OFFSET6;
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->OFFSET7 = OFFSET7;
		gpfn_WriteProcessMemory((HANDLE)-1, MemFun, &Mem, 4, 0);
		ToShellCode((PUCHAR)InitThread, (PUCHAR)((ULONG)MemFun+4), funsize, MemFun);
		char jmpfun[] = { 0x81,0x7C,0x24,0x04,0x90,0x90,0x90,0x90,0x75,0x07,0xB8,0x90,0x90,0x90,0x90,0xFF,0xD0,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0xE9,0x00,0xCC,0xCC,0xCC };
		if (isPass == FALSE) {
			__stosb((unsigned char*)&InitCode, 0, 0x1000);
		}
#ifdef _dbg
		//MessageBox(NULL, "13", "2", MB_OK);
#endif
		ULONG HeadLen = GetPatchSize2((PUCHAR)FakeThread);
		//CHAR buf[512];
#ifdef _dbg
		sprintf(buf, "%X FakeThread %X %X", HeadLen, FakeThread, MemFun);
		MessageBox(NULL, buf, "1", MB_OK);
#endif
 		
		*(DWORD*)(jmpfun + 11) = (ULONG)MemFun + 4;
		if (*(PUCHAR)FakeThread == 0xE9 && HeadLen == 5) {
			*(DWORD*)(jmpfun + sizeof(jmpfun) - 4) = FakeThread + HeadLen + *(int*)(FakeThread+1) - ((ULONG)MemFun + 4 + funsize + sizeof(jmpfun));
		}
		else {
			*(DWORD*)(jmpfun + sizeof(jmpfun) - 4) = FakeThread + HeadLen - ((ULONG)MemFun + 4 + funsize + sizeof(jmpfun));
			//RtlCopyMemory(&jmpfun[17], (PVOID)FakeThread, HeadLen);
			__movsb((unsigned char*)&jmpfun[17], (unsigned char*)FakeThread, HeadLen);
		}
#ifdef _dbg
		//MessageBox(NULL, "15", "2", MB_OK);
#endif
		PUCHAR jmpfunope = (PUCHAR)MemFun + 4 + funsize;
		if (isPass == FALSE) {
			gpfn_PostQuitMessage(0);
		}
		gpfn_WriteProcessMemory((HANDLE)-1, jmpfunope, jmpfun, sizeof(jmpfun), 0);
		//BYTE NOP[] = { 0x90,0x90,0x90,0x90 };
		//WriteProcessMemory(GetCurrentProcess(), (PUCHAR)MemFun + 0x119, NOP, sizeof(NOP), 0);
		//RtlCopyMemory(((PSYSTEM_ROUTINE_ADDRESS)Mem)->jmpcode, (PVOID)FakeThread, HeadLen);
		__movsb((unsigned char*)((PSYSTEM_ROUTINE_ADDRESS)Mem)->jmpcode, (unsigned char*)FakeThread, HeadLen);
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->ToAddr = FakeThread;
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->memStart = MemFun;
		((PSYSTEM_ROUTINE_ADDRESS)Mem)->JmpFunAddr = jmpfunope;
		if (isPass == FALSE) {
			ULONG d = *(ULONG*)0;
		}
#ifdef _dbg
		//MessageBox(NULL, "16", "2", MB_OK);
#endif
 		MakeJmp((PUCHAR)FakeThread, jmpfunope);
   		//sprintf(buf, "%X", FakeThread);
  		//MessageBox(NULL, buf, "1", MB_OK);
		DWORD threadid = 0;
		HANDLE hThread = gpfn_CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)(PUCHAR)FakeThread, (LPVOID)0x90909090, CREATE_SUSPENDED, &threadid);
#ifdef _dbg
		sprintf(buf, "%x %x", threadid, FakeThread);
 		MessageBox(NULL, buf, "1", MB_OK);
#endif
		HANDLE kd = ((PSYSTEM_ROUTINE_ADDRESS)Mem)->g_hEvent = pfn_CreateEventA(NULL, TRUE, TRUE, NULL);
		ULONG values = THREAD_PRIORITY_HIGHEST;
		gpfn_ZwSetInformationThread(hThread, ThreadBasePriority, &values, 4);
		gpfn_ResumeThread(hThread);
		gpfn_WaitForSingleObject(kd, INFINITE);
		
		gpfn_CloseHandle(hThread);
#ifdef _dbg
		//MessageBox(NULL, "17", "2", MB_OK);
#endif
		if (isPass == FALSE) {
			ULONG d = *(ULONG*)0;
		}
#ifdef _dbg
		//MessageBox(NULL, "18", "2", MB_OK);
#endif
		h = gpfn_CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);//
		te.dwSize = sizeof(te);
		//te.dwSize = sizeof(te);
		if (gpfn_Thread32First(h, &te)) //遍历线程ID
		{
			do
			{
				if (te.th32OwnerProcessID == mpid) {
					HANDLE hThread1 = INVALID_HANDLE_VALUE;
					if (te.th32ThreadID != mtid) {

						hThread1 = gpfn_OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
						if (hThread1 == NULL) {
							continue;
						}
					}
					else {
						hThread1 = gpfn_GetCurrentThread();
					}


					if (te.th32ThreadID != mtid) {
						gpfn_ResumeThread(hThread1);
						gpfn_CloseHandle(hThread1);
					}

				}
			} while (gpfn_Thread32Next(h, &te));
		};
		gpfn_CloseHandle(h);
// 		sprintf(buf, "%X", ((PSYSTEM_ROUTINE_ADDRESS)Mem)->Top_Kart_Base);
// 		MessageBox(NULL, buf, "1", MB_OK);

#ifdef _dbg
		//MessageBox(NULL, "19", "2", MB_OK);
#endif
	}
	return;
}
#pragma optimize( "gs", on )

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		//DisableThreadLibraryCalls(hModule);
		SELF = hModule;
		InitCode();
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
#ifdef DBG__
	return TRUE;
#else
	return FALSE;
#endif

}
