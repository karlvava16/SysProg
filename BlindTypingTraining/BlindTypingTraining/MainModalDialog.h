#pragma once
#include "header.h"

std::wstring LoadText();

DWORD WINAPI SpeedThread(LPVOID lp);
DWORD WINAPI TimeThread(LPVOID lp);
LRESULT CALLBACK KeyboardProc(int idCode, WPARAM wParam, LPARAM lParam);

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

	LOGFONT lf;
	HFONT hFont;
	HICON hIcon;
	PNOTIFYICONDATA pNID;

};
