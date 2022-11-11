#include <windows.h>
#include <tchar.h>
#include <time.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hButton, hList, hResult;
TCHAR str[5];
int iMaxNumbers;
int iCountN = 0;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	srand(time(0));
	// создаём главное окно приложения на основе модального диалога
	return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

int Calculate(HWND hWnd)
{
	iCountN = SendMessage(hList, LB_GETSELCOUNT, 0, 0);
	int iCount = 0;

	if (SendDlgItemMessage(hWnd, IDC_SUM, BM_GETCHECK, 0, 0) || SendDlgItemMessage(hWnd, IDC_AVERAGE, BM_GETCHECK, 0, 0))
	{
		// выделим память необходимого размера для хранения индексов выбранных элементов списка
		int* p = new int[iCountN];
		// Заполним динамический массив индексами выделенных элементов списка 
		SendMessage(hList, LB_GETSELITEMS, iCountN, LPARAM(p));
		for (int i = 0; i < iCountN; i++)
		{
			SendMessage(hList, LB_GETTEXT, p[i], LPARAM(str));
			iCount += _wtoi(str);
		}
		delete[]p;
	}
	else if (SendDlgItemMessage(hWnd, IDC_MULT, BM_GETCHECK, 0, 0))
	{
		iCount = iCountN > 0 ? 1 : 0;
		// выделим память необходимого размера для хранения индексов выбранных элементов списка
		int* p = new int[iCountN];
		// Заполним динамический массив индексами выделенных элементов списка 
		SendMessage(hList, LB_GETSELITEMS, iCountN, LPARAM(p));
		for (int i = 0; i < iCountN; i++)
		{
			SendMessage(hList, LB_GETTEXT, p[i], LPARAM(str));
			iCount *= _wtoi(str);
		}
		delete[]p;
	}

	if (SendDlgItemMessage(hWnd, IDC_AVERAGE, BM_GETCHECK, 0, 0))
	{
		iCount /= iCountN;
	}

	return iCount;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		// get handles
		hButton = GetDlgItem(hWnd, IDC_BUTTON1);
		hList = GetDlgItem(hWnd, IDC_LIST1);
		hResult = GetDlgItem(hWnd, IDC_RESULT);
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wp) == IDC_BUTTON1)
		{
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
			// rand max number in list
			iMaxNumbers = rand() % 11 + 10;
			// enter values in list
			for (int i = 0; i < iMaxNumbers; i++)
			{
				wsprintf(str, TEXT("%d"), rand() % 21 - 10);
				SendMessage(hList, LB_ADDSTRING, 0, LPARAM(str));
			}
		}

		if (iCountN != SendMessage(hList, LB_GETSELCOUNT, 0, 0) || LOWORD(wp) == IDC_SUM || LOWORD(wp) == IDC_MULT || LOWORD(wp) == IDC_AVERAGE)
		{
			wsprintf(str, TEXT("%d"), Calculate(hWnd));
			SendMessage(hResult, WM_SETTEXT, 0, LPARAM(str));
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hWnd, 0); // закрываем модальный диалог
		return TRUE;
	}
	return FALSE;
}