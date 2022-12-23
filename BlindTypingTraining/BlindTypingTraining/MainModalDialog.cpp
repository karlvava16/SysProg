#define WM_ICON WM_APP
#define ID_TRAYICON WM_USER
#include "MainModalDialog.h"

CMainModalDialog* CMainModalDialog::ptr = NULL;

HHOOK hHook;
HANDLE hndlTime;
HANDLE hndlSpeed;

TCHAR tcTextMain[TEXT_SIZE];
int iTextLength;
TCHAR tcCurrentText[TEXT_SIZE]; 
TCHAR tcTextMistakes[TEXT_SIZE];
TCHAR TextKB[TEXT_SIZE];

TCHAR tcSpeedText[TEXT_SIZE];
int iSpeed;

HWND hDialog;
HWND hMistakes;
HWND hTime;
HWND hSpeed;

WPARAM wp;

HMENU hMenu;

short minutes;
short seconds;
UINT uMistakes;
HWND hProgress;
UINT uProgressbarPosition;



HANDLE hMutex;


UINT clicks;

HWND hMain;
HWND hNumbers[10];
HWND hCharacters[26];
HWND ButtonComma, ButtonDot;
HWND ButtonSpace;





CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
	pNID = new NOTIFYICONDATA;
}

CMainModalDialog::~CMainModalDialog(void)
{
	delete pNID;
	ReleaseMutex(hMutex);
}

BOOL CMainModalDialog::SingleWindowCheck(HWND hwnd)
{
	TCHAR GUID[] = TEXT("{D99CD3E0-670D-4def-9B74-99FD7E793DFB}");
	hMutex = CreateMutex(NULL, FALSE, GUID);
	DWORD dwAnswer = WaitForSingleObject(hMutex, 0);
	if (dwAnswer == WAIT_TIMEOUT)
	{
		MessageBox(hwnd, TEXT("TKB already in work"), TEXT("TKB"), MB_OK | MB_ICONINFORMATION);
		EndDialog(hwnd, 0);
		return FALSE;
	}
	return TRUE;
}

void CMainModalDialog::TrayInit(HWND hwnd)
{
	// Получим дескриптор экземпляра приложения
	HINSTANCE hInst = GetModuleHandle(NULL);

	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // загружаем иконку
	SetClassLong(hDialog, GCL_HICON, LONG(hIcon)); // устанавливаем иконку в главном окне приложения
	memset(pNID, 0, sizeof(NOTIFYICONDATA)); //Обнуление структуры
	pNID->cbSize = sizeof(NOTIFYICONDATA); //размер структуры
	pNID->hIcon = hIcon; //загружаем пользовательскую иконку
	pNID->hWnd = hwnd; //дескриптор окна, которое будет получать уведомляющие сообщения,
	// ассоциированные с иконкой в трэе.	
	lstrcpy(pNID->szTip, TEXT("TKB")); // Подсказка

	pNID->uCallbackMessage = WM_ICON; // Пользовательское сообщение
	// Система использует этот идентификатор для посылки уведомляющих
	// сообщений окну, дескриптор которого хранится в поле hWnd. Эти сообщения
	// посылаются, когда происходит "мышиное" сообщение в прямоугольнике, где
	// расположена иконка, или иконка выбирается или активизируется с помощью
	// клавиатуры. Параметр сообщения wParam содержит при этом идентификатор
	// иконки в трэе, где произошло событие, а параметр сообщения lParam - 
	// "мышиное" или клавиатурное сообщение, ассоциированное с событием.
	// Пример события: щелчок мышки по иконке в трэе.

	pNID->uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE | NIF_INFO;
	// NIF_ICON - поле hIcon содержит корректное значение (позволяет создать иконку в трэе).
	// NIF_MESSAGE - поле uCallbackMessage содержит корректное значение
	// (позволяет получать сообщения от иконки в трэе).
	// NIF_TIP - поле szTip содержит корректное значение (позволяет создать всплывающую подсказку для иконки в трэе).
	// NIF_INFO - поле szInfo содержит корректное значение (позволяет создать Balloon подсказку для иконки в трэе).
	lstrcpy(pNID->szInfo, TEXT("Try blind typing)"));
	lstrcpy(pNID->szInfoTitle, TEXT("TKB"));
	pNID->uID = IDI_ICON1; // предопределённый идентификатор иконки

}

