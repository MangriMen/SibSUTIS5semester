call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
rc reciever.rc %*
cl reciever.c user32.lib%*
reciever.exe