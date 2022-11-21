#include "CafeModalDialog.h"

#define _CHECK1 TEXT("25.00")
#define _CHECK2 TEXT("30.00")
#define _CHECK3 TEXT("17.50")
#define _CHECK4 TEXT("16.80")



CafeModalDialog* CafeModalDialog::ptr = NULL;

double CafeModalDialog::dCafe = 0;


CafeModalDialog::CafeModalDialog(void)
{
	ptr = this;
}


void CafeModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

void CafeModalDialog::Count()
{
	TCHAR str[200];
	TCHAR* ptr;
	dCafe = 0.f;
	if (Button_GetState(hCheck1) == TRUE)
	{
		GetWindowText(hEdit1, str, 200);
		dCafe += (wcstod(str, &ptr) * _wtoi(_CHECK1));
	}
	if (Button_GetState(hCheck2) == TRUE)
	{
		GetWindowText(hEdit2, str, 200);
		dCafe += (wcstod(str, &ptr) * _wtoi(_CHECK2));

	}
	if (Button_GetState(hCheck3) == TRUE)
	{
		GetWindowText(hEdit3, str, 200);
		dCafe += (wcstod(str, &ptr) * _wtoi(_CHECK3));
	}
	if (Button_GetState(hCheck4) == TRUE)
	{
		GetWindowText(hEdit4, str, 200);
		dCafe += (wcstod(str, &ptr) * _wtoi(_CHECK4));
	}
	if (dCafe != 0.f)
	{
		_stprintf_s(str, TEXT("%f"), dCafe);
		SetWindowText(hResult, str);
	}
	else
		SetWindowText(hResult, TEXT("0.00"));
}

BOOL CafeModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	SetWindowText(hwnd, TEXT("ÊÀÔÅ"));
	hResult = GetDlgItem(hwnd, IDC_EDIT9);

	hCheck1 = GetDlgItem(hwnd, IDC_CHECK1);
	hCheck2 = GetDlgItem(hwnd, IDC_CHECK2);
	hCheck3 = GetDlgItem(hwnd, IDC_CHECK3);
	hCheck4 = GetDlgItem(hwnd, IDC_CHECK4);

	hEditStatic1 = GetDlgItem(hwnd, IDC_EDIT1);
	hEditStatic2 = GetDlgItem(hwnd, IDC_EDIT2);
	hEditStatic3 = GetDlgItem(hwnd, IDC_EDIT3);
	hEditStatic4 = GetDlgItem(hwnd, IDC_EDIT4);

	hEdit1 = GetDlgItem(hwnd, IDC_EDIT5);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT6);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT7);
	hEdit4 = GetDlgItem(hwnd, IDC_EDIT8);


	SetWindowText(hEditStatic1, _CHECK1);
	SetWindowText(hEditStatic2, _CHECK2);
	SetWindowText(hEditStatic3, _CHECK3);
	SetWindowText(hEditStatic4, _CHECK4);

	SetWindowText(hResult, TEXT("0.00"));

	SendMessage(hResult, WM_SETFONT, (WPARAM)hFont, TRUE);


	return TRUE;
}


void CafeModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDOK)
	{
		Count();
	}
	if (IsDlgButtonChecked(hwnd,IDC_CHECK1))
		EnableWindow(hEdit1, TRUE);
	else
		EnableWindow(hEdit1, FALSE);

	if (IsDlgButtonChecked(hwnd, IDC_CHECK2))
		EnableWindow(hEdit2, TRUE);
	else
		EnableWindow(hEdit2, FALSE);

	if (IsDlgButtonChecked(hwnd, IDC_CHECK3))
		EnableWindow(hEdit3, TRUE);
	else
		EnableWindow(hEdit3, FALSE);

	if (IsDlgButtonChecked(hwnd, IDC_CHECK4))
		EnableWindow(hEdit4, TRUE);
	else
		EnableWindow(hEdit4, FALSE);
	
}

BOOL CALLBACK CafeModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
