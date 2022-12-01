#pragma once
#include "headers.h"

class MainDialog
{
public:
	MainDialog(void);
public:
	~MainDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static MainDialog* ptr;
	void Cls_OnClose(HWND hwnd);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
};
