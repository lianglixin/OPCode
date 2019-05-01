#include "Disassembler.h"
#include "OpcodeToString.h"
#include <Windows.h>
#include <Windowsx.h>
#include "resource.h"
#pragma comment (lib, "opcode.lib")


INT_PTR CALLBACK DialogProc (
	_In_ HWND   hwnd,
	_In_ UINT   msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
		{
			std::vector <char> vec (10000);
			GetDlgItemTextA(hwnd, IDC_EDIT1, &vec[0], vec.size());
			std::string str = &vec[0];
			bool isNote = BST_CHECKED == Button_GetCheck (GetDlgItem (hwnd, IDC_CHECK1));
			bool isX64 = BST_CHECKED == Button_GetCheck (GetDlgItem (hwnd, IDC_CHECK2));
			std::string assembly = Tools::disassemble (
				str, isNote, isX64 ? InstSet::x64 : InstSet::x86);
			SetDlgItemTextA (hwnd, IDC_EDIT2, assembly.c_str());
			return TRUE;
		}
		case IDCANCEL:
			EndDialog (hwnd, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}
int WINAPI wWinMain (
	HINSTANCE hInstance,
	HINSTANCE,
	LPWSTR cmdLine,
	int)
{
	DialogBoxW (hInstance, (LPWSTR)IDD_DIALOG1, 0, DialogProc);
	return 0;
}