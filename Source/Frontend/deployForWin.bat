@echo off
echo Current working directory: %CD%
set "executable_path=%CD%\build-ITP-Project-Frontend-Desktop_Qt_6_4_2_MinGW_64_bit-Release\release\"
cd %executable_path%
echo Changed working directory: %CD%
del /S /Q *.o
call "C:\Qt\6.4.2\mingw_64\bin\qtenv2.bat"
call "C:\Qt\6.4.2\mingw_64\bin\.\windeployqt.exe" "%executable_path%ITP-Project-Frontend.exe"
