call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
rc client.rc %*
cl client.cpp client.res user32.lib %*
client.exe