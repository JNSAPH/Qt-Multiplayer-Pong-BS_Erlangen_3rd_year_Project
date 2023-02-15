# How to create a Release version of your Qt application

1. Navigate to the `mingw_64` folder in your Qt installation directory. This is typically located in `C:\Qt\6.4.2\mingw_64` if you installed Qt in the default location.
2. Locate the bin folder for the compiler that you are using for your project. For example, if you are using the MinGW 64-bit compiler, the bin folder will be `mingw64\bin`.
3. Open a command prompt in the bin folder by holding down the "Shift" key and right-clicking on an empty space in the folder. Select "Open command window here" from the context menu.
4. In the command prompt, run the windeployqt.exe tool with the path to your release executable as the argument. For example, if your release executable is located at `C:\path\to\my\release\app.exe`, you would run the following command:
```cmd
windeployqt.exe C:\path\to\my\release\app.exe
```

This command will copy the required Qt libraries and dependencies to the same directory as your executable, so that it can be run on any machine without requiring a Qt installation.

# How to start your Qt application with command-line arguments in Qt Creator
To start your Qt application with command-line arguments in Qt Creator, follow these steps:

1. Open your project in Qt Creator and click the "Projects" button in the left-hand sidebar.
2. Select the "Run" tab.
3. In the "Command line arguments" field, enter the command-line arguments that you want to pass to your application, separated by spaces. For example, to set the --ip argument to "localhost" and the --ws_port argument to "1215", you would enter --ip localhost --ws_port 1215 in this field.
4. Click the "Apply" button to save the changes.
5. Run your project by clicking the green "Run" button in the bottom-left corner of the Qt Creator window.

When you run your project, the command-line arguments that you specified in the "Run" settings will be passed to your application. You can access these arguments in your Qt program using the QCoreApplication::arguments() method to retrieve the list of command-line arguments, as shown in my previous answers.