call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cl /EHsc /MT ev2.c %*
cl /EHsc /MT evd1.cpp %*
cl /EHsc /MT evd11.cpp %*
cl /EHsc /MT libevd1.cpp %*
DEL *.obj