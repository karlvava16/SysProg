#include "Dialog.h"

Dialog* Dialog::ptr = NULL;
Dialog::Dialog(void)
{
	ptr = this;
}

Dialog::~Dialog(void)
{
}

void Dialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL Dialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{

	hAmount = GetDlgItem(hwnd, IDC_AMOUNT);
	hEdit = GetDlgItem(hwnd, IDC_EDIT);
	hStart = GetDlgItem(hwnd, IDC_START);

	SetWindowText(hAmount, TEXT("0"));

	return TRUE;
}

void MessageAboutError(DWORD dwError)
{
	LPVOID lpMsgBuf = NULL;
	TCHAR szBuf[300];

	BOOL fOK = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	if (lpMsgBuf != NULL)
	{
		wsprintf(szBuf, TEXT("������ %d: %s"), dwError, lpMsgBuf);
		MessageBox(0, szBuf, TEXT("��������� �� ������"), MB_OK | MB_ICONSTOP);
		LocalFree(lpMsgBuf);
	}
}

DWORD WINAPI WriteFiles(LPVOID lp)
{
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("{CEEF1E86-01BC-4620-B553-A5B0B5BD65DC}"));
	if (WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
	{
		TCHAR tchBuffName[FILENAME_MAX];
		TCHAR tchFileAmount[20];

		GetWindowText(Dialog::ptr->hEdit, tchBuffName, FILENAME_MAX);
		GetWindowText(Dialog::ptr->hAmount, tchFileAmount, 20);

		if (_wtoi(tchFileAmount) <= 0)
		{
			MessageBox(0, TEXT("�������� ���� ���-�� ����� ������"), tchFileAmount, MB_OK);
			return 1;
		}

		wifstream wifIn(tchBuffName);

		if (!wifIn.is_open())
		{

			MessageAboutError(GetLastError());
			MessageBox(0, TEXT("�������� ���� �������� �����"), tchBuffName, MB_OK);
			return 1;
		}

		wstring wstrStr;
		wofstream wofOut;
		TCHAR tchStrCpy[20 + FILENAME_MAX];

		for (int i = 0; i < _wtoi(tchFileAmount); i++)
		{
			_itow_s(i + 1, tchStrCpy, 10);
			_tcscat_s(tchStrCpy, 20 + FILENAME_MAX, tchBuffName);
			wofOut.open(tchStrCpy);
			if (!wofOut.is_open())
			{
				MessageBox(0, TEXT("�������� ����"), tchStrCpy, MB_OK);
				wifIn.close();
				return 1;
			}
			wifIn.seekg(0, ios::beg);

			while (!wifIn.eof())
			{
				wifIn >> wstrStr;
				wofOut << wstrStr << TEXT(" ");
			}
			wofOut << TEXT("\n");
			wofOut.close();
		}

		wifIn.close();


		MessageBox(0, TEXT("����� ������� ���������� � �����"), TEXT("����������� ������"), MB_OK);
	}
	return 0;
}

DWORD WINAPI ReadFiles(LPVOID lp)
{
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("{CEEF1E86-01BC-4620-B553-A5B0B5BD65DC}"));
	if (WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
	{
		TCHAR tchBuffName[FILENAME_MAX];
		TCHAR tchFileAmount[20];

		GetWindowText(Dialog::ptr->hEdit, tchBuffName, FILENAME_MAX);
		GetWindowText(Dialog::ptr->hAmount, tchFileAmount, 20);




		if (_wtoi(tchFileAmount) <= 0)
		{
			MessageBox(0, TEXT("�������� ���� ���-�� ����� ������"), tchFileAmount, MB_OK);
			return 1;
		}

		wstring wstrResult = TEXT("RESULT_");
		wstrResult += tchBuffName;

		wofstream wofOut(wstrResult);

		if (!wofOut.is_open())
		{

			MessageAboutError(GetLastError());
			MessageBox(0, TEXT("�������� ���� �������� �����"), tchBuffName, MB_OK);
			return 1;
		}


		wstring wstrStr;
		wifstream wifIn;
		TCHAR tchStrCpy[20 + FILENAME_MAX];

		for (int i = 0; i < _wtoi(tchFileAmount); i++)
		{
			_itow_s(i + 1, tchStrCpy, 10);
			_tcscat_s(tchStrCpy, 20 + FILENAME_MAX, tchBuffName);
			wifIn.open(tchStrCpy);
			if (!wifIn.is_open())
			{
				MessageBox(0, TEXT("�������� ����"), tchStrCpy, MB_OK);
				wofOut.close();
				return 1;
			}
			wofOut << "|File: " << tchStrCpy << "|\n";
			wifIn >> wstrStr;
			while (!wifIn.eof())
			{
				wofOut << wstrStr << TEXT(" ");
				wifIn >> wstrStr;
			}
			wofOut << TEXT("\n\n");
			wifIn.close();
		}

		wofOut.close();
		MessageBox(0, TEXT("����� �������� ����������"), wstrResult.c_str(), MB_OK);
	}
	return 0;
}

void Dialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	CreateEvent(NULL, FALSE /*�������������� ����� ������� */,
		FALSE /* ������������ ��������� */, TEXT("{CEEF1E86-01BC-4620-B553-A5B0B5BD65DC}"));
	HANDLE h;
	h = CreateThread(NULL, 0, WriteFiles, 0, 0, NULL);
	CloseHandle(h);
	h = CreateThread(NULL, 0, ReadFiles, 0, 0, NULL);
	CloseHandle(h);

	if (id == IDC_START)
	{

		HANDLE h = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("{CEEF1E86-01BC-4620-B553-A5B0B5BD65DC}"));
		SetEvent(h); // ������� ������� � ���������� ���������
	}
}

BOOL CALLBACK Dialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}