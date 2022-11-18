#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"

#define MAX_GRADE 17


BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hAnswerEdit1, hAnswerEdit2, hProgress1, hTextResult, hSpin1, hSpin2, hEdit1, hEdit2;
HMENU hMenu;
HWND hStaticTime, hProgress;
HANDLE hndlTime;

bool isFirstPressed;
bool isSecondPressed;
bool isThirdPressed;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{

	// создаём главное окно приложения на основе модального диалога
	return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}


DWORD WINAPI Thread_Timer(LPVOID lp)
{
	// для возврата приоритета
	DWORD Priority = GetPriorityClass(GetCurrentProcess());

	// установка приоритета
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);

	HWND hStaticTime = HWND(lp);

	short minutes = 3;
	short seconds = 0;
	TCHAR textMyTime[255];
	TCHAR textSeconds[255];

	while (true)
	{
		seconds--;

		if (minutes == 0 && seconds == -1) break;

		if (seconds == -1)
		{
			minutes--;
			seconds = 59;
		}

		// Записываем в текст число минут
		if (minutes < 11) _stprintf_s(textMyTime, TEXT("0%d"), minutes);
		else _stprintf_s(textMyTime, TEXT("%d"), minutes);


		if (seconds < 11) wcscat_s(textMyTime, 255, TEXT(":0"));
		else wcscat_s(textMyTime, 255, TEXT(":"));


		_stprintf_s(textSeconds, TEXT("%d"), seconds);
		wcscat_s(textMyTime, 255, textSeconds);

		SetWindowText(hStaticTime, textMyTime);
		Sleep(980);
	}

	// возвращаем приоритет в прошлое состояние
	SetPriorityClass(GetCurrentProcess(), Priority);
	SetWindowText(hStaticTime, TEXT("END"));
	return 0;
}

int rightAnswers(HWND hWnd)
{
	int count = 0;
	
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
	

	TCHAR str[100] = TEXT("");

	GetWindowText(hAnswerEdit1, str, 100);
	int length = SendDlgItemMessage(hWnd, IDC_EDIT1, WM_GETTEXTLENGTH, 0, 0);
	if (wcsncmp(str, TEXT("большой"), length) != 0 && strlen("большой") == length) count++;

	GetWindowText(hAnswerEdit2, str, 100);
	length = SendDlgItemMessage(hWnd, IDC_EDIT2, WM_GETTEXTLENGTH, 0, 0);
	if (wcsncmp(str, TEXT("указатель"), length) != 0 && strlen("указатель") == length) count++;

	GetWindowText(hEdit1, str, 100);
	length = SendDlgItemMessage(hWnd, IDC_EDIT3, WM_GETTEXTLENGTH, 0, 0);
	if (wcsncmp(str, TEXT("777"), length) == 0) count++;

	GetWindowText(hEdit2, str, 100);
	length = SendDlgItemMessage(hWnd, IDC_EDIT4, WM_GETTEXTLENGTH, 0, 0);
	if (wcsncmp(str, TEXT("3"), length) == 0) count++;

	return count;
}


BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	static TCHAR str[40] = TEXT("");
	switch (message)
	{
	case WM_INITDIALOG:
	{
		isFirstPressed = false;
		isSecondPressed = false;
		isThirdPressed = false;

		// получаем дескрипторы
		hStaticTime = GetDlgItem(hWnd, IDC_STATIC_TIME);

		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		// Присоединим меню к главному окну приложения
		SetMenu(hWnd, hMenu);

		hAnswerEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
		hAnswerEdit1 = GetDlgItem(hWnd, IDC_EDIT2);
		hTextResult = GetDlgItem(hWnd, IDC_STATIC1);

		hSpin1 = GetDlgItem(hWnd, IDC_SPIN1);
		hSpin2 = GetDlgItem(hWnd, IDC_SPIN2);
		hEdit1 = GetDlgItem(hWnd, IDC_EDIT3);
		hEdit2 = GetDlgItem(hWnd, IDC_EDIT4);

		// установим диапазон счетчика
		SendMessage(hSpin1, UDM_SETRANGE32, 0, 1000);
		SendMessage(hSpin2, UDM_SETRANGE32, 0, 10);
		// зададим правило приращения
		UDACCEL pAcceleration[3] = { {1,1}, {2,25}, {3,50} };
		SendMessage(hSpin1, UDM_SETACCEL, 3, LPARAM(pAcceleration));
		SendMessage(hSpin2, UDM_SETACCEL, 3, LPARAM(pAcceleration));
		// установим приятеля
		SendMessage(hSpin1, UDM_SETBUDDY, WPARAM(hEdit1), 0);
		SendMessage(hSpin2, UDM_SETBUDDY, WPARAM(hEdit2), 0);
		SetWindowText(hEdit1, TEXT("0"));
		SetWindowText(hEdit2, TEXT("0"));

		hProgress1 = GetDlgItem(hWnd, IDC_PROGRESS1);
		SendMessage(hProgress1, PBM_SETRANGE, 0, MAKELPARAM(0, 100)); // Установка интервала для индикатора 
		SendMessage(hProgress1, PBM_SETSTEP, 1, 0); // Установка шага приращения  индикатора 
		SendMessage(hProgress1, PBM_SETPOS, 0, 0); // Установка текущей позиции индикатора
		SendMessage(hProgress1, PBM_SETBARCOLOR, 0, LPARAM(RGB(20, 200, 50)));

		hndlTime = CreateThread(NULL, 0, Thread_Timer, hStaticTime, 0, NULL);
	}
	break;

	case WM_COMMAND:
	{
		if (LOWORD(wp) == ID_MENU_EXIT)
			SendMessage(hWnd, WM_CLOSE, 0, 0);

		else if (LOWORD(wp) == IDC_BUTTON1)
		{
			int i = rightAnswers(hWnd);
			int b = i * 1.0 / MAX_GRADE * 100;

			wsprintf(str, TEXT("%d/%d\n%d/100%% "), i, MAX_GRADE, b);

			SendMessage(hProgress1, PBM_SETPOS, WPARAM(b), 0); // Установка текущей позиции индикатора
			SendMessage(hProgress1, WM_SETTEXT, NULL,NULL); // Установка текущей позиции индикатора
			ShowWindow(hProgress1, SW_SHOW);

			SetWindowText(hTextResult, str);
			ShowWindow(hTextResult, SW_SHOW);
			SuspendThread(hndlTime);
		}
		
	}
	break;
	
	case WM_CLOSE:
		EndDialog(hWnd, 0); // закрываем модальный диалог
		return TRUE;
	}
	return FALSE;
}