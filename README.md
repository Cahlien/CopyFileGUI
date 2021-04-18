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
