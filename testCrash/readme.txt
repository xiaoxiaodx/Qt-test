在程序结束前捕获程序崩溃
	1、使用程序生成的崩溃日志与D:\Qt\Qt5.12.2\5.12.2\mingw73_32>下的addr2line 配合使用
	2、假如日志如下
	
	APP Version: APP_VERSION
Windows:  6.1.7600, SP 0.0, Product Type 1
GraphicsCard: SoundDevice: Process:  F:\testCrash\build-testCrash-Desktop_Qt_5_12_2_MinGW_32_bit-Debug\debug\testCrash.exe
Exception Addr:  02BA7A46   Module: D:\Qt\Qt5.12.2\5.12.2\mingw73_32\bin\Qt5Cored.dll
Exception Code:  C0000005
Write Address:  18EC842C
Instruction:  F0 0F B1 11 75 02 F3 C3 83 EC 1C 83 F8 03 77 09
Registers: 
EAX: 00000000  EBX: 18EC83EC  ECX: 18EC842C  EDX: 00000001
ESI: 757B7480  EDI: 3E2B21B8  ESP: 006EFDCC  EBP: 006EFE08
EIP: 02BA7A46  EFlags: 00010202
Call Stack:
02BA7A46  D:\Qt\Qt5.12.2\5.12.2\mingw73_32\bin\Qt5Cored.dll
0040189E  F:\testCrash\build-testCrash-Desktop_Qt_5_12_2_MinGW_32_bit-Debug\debug\testCrash.exe
004039F0  F:\testCrash\build-testCrash-Desktop_Qt_5_12_2_MinGW_32_bit-Debug\debug\testCrash.exe


则命令行：D:\Qt\Qt5.12.2\5.12.2\mingw73_32>addr2line -f -e testCrash.exe.exe 0040189E 004039F0 