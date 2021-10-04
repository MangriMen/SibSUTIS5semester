call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cl main.cpp /EHsc %*
DEL main.obj
main.exe