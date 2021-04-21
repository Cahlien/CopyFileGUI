// include the main.h header that defines the CopyApp class and has all of the required headers
#include "copyapp.h"

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

// define what to do when Copy button is clicked
void CopyApp::OnCopyEntered(wxCommandEvent& event)
{
		Copier copier{};
		// read contents of "sourceEntry" resource, a wxFilePickerCtrl, convert from wxString to std::string, and pass to setter for sourceFile
		copier.SetSource(XRCCTRL(*(guiManager.GetMainWindow()), "sourceEntry", wxFilePickerCtrl)->GetPath().ToStdString());
		// read contents of "destinationEntry" resource, a wxFilePickerCtrl, convert from wxString to std::string, and pass to setter for destinationFile 
		copier.SetDestination(XRCCTRL(*(guiManager.GetMainWindow()), "destinationEntry", wxFilePickerCtrl)->GetPath().ToStdString());
		// create workhorse thread executing function to copy source file to destination file, using getters to ensure safe access to private variables
		std::thread copy_thread(&Copier::CreateCopy, std::ref(copier));
		// detach thread so that the rest of the application can continue to process data
		copy_thread.detach();

		// run a loop to freeze the thread until completion, contrary to the intent above, until a more elegant solution is implemented
		while(!copier.isFinished())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		
		// check to see if an exception was thrown
		if(copier.GetException() != nullptr)
		{
			// if an exception was thrown, display an error dialog
			guiManager.DisplayErrorDialog("Failed to Copy File");
		}
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
	// hide window from user to make application feel faster 
	guiManager.GetMainWindow()->Show(false);
	// call OnCopyEntered to perform desired work
	OnCopyEntered(event);
	// call OnExit to close the application
	OnExit();
}

// getter for the gui manager
GUIManager* CopyApp::GetGUIManager()
{
	return &guiManager;
}
