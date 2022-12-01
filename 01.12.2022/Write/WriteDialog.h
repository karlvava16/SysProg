#pragma once
#include "headers.h"
using namespace std;


class WriteDialog
{
public:
	WriteDialog(void);
public:
	~WriteDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static WriteDialog* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	HWND hDialog;
};
