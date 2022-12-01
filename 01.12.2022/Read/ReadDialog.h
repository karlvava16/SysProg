#pragma once
#include "headers.h"
using namespace std;

class ReadDialog
{
public:
	ReadDialog(void);
public:
	~ReadDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static ReadDialog* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	HWND hDialog;
};