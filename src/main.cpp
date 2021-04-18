// include the main.h header that defines the CopyApp class and has all of the required headers
#include "main.h"

// invoke wxWidgets' magic to instantiate the app
wxIMPLEMENT_APP(CopyApp);

// define the OnInit function, which is essentially the main() function
bool CopyApp::OnInit()
{
	// initialize all resource handlers for XML resources
	wxXmlResource::Get()->InitAllHandlers();
	// load the specified xml resource file
	wxXmlResource::Get()->Load("../../../src/include/gui.xrc");
	
	// set the gui manager's frame to the specified xrc resource
	guiManager.SetMainWindow(wxXmlResource::Get()->LoadFrame(NULL, "mainWindow"));
	
	// use the gui manager to set the frame's icon to the value of the specified file, allowing wxWidgets to figure out the bitmap type
	guiManager.SetMainWindowIcon(wxIcon("../../../src/include/Icon16.png", wxBITMAP_TYPE_ANY));
	
	// make guiManager visible
	guiManager.GetMainWindow()->Show(true);
	
	// set the top level window in the application to be the gui manager's main window
	SetTopWindow(guiManager.GetMainWindow());

	// search guiManager for resources with specified names of specified types, then bind their button_clicked events to command event handlers so that the events get processed by the app
	XRCCTRL(*(guiManager.GetMainWindow()), "copyButton", wxButton)->Bind(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CopyApp::OnCopyEntered), this, XRCID("copyButton"));
	XRCCTRL(*(guiManager.GetMainWindow()), "wxID_OK", wxButton)->Bind(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CopyApp::OnOK), this, XRCID("wxID_OK"));
	XRCCTRL(*(guiManager.GetMainWindow()), "wxID_CANCEL", wxButton)->Bind(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CopyApp::OnCancel), this, XRCID("wxID_CANCEL"));
	
	// return true if function completes successfully
	return true;
}

// define the OnExit function, which runs when the program is closed
int CopyApp::OnExit()
{
	// shutdown the gui manager
	guiManager.Close();

	// exit application with a status code of 0
	exit(0);
}

// getter for private variable, sourceFile
std::string CopyApp::GetSourceFile()
{
	return sourceFile;
}

// setter for private variable, sourceFile
void CopyApp::SetSourceFile(const std::string& name)
{
	sourceFile = name;
}

// getter for private variable, destinationFile
std::string CopyApp::GetDestinationFile()
{
	return destinationFile;
}

// setter for private variable, destinationFile
void CopyApp::SetDestinationFile(const std::string& name)
{
	destinationFile = name;
}

// define the function that actually copies the file
bool CopyApp::CopyFile(const std::string& source, const std::string& destination)
{
	// try block so it can fail gracefully
	try
	{
		// instantiate input and output files and a string variable to transfer the data
		std::ifstream inFile{};
		std::ofstream outFile{};
		std::string line{};
		
		// use input file as a resource handle for the opensource file
		inFile.open(source);
		// use output file as a resource handle for the open destination file
		outFile.open(destination);
		
		// while std::getline successfully reads a line from the source file, store it in the variable line
		while(std::getline(inFile, line))
		{
			// write what is in the line variable to the destination file and append an endline character
			outFile << line << "\n";
		}
		
		// close files via resource handles, just to be explicit (sorry, RAII)
		inFile.close();
		outFile.close();
		
		// return true if successfully completed
		return true;
	}
	// catch any exceptions that were thrown
	catch(...)
	{
		// print generic error message to standard error output
		std::cerr << "[-] error: exception thrown during file copy" << std::endl;
	}
	
	// return false, because function execution won't reach this point if it completed successfully
	return false;
}

// define what to do when Copy button is clicked
void CopyApp::OnCopyEntered(wxCommandEvent& event)
{
	// read contents of "sourceEntry" resource, a wxFilePickerCtrl, convert from wxString to std::string, and pass to setter for sourceFile
	SetSourceFile(XRCCTRL(*(guiManager.GetMainWindow()), "sourceEntry", wxFilePickerCtrl)->GetPath().ToStdString());
	// read contents of "destinationEntry" resource, a wxFilePickerCtrl, convert from wxString to std::string, and pass to setter for destinationFile 
	SetDestinationFile(XRCCTRL(*(guiManager.GetMainWindow()), "destinationEntry", wxFilePickerCtrl)->GetPath().ToStdString());
	// call workhorse function to copy source file to destination file, using getters to ensure safe access to private variables
	CopyFile(GetSourceFile(), GetDestinationFile());
}

// define what to do when Cancel is clicked
void CopyApp::OnCancel(wxCommandEvent& event)
{
	// call OnExit to close the application
	OnExit();
}

// define what to do when OK is clicked
void CopyApp::OnOK(wxCommandEvent& event)
{
	// call OnCopyEntered to perform desired work
	OnCopyEntered(event);
	// call OnExit to close the application
	OnExit();
}
