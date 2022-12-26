# Doxygen Documentation Instructions
To generate documentation using Doxygen, you need to have Doxygen installed on your system. Here's how you can install Doxygen on your system:

## Installing Doxygen
1. Download the latest version of Doxygen from the official website: https://www.doxygen.nl/download.html
2. Extract the downloaded archive to a location of your choice.
3. Open a terminal and navigate to the extracted folder.
4. Run the following command to install Doxygen:
```
make install
```

This will install Doxygen on your system.

## Generating documentation
Once Doxygen is installed, you can generate documentation by following these steps:

1. Open a terminal and navigate to the directory where you have your source code and the Doxyfile configuration file.
2. Run the following command to generate the documentation:
```
doxygen Doxyfile
```
This will generate the documentation in the format specified in the Doxyfile configuration file. By default, the documentation will be generated in the html folder.

You can also specify the path to the Doxyfile using the -c flag:
```
doxygen -c /path/to/doxyfile
```
This will generate the documentation using the specified Doxyfile configuration file.

You can also generate the documentation in multiple formats by specifying the desired formats in the Doxyfile. For example, to generate both HTML and Markdown documentation, you can set the GENERATE_HTML and GENERATE_MARKDOWN options to YES in the Doxyfile.

```
GENERATE_HTML = YES
GENERATE_MARKDOWN = YES
```
This will generate the documentation in both HTML and Markdown formats. The documentation will be generated in the html and markdown folders, respectively.