std::wstring LoadText()
{
	srand(time(0));
	fs::path p = fs::current_path().wstring() + TEXT("\\TextForType");
	std::vector<std::wstring> strings;
	int count = 0;
	for (const auto& entry : fs::directory_iterator(p))
	{
		strings.push_back(entry.path().wstring());
		count++;
	}
	std::wifstream file(strings[rand() % count]);
	std::wstring result;
	getline(file, result);
	return result;
}

BOOL  CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	//use mutex to check how many dialog exist (must be only one main dialog)
	if (!SingleWindowCheck(hwnd)) return FALSE;


	hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
	
	// connect menu to dialog
	SetMenu(hwnd, hMenu);

	//set tray icon and notifications
	TrayInit(hwnd);

	uProgressbarPosition = 0;

	hDialog = hwnd;
	hMain = GetDlgItem(hwnd, IDC_MAIN);
	hProgress = GetDlgItem(hwnd, IDC_PROGRESS1);
	hMistakes = GetDlgItem(hwnd, IDC_MISSTAKES);
	hTime = GetDlgItem(hwnd, IDC_TIME);
	hSpeed = GetDlgItem(hwnd, IDC_SPEED);
	uMistakes = 0;

	for (int i = 0; i < 10; i++)
	{
		hNumbers[i] = GetDlgItem(hDialog, IDC_NUM1 + i);
	}

	for (int i = 0; i < 26; i++)
	{
		hCharacters[i] = GetDlgItem(hDialog, IDC_A + i);
	}

	ButtonComma = GetDlgItem(hDialog, IDC_COMA);
	ButtonDot = GetDlgItem(hDialog, IDC_DOT);

	ButtonSpace = GetDlgItem(hDialog, IDC_SPACE);



	hndlTime = CreateThread(NULL, 0, TimeThread, hTime, 0, NULL);
	hndlSpeed = CreateThread(NULL, 0, SpeedThread, hSpeed, 0, NULL);


	minutes = 3;
	seconds = 0;

	srand(time(NULL));
	_tcscpy_s(tcTextMain, LoadText().c_str());
	_tcscpy_s(tcCurrentText, tcTextMain);
	int textEditLength = _tcslen(tcTextMain);
	SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, textEditLength));
	SetWindowText(hMain, tcTextMain);

	hHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, NULL, GetCurrentThreadId());


	// set font
	memset(&lf, 0, sizeof(lf));
	lf.lfHeight = 40;
	hFont = CreateFontIndirect(&lf);
	SendMessage(hMain, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hTime, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hSpeed, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hMistakes, WM_SETFONT, (WPARAM)hFont, TRUE);


	SetFocus(hMain);

	return TRUE;
}

DWORD WINAPI SpeedThread(LPVOID lp)
{
	while (true)
	{
		clicks = 0;
		Sleep(5000);
		iSpeed = clicks * 12;

		wsprintf(tcSpeedText, TEXT("%d"), iSpeed);
		SetWindowText(hSpeed, tcSpeedText);
	}
	return 0;
}

DWORD WINAPI TimeThread(LPVOID lp)
{
	HWND hTime = HWND(lp);

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

		if (minutes < 11) _stprintf_s(textMyTime, TEXT("0%d"), minutes);
		else _stprintf_s(textMyTime, TEXT("%d"), minutes);


		if (seconds < 11) wcscat_s(textMyTime, 255, TEXT(":0"));
		else wcscat_s(textMyTime, 255, TEXT(":"));


		_stprintf_s(textSeconds, TEXT("%d"), seconds);
		wcscat_s(textMyTime, 255, textSeconds);

		SetWindowText(hTime, textMyTime);
		Sleep(980);

		if (minutes == 0 && seconds == 0)
		{
			
			minutes = 3;
			seconds = 0;
			//ResumeThread(hndlTime);
			srand(time(NULL));

			_tcscpy_s(tcTextMain, LoadText().c_str());



			_tcscpy_s(tcCurrentText, tcTextMain);
			uMistakes = 0;
			swprintf_s(tcTextMistakes, TEXT("%d"), uMistakes);
			SetWindowText(hMistakes, tcTextMistakes);

			iTextLength = _tcsclen(tcTextMain);

			uProgressbarPosition = 0;
			SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, iTextLength));
			SendMessage(hProgress, PBM_SETPOS, uProgressbarPosition, 0);
			SetWindowText(hMain, tcTextMain);
		}
	}
	return 0;
}

