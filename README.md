# Ecole42-Stdheader
An automatic header setter for Ecole 42 projects.

As we all know we have to use `Stdheader` option of vim to set our headers to files that norminette requires us to. But if you have too many files and none of them has the `Stdheader` set, it can be pain in the butt to set them all one by one.

Now using this project you can set the headers of all files of the directory you choose.

First you need to compile `handler.cpp` file with the following command `g++ handler.cpp -std=c++17`

Then you'll need to execute the program but program takes two arguments, first one is the directory of the files and second one is the extension of the files.

If there is only one argument passed it'll be the directory if none passed then program will work in the current directory for the files with .c extension.
