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


BOOL CMainModalDialog::SingleWindowCheck(HWND hwnd)
{
	TCHAR GUID[] = TEXT("{D99CD3E0-670D-4def-9B74-99FD7E793DFB}");
	hMutex = CreateMutex(NULL, FALSE, GUID);
	DWORD dwAnswer = WaitForSingleObject(hMutex, 0);
	if (dwAnswer == WAIT_TIMEOUT)
	{
		MessageBox(hwnd, TEXT("���������� TKL ��� ��������."), TEXT("TKB"), MB_OK | MB_ICONINFORMATION);
		EndDialog(hwnd, 0);
		return FALSE;
	}
	return TRUE;
}

void CMainModalDialog::TrayInit(HWND hwnd)
{
	// ������� ���������� ���������� ����������
	HINSTANCE hInst = GetModuleHandle(NULL);

	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // ��������� ������
	SetClassLong(hDialog, GCL_HICON, LONG(hIcon)); // ������������� ������ � ������� ���� ����������
	memset(pNID, 0, sizeof(NOTIFYICONDATA)); //��������� ���������
	pNID->cbSize = sizeof(NOTIFYICONDATA); //������ ���������
	pNID->hIcon = hIcon; //��������� ���������������� ������
	pNID->hWnd = hwnd; //���������� ����, ������� ����� �������� ������������ ���������,
	// ��������������� � ������� � ����.	
	lstrcpy(pNID->szTip, TEXT("TKB")); // ���������

	pNID->uCallbackMessage = WM_ICON; // ���������������� ���������
	// ������� ���������� ���� ������������� ��� ������� ������������
	// ��������� ����, ���������� �������� �������� � ���� hWnd. ��� ���������
	// ����������, ����� ���������� "�������" ��������� � ��������������, ���
	// ����������� ������, ��� ������ ���������� ��� �������������� � �������
	// ����������. �������� ��������� wParam �������� ��� ���� �������������
	// ������ � ����, ��� ��������� �������, � �������� ��������� lParam - 
	// "�������" ��� ������������ ���������, ��������������� � ��������.
	// ������ �������: ������ ����� �� ������ � ����.

	pNID->uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE | NIF_INFO;
	// NIF_ICON - ���� hIcon �������� ���������� �������� (��������� ������� ������ � ����).
	// NIF_MESSAGE - ���� uCallbackMessage �������� ���������� ��������
	// (��������� �������� ��������� �� ������ � ����).
	// NIF_TIP - ���� szTip �������� ���������� �������� (��������� ������� ����������� ��������� ��� ������ � ����).
	// NIF_INFO - ���� szInfo �������� ���������� �������� (��������� ������� Balloon ��������� ��� ������ � ����).
	lstrcpy(pNID->szInfo, TEXT("������� ������ ������)"));
	lstrcpy(pNID->szInfoTitle, TEXT("TKB"));
	pNID->uID = IDI_ICON1; // ��������������� ������������� ������
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	//use mutex to check how many dialog exist (must be only one main dialog)
	if (!SingleWindowCheck(hwnd)) return FALSE;

	//set HWND for main dialog
	SetWindowText(hwnd, TEXT("TKB"));
	hDialog = hwnd;

	//set HWND menu and attach menu to main dialog
	hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(hDialog, hMenu);

	//lf.lfHeight = 20;
	//hFont = CreateFontIndirect(&lf);
	//hEdit = GetDlgItem(hwnd, IDC_RESULT);
	//SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);

	//set tray icon and notifications
	TrayInit(hwnd);

	return TRUE;
}


void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	/*
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
		ShowWindow(hwnd, SW_HIDE); // ������ ����
		Shell_NotifyIcon(NIM_ADD, pNID); // ��������� ������ � ����
	}
}

// ���������� ����������������� ���������
void CMainModalDialog::OnTrayIcon(WPARAM wp, LPARAM lp)
{
	// WPARAM - ������������� ������
	// LPARAM - ��������� �� ���� ��� ������������ ���������
	if (lp == WM_LBUTTONDBLCLK)
	{
		Shell_NotifyIcon(NIM_DELETE, pNID); // ������� ������ �� ����
		ShowWindow(hDialog, SW_NORMAL); // ��������������� ����
		SetForegroundWindow(hDialog); // ������������� ���� �� �������� ����
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
	// ���������������� ���������
	if (message == WM_ICON)
	{
		ptr->OnTrayIcon(wParam, lParam);
		return TRUE;
	}
	return FALSE;
}
