// include the gui manager header
#include "guimanager.h"

// blank default constructor for gui manager
GUIManager::GUIManager()
{
	
}

// gui manager's destructor calls GUIManager::Close()
GUIManager::~GUIManager()
{
	Close();
}

// getter for the main window
wxFrame* GUIManager::GetMainWindow()
{
	return mainWindow;
}

// setter for the main window
void GUIManager::SetMainWindow(wxFrame* frame)
{
		mainWindow = frame;
}

// getter for the main window's icon
wxIcon* GUIManager::GetMainWindowIcon()
{
	return mainWindowIcon;
}

// setter for the main window's icon
void GUIManager::SetMainWindowIcon(wxIcon icon)
{
	mainWindowIcon = &icon;
	mainWindow->SetIcon(*mainWindowIcon);
}

// display error dialog
void GUIManager::DisplayErrorDialog(const std::string& errorMessage)
{
	wxMessageDialog* error = new wxMessageDialog(NULL, errorMessage, wxT("Error"), wxOK);
	error->ShowModal();
	wxDELETE(error);
}

// function to ensure all elements of the gui are properly dealt with
int GUIManager::Close()
{
	mainWindow->Destroy();
	return 0;
}
