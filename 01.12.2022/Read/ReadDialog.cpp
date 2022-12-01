#include "ReadDialog.h"

ReadDialog* ReadDialog::ptr = NULL;


ReadDialog::ReadDialog(void)
{
	ptr = this;
}

ReadDialog::~ReadDialog(void)
{

}

void ReadDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Decoding_Thread(LPVOID lp)
{
	ReadDialog* ptr = (ReadDialog*)lp;
	char buf[4096];

	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{B8A2C367-10FE-494d-A869-841B2AF972E0}"));

	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	if (dwAnswer == WAIT_OBJECT_0)
	{
		ifstream in(TEXT("test.txt"), ios::binary | ios::in);
		if (!in)
		{
			MessageBox(ptr->hDialog, TEXT("Ошибка открытия файла!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
			return 1;
		}
		ofstream out("Read.txt", ios::binary | ios::out | ios::trunc);
		string str;
		while (!in.eof())
		{
			while (!in.eof())
			{
				in >> str;
				out << str << " ";
			}
			out.close();
		}
		out.close();
		in.close();

		ReleaseMutex(hMutex);

		MessageBox(ptr->hDialog, TEXT("Чтение данных из файла test.txt завершено!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
	}
	return 0;
}

BOOL ReadDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, 0, Decoding_Thread, this, 0, NULL);
	return TRUE;
}

BOOL CALLBACK ReadDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}
