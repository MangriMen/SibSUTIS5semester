call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cl /EHsc /MT mutexSync1.cpp %*
cl /EHsc /MT mutexSync2.cpp %*
DEL *.obj