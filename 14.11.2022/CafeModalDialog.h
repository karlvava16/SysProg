#pragma once
#include "header.h"

class CafeModalDialog
{
public:
	CafeModalDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CafeModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Count();
	HWND hEditStatic1, hEditStatic2, hEditStatic3, hEditStatic4;
	HWND hEdit1, hEdit2, hEdit3, hEdit4;
	HWND hCheck1, hCheck2, hCheck3, hCheck4;
	HWND hResult;
	static double dCafe;
	LOGFONT lf;
	HFONT hFont;
};

