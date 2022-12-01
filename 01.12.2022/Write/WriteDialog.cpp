#include "WriteDialog.h"

WriteDialog* WriteDialog::ptr = NULL;




WriteDialog::WriteDialog(void)
{
	ptr = this;
}

WriteDialog::~WriteDialog(void)
{

}

void WriteDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Coding_Thread(LPVOID lp)
{
	WriteDialog* ptr = (WriteDialog*)lp;
	char buf[4096];
	ifstream in(TEXT("music.txt"), ios::binary | ios::in);
	if (!in)
	{
		MessageBox(ptr->hDialog, TEXT("Ошибка открытия файла!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
		return 1;
	}
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{B8A2C367-10FE-494d-A869-841B2AF972E0}"));

	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	if (dwAnswer == WAIT_OBJECT_0)
	{
		ofstream out("Write.txt", ios::binary | ios::out | ios::trunc);
		string str;
		while (!in.eof())
		{
			in >> str;
			out << str << " ";
		}
		out.close();

		ReleaseMutex(hMutex);

		MessageBox(ptr->hDialog, TEXT("Запись данных в файл Write.txt завершена!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
	}
	in.close();
	return 0;
}

BOOL WriteDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, 0, Coding_Thread, this, 0, NULL);
	return TRUE;
}


BOOL CALLBACK WriteDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}
