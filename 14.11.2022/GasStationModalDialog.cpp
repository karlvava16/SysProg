#include "GasStationModalDialog.h"

GasStationModalDialog* GasStationModalDialog::ptr = NULL;

double GasStationModalDialog::dGasStation = 0;

GasStationModalDialog::GasStationModalDialog(void)
{
	ptr = this;
}


void GasStationModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

void GasStationModalDialog::Count()
{
	TCHAR temp[200] = TEXT("");
	TCHAR str[200] = TEXT("");
	TCHAR* ptr;
	if (Button_GetState(hRadio1) == TRUE)
	{
		GetWindowText(hEdit1, str, 200);
		dGasStation = wcstod(str, &ptr);
		GetWindowText(hEdit, str, 200);
		dGasStation *= wcstod(str, &ptr);
		dGasStation = round(dGasStation * 100) / 100.f;
		_stprintf_s(temp, TEXT("%f"), dGasStation);
		SetWindowText(hEdit2, temp);
		SetWindowText(hResult, temp);
	}
	else
	{
		GetWindowText(hEdit2, str, 200);
		SetWindowText(hResult, str);
		dGasStation = wcstod(str, &ptr);
		dGasStation = round(dGasStation * 100) / 100.f;
		GetWindowText(hEdit, str, 200);
		if (wcstod(str, &ptr) != 0.f)
		{
			_stprintf_s(temp, TEXT("%f"), round(dGasStation / wcstod(str, &ptr) * 100) / 100.f);
			SetWindowText(hEdit1, temp);
			_stprintf_s(temp, TEXT("%f"), dGasStation);
			SetWindowText(hResult, temp);

		}
		else
		{
			dGasStation = 0.f;
			SetWindowText(hEdit1, TEXT("0.00"));
			SetWindowText(hResult, TEXT("0.00"));
		}
	}
}

BOOL GasStationModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	SetWindowText(hwnd, TEXT("ÀÂÒÎÇÀÏÐÀÂÊÀ"));

	hRadio1 = GetDlgItem(hwnd, IDC_RADIO1);
	hRadio2 = GetDlgItem(hwnd, IDC_RADIO2);
	SendMessage(hRadio1, BM_SETCHECK, BST_CHECKED, 1);


	hCombo = GetDlgItem(hwnd, IDC_COMBO1);

	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("[ÂÛÁÐÀÒÜ]")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("À-95")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("À-92")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("Äèçåëüíûé")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("Ãàç")));

	SendMessage(hCombo, CB_SELECTSTRING, 0, LPARAM(TEXT("[ÂÛÁÐÀÒÜ]")));

	hEdit = GetDlgItem(hwnd, IDC_COMBO_RESULT);
	hEdit1 = GetDlgItem(hwnd, IDC_AMOUNT_GASSTATION);
	hEdit2 = GetDlgItem(hwnd, IDC_CHECK_GASSTATION);
	hResult = GetDlgItem(hwnd, IDC_RESULT_GASSTATION);
	
	SetWindowText(hEdit, TEXT("0.00"));
	SetWindowText(hEdit1, TEXT("0.00"));
	SetWindowText(hEdit2, TEXT("0.00"));
	SetWindowText(hResult, TEXT("0.00"));


	SendMessage(hResult, WM_SETFONT, (WPARAM)hFont, TRUE);

	return TRUE;
}


void GasStationModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_COMBO1 && codeNotify == CBN_SELCHANGE)
	{
		int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		switch (index)
		{
		case 0: 
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(TEXT("0.00")));
			break;
		case 1:
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(TEXT("49.43")));
			break;

		case 2:
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(TEXT("47.83")));
			break;

		case 3:
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(TEXT("53.95")));
			break;

		case 4:
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(TEXT("25.72")));
			break;
		}
	}
	else if (id == IDC_RADIO1)
	{
		EnableWindow(hEdit1, TRUE);
		EnableWindow(hEdit2, FALSE);
	}
	else if (id == IDC_RADIO2)
	{
		EnableWindow(hEdit1, FALSE);
		EnableWindow(hEdit2, TRUE);
	}
	else if (id == IDOK)
	{
		Count();
	}
	
}

BOOL CALLBACK GasStationModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
