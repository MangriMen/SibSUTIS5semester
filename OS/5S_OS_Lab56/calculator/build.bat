call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
rc calc.rc %*
cl /Fe:"simpleCalc" calc.cpp calc.res user32.lib /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS %*
simpleCalc.exe