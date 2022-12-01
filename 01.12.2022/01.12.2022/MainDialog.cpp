#include "MainDialog.h"




MainDialog* MainDialog::ptr = NULL;

MainDialog::MainDialog(void)
{
	ptr = this;
}

MainDialog::~MainDialog(void)
{

}

void MainDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}



void MainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (IDC_BUTTON1 == id)
	{
		CreateMutex(0, FALSE, TEXT("{B8A2C367-10FE-494d-A869-841B2AF972E0}"));

		STARTUPINFO st = { sizeof(st) };
		PROCESS_INFORMATION pr;

		TCHAR filename[20];
		wsprintf(filename, TEXT("%s"), TEXT("Write.exe"));

		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr))
		{
			MessageBox(0, 0, 0, 0);
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);

		ZeroMemory(&st, sizeof(st));
		st.cb = sizeof(st);

		wsprintf(filename, TEXT("%s"), TEXT("Read.exe"));

		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr))
		{
			MessageBox(0, 0, 0, 0);
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);
	}
}

BOOL CALLBACK MainDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

