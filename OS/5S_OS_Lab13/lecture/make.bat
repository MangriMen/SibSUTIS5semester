call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cl /nologo /Zi /DEBUG:FASTLINK  /EHsc np1.c %*
cl /nologo /Zi /DEBUG:FASTLINK  /EHsc np2.c %*