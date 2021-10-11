call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cl /EHsc main.cpp imagehlp.lib %*
DEL main.obj
main.exe kernel32.dll > kernel32.txt
main.exe notepad.exe > notepad.txt