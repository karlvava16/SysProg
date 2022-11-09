#include <windows.h>
#include <tchar.h>
#include "resource.h"


BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hAnswerEdit1, hAnswerEdit2;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	// создаём главное окно приложения на основе модального диалога
	return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

int rightAnswers(HWND hWnd)
{
	int count = 0;
	//IDC_RADIO3
	//IDC_RADIO7
	//IDC_RADIO10
	//IDC_RADIO15
	//IDC_RADIO18
	//IDC_RADIO25
	//IDC_RADIO29
	//IDC_RADIO32
	if (SendDlgItemMessage(hWnd, IDC_RADIO3, BM_GETCHECK, 0, 0)) count++;
	if (SendDlgItemMessage(hWnd, IDC_RADIO7, BM_GETCHECK, 0, 0)) count++;
	if (SendDlgItemMessage(hWnd, IDC_RADIO10, BM_GETCHECK, 0, 0)) count++;
	if (SendDlgItemMessage(hWnd, IDC_RADIO15, BM_GETCHECK, 0, 0)) count++;
	if (SendDlgItemMessage(hWnd, IDC_RADIO18, BM_GETCHECK, 0, 0)) count++;
	if (SendDlgItemMessage(hWnd, IDC_RADIO25, BM_GETCHECK, 0, 0)) count++;
	if (SendDlgItemMessage(hWnd, IDC_RADIO29, BM_GETCHECK, 0, 0)) count++;
	if (SendDlgItemMessage(hWnd, IDC_RADIO32, BM_GETCHECK, 0, 0)) count++;

	if (!SendDlgItemMessage(hWnd, IDC_CHECK1, BM_GETCHECK, 0, 0) &&
		!SendDlgItemMessage(hWnd, IDC_CHECK3, BM_GETCHECK, 0, 0) &&
		!SendDlgItemMessage(hWnd, IDC_CHECK5, BM_GETCHECK, 0, 0))
	{
		if (SendDlgItemMessage(hWnd, IDC_CHECK2, BM_GETCHECK, 0, 0)) count++;
		if (SendDlgItemMessage(hWnd, IDC_CHECK4, BM_GETCHECK, 0, 0)) count++;
	}

	if (!SendDlgItemMessage(hWnd, IDC_CHECK8, BM_GETCHECK, 0, 0) &&
		!SendDlgItemMessage(hWnd, IDC_CHECK9, BM_GETCHECK, 0, 0))
	{
		if (SendDlgItemMessage(hWnd, IDC_CHECK6, BM_GETCHECK, 0, 0)) count++;
		if (SendDlgItemMessage(hWnd, IDC_CHECK7, BM_GETCHECK, 0, 0)) count++;
		if (SendDlgItemMessage(hWnd, IDC_CHECK10, BM_GETCHECK, 0, 0)) count++;
	}

	TCHAR str[100];

	GetWindowText(hAnswerEdit1, str, 100);
	int length = SendDlgItemMessage(hWnd, IDC_EDIT1, WM_GETTEXTLENGTH, 0, 0);

	if (wcsncmp(str, TEXT("большой"), length) != 0) count++;

	GetWindowText(hAnswerEdit2, str, 100);
	length = SendDlgItemMessage(hWnd, IDC_EDIT2, WM_GETTEXTLENGTH, 0, 0);

	if (wcsncmp(str, TEXT("указатель"), length) != 0) count++;

	return count;
}


BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	static TCHAR str[40] = TEXT("");
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hAnswerEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
		hAnswerEdit1 = GetDlgItem(hWnd, IDC_EDIT2);
	}
	case WM_COMMAND:
	{
		if (LOWORD(wp) == IDC_BUTTON1)
		{
			int i = rightAnswers(hWnd);
			int b = i * 1.0 / 15 * 100;

			wsprintf(str, TEXT("%d/%d\t %d/100%% "), i, 15, b);
			MessageBox(hWnd, str, TEXT(""), MB_OK);
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hWnd, 0); // закрываем модальный диалог
		return TRUE;
	}
	return FALSE;
}