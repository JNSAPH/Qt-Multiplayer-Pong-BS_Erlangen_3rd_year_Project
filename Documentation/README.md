# ITP-Project1 Documentation
Notice that this is a rough draft and for now will only be note and store things for the final, actuall Documentation.

## MariaDB Class
You might encounter the Error:
```
QSqlDatabase: QMYSQL driver not loaded
QSqlDatabase: available drivers: QSQLITE QODBC QPSQL
Error opening database: "Driver not loaded Driver not loaded"
```

The QMYSQL Drivers are a plugin for the Qt framework that allow you to connect to MySQL databases using the QtSql module. The QMYSQL Drivers are implemented as a shared library and can be built from source or installed as precompiled binaries.

To build the Dlls yourself follow the Steps at https://doc.qt.io/qt-6/sql-driver.html

**OR**

just use my precompiled Dlls located in **/Backend/Dlls/sqldrivers/**. Move everything in the sqldrivers folder to C:\Qt\6.4.1\mingw_64\plugins\sqldrivers and pray it works.