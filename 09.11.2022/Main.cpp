#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HICON hIcon;
HBITMAP hbPictures[2];
HWND hFields[9];

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	// ������ ������� ���� ���������� �� ������ ���������� �������
	return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

	}
	break;
	case WM_COMMAND:
	{

	}
	break;
	case WM_CLOSE:
		EndDialog(hWnd, 0); // ��������� ��������� ������
		return TRUE;
	}
	return FALSE;
}