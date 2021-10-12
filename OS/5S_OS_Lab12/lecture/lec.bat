call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"
cl /EHsc /MT creator.cpp %*
cl /EHsc /MT reader.cpp %*
DEL *.obj