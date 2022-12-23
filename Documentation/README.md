# ITP-Project1 Documentation
Notice that this is a rough draft and for now will only be note and store things for the final, actuall Documentation.

## MariaDB Class
You might encounter the Error:
```
QSqlDatabase: QMYSQL driver not loaded
QSqlDatabase: available drivers: QSQLITE QODBC QPSQL
Error opening database: "Driver not loaded Driver not loaded"
```
The QT Sql Library requires for you to install "MySQL Connector/C++". 

To install the MySQL Connector/C++ library on Windows, you can follow these steps:

1. Download the MySQL Connector/C++ installer from the MySQL website.
2. Run the installer and follow the prompts to complete the installation.
3. Add the path to the MySQL Connector/C++ library to your system's PATH environment variable. This is usually C:\Program Files\MySQL\MySQL Connector C++ 8.0\lib.
Once the MySQL Connector/C++ library is installed, you should be able to use the MariaDB class to connect to a MariaDB database.

On Linux, you can install the MySQL Connector/C++ library using the package manager of your distribution. For example, on Ubuntu, you can use the following command:

```bash
sudo apt-get install libmysqlcppconn7
```
This will install the MySQL Connector/C++ library and its dependencies. You may also need to install the **libqt5-mysql** package to use the QMYSQL driver with Qt's SQL module.

Once the MySQL Connector/C++ library is installed, you should be able to use the MariaDB class to connect to a MariaDB database.

This article may help too:
https://doc.qt.io/qt-6/sql-driver.html#qmysql