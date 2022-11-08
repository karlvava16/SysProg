#include <windows.h>
#include <tchar.h>
#include "resource.h"

#define CRT_SECURE_NO_WARNINGS

HINSTANCE hInst;                                // current instance
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HICON hIcon;
HBITMAP hbPictures;
HWND hFields[3][3];
BOOL bCheck;

short sFields[3][3]{};
short count = 0;


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	// создаём главное окно приложения на основе модального диалога
	return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	static int i = 0;
	static UINT res = 0;

	switch (message)
	{
	case WM_INITDIALOG:
	{
		hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hWnd, WM_SETICON, 1, LPARAM(hIcon));
		bCheck = TRUE;

		for (int i = 0; i < 9; i++)
		{
			hFields[0][i] = GetDlgItem(hWnd, (IDC_BUTTON1 + i));
		}
	}
	break;
	case WM_COMMAND:
	{
		i = 0;
		for (; i < 9; i++)
		{
			if (LOWORD(wp) == (IDC_BUTTON1 + i)) {
				SendMessage(hFields[0][i], WM_SETTEXT, 0, LPARAM(bCheck ? TEXT("X") : TEXT("O")));
				EnableWindow(hFields[0][i], FALSE);
				sFields[0][i] = bCheck ? 1 : 2;
				bCheck = bCheck ? FALSE : TRUE;
				count++;
				break;
			}
		}
		if ((sFields[0][0] == sFields[0][1] && sFields[0][1] == sFields[0][2] && sFields[0][2] != 0) ||
			(sFields[1][0] == sFields[1][1] && sFields[1][1] == sFields[1][2] && sFields[1][2] != 0) ||
			(sFields[2][0] == sFields[2][1] && sFields[2][1] == sFields[2][2] && sFields[2][2] != 0) ||
			(sFields[0][0] == sFields[1][0] && sFields[1][0] == sFields[2][0] && sFields[2][0] != 0) ||
			(sFields[0][1] == sFields[1][1] && sFields[1][1] == sFields[2][1] && sFields[2][1] != 0) ||
			(sFields[0][2] == sFields[1][2] && sFields[1][2] == sFields[2][2] && sFields[2][2] != 0) ||
			(sFields[0][0] == sFields[1][1] && sFields[1][1] == sFields[2][2] && sFields[2][2] != 0) ||
			(sFields[0][2] == sFields[1][1] && sFields[1][1] == sFields[2][0] && sFields[2][0] != 0))
		{
			TCHAR str[30]{};
			_tcscpy_s(str, !bCheck ? TEXT("X IS WINNER") : TEXT("O IS WINNER"));
			res = MessageBox(hWnd, TEXT("RESTART?"), str, MB_YESNO);
			count++;
		}
		else if (count == 9)
		{
			res = MessageBox(hWnd, TEXT("RESTART?"), TEXT("DRAW"), MB_YESNO);
		}
		if (res == IDYES)
		{
			for (int i = 0; i < 9; i++)
			{
				SendMessage(hFields[0][i], WM_SETTEXT, 0, LPARAM(TEXT("")));
				sFields[0][i] = 0;
				EnableWindow(hFields[0][i], TRUE);
			}
			count = 0;
			res = 0;
		}
		else if (res == IDNO)
		{
			EndDialog(hWnd, 0); // закрываем модальный диалог
			return TRUE;
		}
	}
	break;

	case WM_CLOSE:
		EndDialog(hWnd, 0); // закрываем модальный диалог
		return TRUE;
	}
	return FALSE;
}

