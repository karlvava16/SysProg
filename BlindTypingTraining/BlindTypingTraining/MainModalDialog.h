#pragma once
#include "header.h"

class CMainModalDialog
{
public:
		static CMainModalDialog* ptr;
	CMainModalDialog(void);
	~CMainModalDialog(void);
	

	BOOL SingleWindowCheck(HWND hwnd);
	void TrayInit(HWND hwnd);
	
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy);

	void OnTrayIcon(WPARAM wp, LPARAM lp); // обработчик пользовательского сообщени€
	
	
	static double dCheck;
	HWND hEdit, hDialog;
	LOGFONT lf;
	HFONT hFont;
	COLORREF color;
	HICON hIcon;
	PNOTIFYICONDATA pNID;
	HANDLE hMutex;
	HMENU hMenu;
};
