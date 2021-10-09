call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cl /EHsc /LD lib1.cpp %*
cl a.cpp /EHsc %*
DEL a.obj
DEL lib1.obj
DEL lib1.exp
DEL lib1.lib
a.exe