LRESULT CALLBACK KeyboardProc(int idCode, WPARAM wParam, LPARAM lParam)
{
	if (HC_ACTION == idCode)
	{
		TCHAR szMistakes[TEXT_SIZE];
		HWND hWnd = GetFocus();
		static TCHAR buf[40];
		GetClassName(hWnd, buf, 40);

		if (lstrcmpi(buf, TEXT("EDIT")) == 0 && (lParam & 0x80000000)) // клавиша отпущена!!!
		{
			if (wParam <= 32) // непечатаемый символ
			{
				wsprintf(buf, TEXT("0X%X"), wParam);
			}
			else
			{
				if (!(wParam >= 'A' && wParam <= 'Z')) // цифры и некоторые символы
				{
					wsprintf(buf, TEXT("%c"), wParam);

				}

				else
				{
					short shift = GetKeyState(VK_SHIFT); // если старший бит равен 1, то клавиша нажата
					short caps = GetKeyState(VK_CAPITAL); // если младший бит равен 1, то клавиша переключена
					short space = GetKeyState(VK_SPACE); // если младший бит равен 1, то клавиша переключена
					if ((shift & 0x8000) && !(caps & 1) || !(shift & 0x8000) && (caps & 1))
					{
						wsprintf(buf, TEXT("%c"), wParam);
					}
					else
					{
						wsprintf(buf, TEXT("%c"), tolower(wParam));
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				if (buf[0] == TEXT('1' + i))
					SendMessage(hNumbers[i], WM_LBUTTONDOWN, 0, 0);
			}

			for (int i = 0; i < 26; i++)
			{
				if (tolower(buf[0]) == TEXT('a' + i))
					SendMessage(hCharacters[i], WM_LBUTTONDOWN, 0, 0);
			}

			if (buf[0] == TEXT('¼')) 
				SendMessage(ButtonComma, WM_LBUTTONDOWN, 0, 0);
			if (buf[0] == TEXT('¾')) 
				SendMessage(ButtonDot, WM_LBUTTONDOWN, 0, 0);
			if ((buf[0] == TEXT('0') && buf[1] == TEXT('X') && buf[2] == TEXT('2') && buf[3] == TEXT('0'))) 
				SendMessage(ButtonSpace, WM_LBUTTONDOWN, 0, 0);

			Sleep(50);

			for (int i = 0; i < 10; i++)
			{
				SendMessage(hNumbers[i], WM_LBUTTONUP, 0, 0);
			}

			for (int i = 0; i < 26; i++)
			{
				SendMessage(hCharacters[i], WM_LBUTTONUP, 0, 0);
			}

			SendMessage(ButtonComma, WM_LBUTTONUP, 0, 0);
			SendMessage(ButtonDot, WM_LBUTTONUP, 0, 0);
			SendMessage(ButtonSpace, WM_LBUTTONUP, 0, 0);
			SendDlgItemMessage(hDialog, IDC_MAIN, WM_SETFOCUS, 0, 0);
			SetFocus(hMain);

			++clicks;

			if (buf[0] == TEXT('0') && buf[1] == TEXT('X') && buf[2] == TEXT('2') && buf[3] == TEXT('0'))
				buf[0] = TEXT(' ');

			if (buf[0] == TEXT('¾')) buf[0] = TEXT('.');

			if (buf[0] == TEXT('¼')) buf[0] = TEXT(',');


			GetWindowText(hWnd, TextKB, TEXT_SIZE);

			if (_tcslen(TextKB) == 0)
			{
				SuspendThread(hndlTime);
				SuspendThread(hndlSpeed);


				INT_PTR result = MessageBox(NULL, TEXT("Try again?"), TEXT("DONE"), MB_YESNO);
				if (result == IDNO)
					SendMessage(hDialog, WM_CLOSE, NULL, NULL);



				minutes = 3;
				seconds = 0;
				ResumeThread(hndlTime);
				SuspendThread(hndlSpeed);

				srand(time(NULL));

				_tcscpy_s(tcTextMain, LoadText().c_str());

				_tcscpy_s(tcCurrentText, tcTextMain);
				uMistakes = 0;
				swprintf_s(tcTextMistakes, TEXT("%d"), uMistakes);
				SetWindowText(hMistakes, tcTextMistakes);

				iTextLength = _tcsclen(tcTextMain);

				uProgressbarPosition = 0;
				SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, iTextLength));
				SendMessage(hProgress, PBM_SETPOS, uProgressbarPosition, 0);
				SetWindowText(hMain, tcTextMain);



				return 1;
			}

			int iTextLength = _tcslen(TextKB);
			if (buf[0] == TextKB[0])
			{
				for (int i = 0; i < iTextLength - 1; ++i)
					TextKB[i] = TextKB[i + 1];
				TextKB[iTextLength - 1] = 0;

				SendMessage(hProgress, PBM_SETPOS, uProgressbarPosition++, 0);

				SetWindowText(hWnd, TextKB);
			}
			else
			{

				if (buf[0] >= TEXT('a') && buf[0] <= TEXT('z') || buf[0] >= TEXT('A') && buf[0] <= TEXT('Z') 
					|| buf[0] >= TEXT('1') && buf[0] <= TEXT('9') || buf[0] == TEXT('.') || buf[0] == TEXT(',') || buf[0] == TEXT(' '))
				{
					uMistakes++;
					swprintf_s(szMistakes, TEXT("%d"), uMistakes);
					SetDlgItemText(hDialog, IDC_MISSTAKES, szMistakes);
				}
			}
		}
	}
	return CallNextHookEx(hHook, idCode, wParam, lParam);
}

