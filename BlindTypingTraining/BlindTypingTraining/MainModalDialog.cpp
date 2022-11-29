#define WM_ICON WM_APP
#define ID_TRAYICON WM_USER
#include "MainModalDialog.h"


CMainModalDialog* CMainModalDialog::ptr = NULL;
double CMainModalDialog::dCheck = 0;


CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
	pNID = new NOTIFYICONDATA;
}

CMainModalDialog::~CMainModalDialog(void)
{
	delete pNID;
}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}


BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	SetWindowText(hwnd, TEXT("TKB"));
	hDialog = hwnd;

	//lf.lfHeight = 20;
	//hFont = CreateFontIndirect(&lf);
	//hEdit = GetDlgItem(hwnd, IDC_RESULT);

	SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);

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
	lstrcpy(pNID->szInfo, TEXT("Научись слепой печати)"));
	lstrcpy(pNID->szInfoTitle, TEXT("TKB"));
	pNID->uID = IDI_ICON1; // предопределённый идентификатор иконки

	return TRUE;
}


void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{/*
	if (id == IDC_GASSTATION)
	{
		GasStationModalDialog gs;
		INT_PTR result = DialogBox
		(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, GasStationModalDialog::DlgProc);
		CMainModalDialog::Count();
		SetWindowText(hEdit, std::to_wstring(dCheck).c_str());
	}
	if (id == IDC_CAFE)
	{
		CafeModalDialog cafe;
		INT_PTR result = DialogBox
		(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, CafeModalDialog::DlgProc);
		CMainModalDialog::Count();
		SetWindowText(hEdit, std::to_wstring(dCheck).c_str());
	}
	*/
}

void CMainModalDialog::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	if (state == SIZE_MINIMIZED)
	{
		ShowWindow(hwnd, SW_HIDE); // Прячем окно
		Shell_NotifyIcon(NIM_ADD, pNID); // Добавляем иконку в трэй
	}
}

// обработчик пользовательского сообщения
void CMainModalDialog::OnTrayIcon(WPARAM wp, LPARAM lp)
{
	// WPARAM - идентификатор иконки
	// LPARAM - сообщение от мыши или клавиатурное сообщение
	if (lp == WM_LBUTTONDBLCLK)
	{
		Shell_NotifyIcon(NIM_DELETE, pNID); // Удаляем иконку из трэя
		ShowWindow(hDialog, SW_NORMAL); // Восстанавливаем окно
		SetForegroundWindow(hDialog); // устанавливаем окно на передний план
	}
}

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
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
