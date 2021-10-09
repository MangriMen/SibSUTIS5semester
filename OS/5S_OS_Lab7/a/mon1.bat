call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cl /EHsc mon1.cpp %*
DEL mon1.obj
mon1.exe