<h1># CopyFileGUI</h1>
<p>
A graphical C++ application to clone a file with CMake and wxWidgets.
<p>

<h2>Note About Comments</h2>
<p>
	These files are fully commented to serve as examples and tutorial building blocks.  The
number of comments included is excessive for almost any purpose, but it is my belief that
such thorough and explicit declarations of the purpose for each line of code will make the
material less opaque.
</p>

<h2>GUI Management</h2>
<p>
	The responsibility for managing the GUI has been delegated to the GUIManager class
as defined in src/include/guimanager.h and src/guimanager.cpp.  This new class ensures
the proper destruction of all elements of the graphical user interface and relieves the
CopyApp class of any responsibilities other than assisting in the construction of the gui
manager and the assignment of assets to the manager's control.
</p>

<h2>Multithreading</h2>
<p>
	The act of copying a file launches a thread which then performs the work.  For the moment,
this thread joins, forcing the parent thread to wait for it to execute prior to resuming.  This is
undesired behavior, but is necessary in this transitory stage due to the implementation of the
OnCopyEntered function, which passes a local copier object to the thread.  That local object
would be deleted prior to completing the thread's execution if we detached the thread, so fixing
this is a ToDo item for the next few days.
</p>
