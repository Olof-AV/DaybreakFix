#include <windows.h>
#include <d3d9.h>
#include "detours.h"
#include "FixerDevice.h"
#include "../Common/Utils.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "detours.lib")

typedef HRESULT(APIENTRY* createDevice)(IDirect3D9*, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS*, IDirect3DDevice9**);
createDevice originalCreateDevice;

FixerDevice* g_pDevice;

void GetVTable(void** vTable, size_t size)
{
	IDirect3D9* const pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	memcpy(vTable, *reinterpret_cast<void***>(pDirect3D), size);

	pDirect3D->Release();
}

HRESULT APIENTRY MyCreateDevice(IDirect3D9* This, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface)
{
	HRESULT hr = originalCreateDevice(This, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

	g_pDevice = new FixerDevice();
	g_pDevice->m_pDevice = *ppReturnedDeviceInterface;
	*ppReturnedDeviceInterface = (IDirect3DDevice9*)(g_pDevice);

	return hr;
}

DWORD WINAPI MainThread(LPVOID lpThreadParam)
{
	constexpr unsigned char vTableSizeDirect3D = 17;
	constexpr unsigned char createDeviceOffset = 16;

	HMODULE hModule = static_cast<HMODULE>(lpThreadParam);

	// Look for CreateDevice function to detour.
	void* vTable[vTableSizeDirect3D];
	GetVTable(vTable, sizeof(vTable));
	originalCreateDevice = (createDevice)(vTable[createDeviceOffset]);

	// Apply detour.
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)originalCreateDevice, MyCreateDevice);
	LONG error = DetourTransactionCommit();
	if (error != NO_ERROR)
	{
		MessageBoxWithErrorAndThrow(L"Failed DetourAttach.");
	}

	// Wait until custom device has been injected, then detach & exit.
	while (!g_pDevice)
	{
		Sleep(1000);
	}
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)originalCreateDevice, MyCreateDevice);
	error = DetourTransactionCommit();
	if (error != NO_ERROR)
	{
		MessageBoxWithErrorAndThrow(L"Failed DetourDetach.");
	}
	else
	{
		::PlaySound(TEXT("DeviceConnect"), NULL, SND_ALIAS | SND_ASYNC);
	}

	// TODO: Investigate why this crashes Daybreak... (probably need to give original device back?)
	//FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);

	return EXIT_SUCCESS;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hModule);

			const HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, NULL);
			if (hThread)
			{
				CloseHandle(hThread);
			}
		}
		default:
			break;
	}

	return TRUE;
	// Do not use EXIT_SUCCESS here, that is 0 == FALSE == Failed to attach...
}