void  CMainModalDialog::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	if (state == SIZE_MINIMIZED)
	{
		SuspendThread(hndlTime);
		SuspendThread(hndlSpeed);
		ShowWindow(hwnd, SW_HIDE); // Прячем окно
		Shell_NotifyIcon(NIM_ADD, pNID); // Добавляем иконку в трэй
	}
}

// обработчик пользовательского сообщения
void  CMainModalDialog::OnTrayIcon(WPARAM wp, LPARAM lp)
{
	// WPARAM - идентификатор иконки
	// LPARAM - сообщение от мыши или клавиатурное сообщение
	if (lp == WM_LBUTTONDBLCLK)
	{
		Shell_NotifyIcon(NIM_DELETE, pNID); // Удаляем иконку из трэя
		ShowWindow(hDialog, SW_NORMAL); // Восстанавливаем окно
		SetForegroundWindow(hDialog); // устанавливаем окно на передний план
		ResumeThread(hndlTime);
		ResumeThread(hndlSpeed);
	}
}

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	wp = wParam;

	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_SIZE, ptr->Cls_OnSize);
	}

	// пользовательское сообщение
	if (message == WM_ICON)
	{
		ptr->OnTrayIcon(wParam, lParam);
		return TRUE;
	}
	return FALSE;
}

void  CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

void  CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (LOWORD(wp) == ID_MENU_RESTART)
	{
		minutes = 3;
		seconds = 0;
		/*ResumeThread(hndlTime);*/
		srand(time(NULL));
		_tcscpy_s(tcTextMain, LoadText().c_str());


		_tcscpy_s(tcCurrentText, tcTextMain);
		uMistakes = 0;
		swprintf_s(tcTextMistakes, TEXT("%d"), uMistakes);
		SetWindowText(hMistakes, tcTextMistakes);
		uProgressbarPosition = 0;
		SendMessage(hProgress, PBM_SETPOS, uProgressbarPosition, 0);
		SetWindowText(hMain, tcTextMain);
	}
}