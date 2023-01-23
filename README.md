# ITP-Project-1

## Get Windows Executable
1. Generate a Release Build
    * Through QT
    * Building with QMake and mingw
    ```
    > cd .\Source\Frontend\ITP-Project-Frontend
    > qmake ITP-Project-Frontend.pro
    > mingw32-make
    > cd release
    ```
2. Run deployForWin.bat in /Frontend

**OR**

2. Run **qtenv2.bat** inside C:\Qt\6.4.2\mingw_64\bin
3. Run windeployqt.exe --compiler-runtime <Build.exe>