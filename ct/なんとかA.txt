Last login: Sat Aug  8 10:24:17 2015 from 10.0.2.2
[q4@localhost ~]$ ls
flag.txt  q4  readme.txt
[q4@localhost ~]$ cat readme.txt
You are not allowed to connect internet and write the home directory.
If you need temporary directory, use /tmp.
Sometimes this machine will be reset.
[q4@localhost ~]$ cat flag.txt
cat: flag.txt: Permission denied
[q4@localhost ~]$ ls -l flag.txt
-r--------. 2 q4a q4a 22 May 22  2012 flag.txt
[q4@localhost ~]$ ls -l q4
-rwsr-xr-x. 1 q4a q4a 5857 May 22  2012 q4
[q4@localhost ~]$ file q4
q4: setuid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.18, not stripped
[q4@localhost ~]$ gdb q4
(gdb) set disassembly-flavor intel
(gdb) disas main
   0x080485b4 <+0>:     push   ebp
   0x080485b5 <+1>:     mov    ebp,esp
   0x080485b7 <+3>:     and    esp,0xfffffff0
   0x080485ba <+6>:     sub    esp,0x420
   0x080485c0 <+12>:    mov    DWORD PTR [esp],0x80487a4			#0x80487a4 : "What's your name?"
   0x080485c7 <+19>:    call   0x80484c4 <puts@plt>				    #puts呼び出し
   0x080485cc <+24>:    mov    eax,ds:0x8049a04
   0x080485d1 <+29>:    mov    DWORD PTR [esp+0x8],eax
   0x080485d5 <+33>:    mov    DWORD PTR [esp+0x4],0x400
   0x080485dd <+41>:    lea    eax,[esp+0x18]
   0x080485e1 <+45>:    mov    DWORD PTR [esp],eax
   0x080485e4 <+48>:    call   0x8048484 <fgets@plt>				#fgets呼び出し
   0x080485e9 <+53>:    mov    DWORD PTR [esp],0x80487b6			#0x80487b6 : "Hi,"
   0x080485f0 <+60>:    call   0x80484b4 <printf@plt>               #printf呼び出し
   0x080485f5 <+65>:    lea    eax,[esp+0x18]
   
      ※下記のようにfgets返り値ポインタ(eax)を直渡しは危険。formatstringattackが可能
   0x080485f9 <+69>:    mov    DWORD PTR [esp],eax                  #eax=fgetsの戻り値 

   0x080485fc <+72>:    call   0x80484b4 <printf@plt>				#printf呼び出し
   0x08048601 <+77>:    mov    DWORD PTR [esp],0xa
   0x08048608 <+84>:    call   0x8048474 <putchar@plt>				#putchar呼び出し
   0x0804860d <+89>:    mov    DWORD PTR [esp+0x418],0x1
   0x08048618 <+100>:   jmp    0x8048681 <main+205>
   0x0804861a <+102>:   mov    DWORD PTR [esp],0x80487bb            #0x80487bb : "Do you want the flag?"
   0x08048621 <+109>:   call   0x80484c4 <puts@plt>
   0x08048626 <+114>:   mov    eax,ds:0x8049a04
   0x0804862b <+119>:   mov    DWORD PTR [esp+0x8],eax
   0x0804862f <+123>:   mov    DWORD PTR [esp+0x4],0x400
   0x08048637 <+131>:   lea    eax,[esp+0x18]
   0x0804863b <+135>:   mov    DWORD PTR [esp],eax
   0x0804863e <+138>:   call   0x8048484 <fgets@plt>				#fgets呼び出し
   0x08048643 <+143>:   test   eax,eax
   0x08048645 <+145>:   sete   al
   0x08048648 <+148>:   test   al,al
   0x0804864a <+150>:   je     0x8048656 <main+162>
   0x0804864c <+152>:   mov    eax,0x0                              #flag = 0
   0x08048651 <+157>:   jmp    0x80486dc <main+296>
   0x08048656 <+162>:   mov    DWORD PTR [esp+0x4],0x80487d1        #0x80487d1 : "no"
   0x0804865e <+170>:   lea    eax,[esp+0x18]
   0x08048662 <+174>:   mov    DWORD PTR [esp],eax
   0x08048665 <+177>:   call   0x80484e4 <strcmp@plt>
   0x0804866a <+182>:   test   eax,eax
   0x0804866c <+184>:   jne    0x8048681 <main+205>                 #fgetsの戻り値が"no"なら飛ばない
   0x0804866e <+186>:   mov    DWORD PTR [esp],0x80487d5            #0x80487d5 : "I see. Good bye"
   0x08048675 <+193>:   call   0x80484c4 <puts@plt>				    #puts呼び出し
   0x0804867a <+198>:   mov    eax,0x0
   0x0804867f <+203>:   jmp    0x80486dc <main+296>
   0x08048681 <+205>:   mov    eax,DWORD PTR [esp+0x418]
   0x08048688 <+212>:   test   eax,eax
   0x0804868a <+214>:   setne  al
   0x0804868d <+217>:   test   al,al
   0x0804868f <+219>:   jne    0x804861a <main+102>                 #0x804861aに必ず飛ぶ
   /////////////////////////////////////////////////////////////////////////////////////////////////////
   0x08048691 <+221>:   mov    DWORD PTR [esp+0x4],0x80487e6        #0x80487e6 : "r" 読み込みモード
   0x08048699 <+229>:   mov    DWORD PTR [esp],0x80487e8            #0x80487e8 : "flag.txt"
   0x080486a0 <+236>:   call   0x80484a4 <fopen@plt>                #fopen呼び出し
   0x080486a5 <+241>:   mov    DWORD PTR [esp+0x41c],eax
   0x080486ac <+248>:   mov    eax,DWORD PTR [esp+0x41c]
   0x080486b3 <+255>:   mov    DWORD PTR [esp+0x8],eax
   0x080486b7 <+259>:   mov    DWORD PTR [esp+0x4],0x400
   0x080486bf <+267>:   lea    eax,[esp+0x18]
   0x080486c3 <+271>:   mov    DWORD PTR [esp],eax
   0x080486c6 <+274>:   call   0x8048484 <fgets@plt>
   0x080486cb <+279>:   lea    eax,[esp+0x18]
   0x080486cf <+283>:   mov    DWORD PTR [esp],eax
   0x080486d2 <+286>:   call   0x80484b4 <printf@plt>                #flag.txtの中身が出力される。
   0x080486d7 <+291>:   mov    eax,0x0
   /////////////////////////////////////////////////////////////////////////////////////////////////////   
   0x080486dc <+296>:   leave
   0x080486dd <+297>:   ret
(gdb) q
[q4@localhost ~]$ ./q4
What's your name?
%p %p %p %p %p %p
Hi, 0x400 0x5ed440 0x8 0x14 0x22afc4 0x25207025

Do you want the flag?
no
I see. Good bye.