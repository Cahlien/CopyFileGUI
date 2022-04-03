# CopyFileGUI
A graphical C++ application to clone a file with CMake and wxWidgets.

## Note About Comments
These files are fully commented to serve as examples and tutorial building blocks.  The
number of comments included is excessive for almost any purpose, but it is my belief that
such thorough and explicit declarations of the purpose for each line of code will make the
material less opaque.

## GUI Management
The responsibility for managing the GUI has been delegated to the GUIManager class
as defined in src/include/guimanager.h and src/guimanager.cpp.  This new class ensures
the proper destruction of all elements of the graphical user interface and relieves the
CopyApp class of any responsibilities other than assisting in the construction of the gui
manager and the assignment of assets to the manager's control.

## Multithreading
The act of copying a file launches a thread which then performs the work.  For the moment,
this thread joins, forcing the parent thread to wait for it to execute prior to resuming.  This is
undesired behavior, but is necessary in this transitory stage due to the implementation of the
OnCopyEntered function, which passes a local copier object to the thread.  That local object
would be deleted prior to completing the thread's execution if we detached the thread, so fixing
this is a ToDo item for the next few days.

## Icon
Icons made by <a href="https://www.freepik.com" title="Freepik">Freepik</a> from <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a></div>


## Running in Docker

Before running the docker-compose, enter the following terminal command:
```bash
$ xhost +
```
Failure to enter this command will, in the current version, result in a failure to run the GUI in Docker.

After running, enter the following:
```bash
$ xhost -
```