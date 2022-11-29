#include "MainModalDialog.h"


CMainModalDialog* CMainModalDialog::ptr = NULL;
double CMainModalDialog::dCheck = 0;


CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

void CMainModalDialog::Count()
{
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	SetWindowText(hwnd, TEXT("OKKO"));

	//lf.lfHeight = 20;
	//hFont = CreateFontIndirect(&lf);
	//hEdit = GetDlgItem(hwnd, IDC_RESULT);

	SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);

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

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
