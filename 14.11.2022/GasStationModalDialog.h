#pragma once
#include "header.h"

class GasStationModalDialog
{
public:
	GasStationModalDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static GasStationModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Count();
	HWND hEdit, hEdit1, hEdit2, hResult, hCombo, hRadio1, hRadio2;
	static double dGasStation;
	LOGFONT lf;
	HFONT hFont;
};
